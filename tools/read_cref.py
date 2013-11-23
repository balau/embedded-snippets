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

import sys
import io
from optparse import OptionParser
import networkx as nx
import matplotlib.pyplot as plt
import re

def add_dependency(needed_module, dependent_module, symbol, modules):
    modules.add_edge(dependent_module, needed_module, label=symbol);

def get_entry_module(modules, entry):
    entry_edges = filter(lambda e: e[2]['label'] == entry, modules.edges(data=True))
    entry_module = None
    for e in entry_edges:
        if not entry_module:
            entry_module = e[1]
        else:
            if entry_module != e[1]:
                # error: entry point is ambiguous.
                return None
    return entry_module

def get_cref_from_entry_module(modules, entry_module):
    nodes = nx.dfs_preorder_nodes(modules, entry_module)
    return modules.subgraph(nodes)

def get_cref_from_entry(modules, entry):
    entry_module = get_entry_module(modules, entry)
    return get_cref_from_entry_module(modules, entry_module)
    
def get_cref_excluding_modules(modules, exclude_modules):
    nodes = filter(
            lambda n: not any(map(
                lambda p: re.match('.*' + p + '.*', n),
                exclude_modules)),
            modules.nodes())
    return modules.subgraph(nodes)

def read_cref(inmap, options):
    while True:
        l = inmap.readline()
        if len(l) == 0:
            print 'error: cannot find start of cross reference table.'
            exit(1)
        words = l.split()
        if len(words) == 2:
            if words[0] == 'Symbol' and words[1] == 'File':
                break
    modules = nx.MultiDiGraph()
    last_symbol = None
    last_module = None
    l = inmap.readline()
    while len(l) > 0:
        words = l.split()
        if len(words) == 2:
            last_symbol = words[0]
            last_module = words[1]
            if not last_module in modules: modules.add_node(last_module)
        elif len(words) == 1:
            if last_symbol == None or last_module == None:
                pass
            else:
                module = words[0]
                if not module in modules: modules.add_node(module)
                add_dependency(last_module, module, last_symbol, modules)
        else:
            print 'error: syntax of line: ' + l
        l = inmap.readline()
    return modules

def create_dot(graph, filename):
    nx.write_dot(graph, filename)

def plot(graph):
    nx.draw_graphviz(modules, prog='dot')
    plt.show()

if __name__ == '__main__':
    parser = OptionParser(usage='Usage: %prog [options] mapfile [out.dot]')
    parser.set_defaults(exclude_modules=[])
    parser.add_option('-x', '--exclude-modules',
            action='append', dest='exclude_modules', metavar='FILTER',
            help='ignore modules that match FILTER, expressed as a regular expression.')
    parser.add_option('-e', '--entry', dest='entry', metavar='ENTRY',
            help='consider function (or variable) ENTRY as the entry point and compute module dependencies from there.')
    (options, args) = parser.parse_args()
    if len(args) < 1 or len(args) > 2:
        parser.print_usage()
        sys.exit(1)
    inmap = io.open(args[0], 'r')
    l = inmap.readline()
    while len(l) > 0:
        if l.strip() == 'Cross Reference Table':
            modules = read_cref(inmap, options)
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
                nx.set_node_attributes(modules, 'shape', { entry_module: 'doubleoctagon' })
                modules = get_cref_from_entry_module(modules, entry_module)
            if len(args) >= 2:
                create_dot(modules, args[1])
            else:
                plot(modules)
            sys.exit(0)
        l = inmap.readline()
    print 'error: cross reference table not found.'
    sys.exit(1)

