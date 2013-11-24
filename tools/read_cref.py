#!/usr/bin/env python
#
# Copyright (c) 2013 Francesco Balducci
#
# This file is part of embedded-snippets.
#
#    embedded-snippets is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    embedded-snippets is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with embedded-snippets.  If not, see <http://www.gnu.org/licenses/>.
#

from sys import exit
from io import open
from optparse import OptionParser
from re import match
import networkx

def get_entry_module(modules, entry):
    entry_edges = filter(lambda e: e[2]['label'] == entry, modules.edges(data=True))
    entry_modules = set(map(lambda e: e[1], entry_edges))
    if len(entry_modules) != 1:
        return None
    return entry_modules.pop()

def get_cref_from_entry_module(modules, entry_module):
    nodes = networkx.dfs_preorder_nodes(modules, entry_module)
    return modules.subgraph(nodes)

def get_cref_from_entry(modules, entry):
    entry_module = get_entry_module(modules, entry)
    return get_cref_from_entry_module(modules, entry_module)
    
def get_cref_excluding_modules(modules, exclude_modules):
    nodes = filter(
            lambda n: not any(map(
                lambda p: match('.*' + p + '.*', n),
                exclude_modules)),
            modules.nodes())
    return modules.subgraph(nodes)

def find_cref(inmap):
    while True:
        l = inmap.readline()
        if l.strip() == 'Cross Reference Table':
            break;
        if len(l) == 0: return False
    while True:
        l = inmap.readline()
        if len(l) == 0: return False
        words = l.split()
        if len(words) == 2:
            if words[0] == 'Symbol' and words[1] == 'File':
                return True

def read_cref(inmap):
    modules = networkx.MultiDiGraph()
    last_symbol = None
    last_module = None
    while True:
        l = inmap.readline()
        words = l.split()
        if len(words) == 2:
            last_symbol = words[0]
            last_module = words[1]
            if not last_module in modules: modules.add_node(last_module)
        elif len(words) == 1:
            if last_symbol:
                module = words[0]
                if not module in modules: modules.add_node(module)
                modules.add_edge(module, last_module, label=last_symbol);
        elif len(l) == 0:
            return modules
        else:
            print 'error: syntax of line: ' + l
    return modules

def get_collapsed(modules):
    collapsed = networkx.MultiDiGraph()
    collapsed.add_nodes_from(modules.nodes())
    for e in modules.edges():
        if not e in collapsed.edges():
            collapsed.add_edge(e[0], e[1])
    return collapsed

if __name__ == '__main__':
    parser = OptionParser(usage='Usage: %prog [options] mapfile out.dot')
    parser.set_defaults(exclude_modules=[])
    parser.add_option('-x', '--exclude-modules',
            action='append', dest='exclude_modules', metavar='FILTER',
            help='ignore modules that match FILTER, expressed as a regular expression.')
    parser.add_option('-e', '--entry', dest='entry', metavar='ENTRY',
            help='consider function (or variable) ENTRY as the entry point and compute module dependencies from there.')
    parser.add_option('-c', '--collapse-symbols',
            action='store_true', dest='collapse_symbols', default=False,
            help='Collapse symbols information, displaying only dependencies between modules.')
    (options, args) = parser.parse_args()
    if len(args) != 2:
        parser.print_usage()
        exit(1)
    inmap = open(args[0], 'r')
    if not find_cref(inmap):
        print 'error: cross reference table not found.'
        exit(1)
    modules = read_cref(inmap)
    entry_module = None
    if options.entry:
        entry_module = get_entry_module(modules, options.entry)
        if entry_module:
            print 'entry module (containing entry point): %s (%s)' % (entry_module, options.entry)
        else:
            print 'error: cannot find entry point %s.' % entry
            exit(1)
    if options.exclude_modules:
        modules = get_cref_excluding_modules(modules, options.exclude_modules)
    if entry_module:
        networkx.set_node_attributes(modules, 'shape', { entry_module: 'doubleoctagon' })
        modules = get_cref_from_entry_module(modules, entry_module)
    if options.collapse_symbols:
        modules = get_collapsed(modules)
    networkx.write_dot(modules, args[1])
    exit(0)

