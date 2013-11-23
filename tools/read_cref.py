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

def init_symbols():
    return []

def init_modules():
    return nx.MultiDiGraph()

def exclude_module(name, exclude_modules):
    for p in exclude_modules:
        pext = '.*' + p + '.*'
        if re.match(pext, name):
            return True
    return False

def get_symbol(name, symbols):
    if not name in symbols:
        symbols.append(name)
    return name

def get_module(name, modules):
    if not modules.has_node(name):
        modules.add_node(name)
    return name

def add_dependency(needed_module, dependent_module, symbol, modules):
    modules.add_edge(dependent_module, needed_module, label=symbol);

def get_cref_from_entry(graph, entry):
    entry_edges = filter(lambda e: e[2]['label'] == entry, graph.edges(data=True))
    if len(entry_edges) == 0:
        print 'error: cannot find entry point %s.' % entry
        exit(1)
    entry_node = None
    for e in entry_edges:
        if not entry_node:
            entry_node = e[1]
        else:
            if entry_node != e[1]:
                print 'error: entry point %s ambiguous.' % entry
                exit(1)
    print 'entry module (containing entry point): %s (%s)' % (entry_node, entry)
    nx.set_node_attributes(graph, 'shape', { entry_node: 'doubleoctagon' })
    nodes = nx.dfs_preorder_nodes(graph, entry_node)
    return graph.subgraph(nodes)

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
    symbols = []
    modules = nx.MultiDiGraph()
    last_symbol = None
    last_module = None
    l = inmap.readline()
    while len(l) > 0:
        words = l.split()
        if len(words) == 2:
            if not exclude_module(words[1], options.exclude_modules):
                last_symbol = get_symbol(words[0], symbols)
                last_module = get_module(words[1], modules)
            else:
                last_symbol = None
                last_module = None
        elif len(words) == 1:
            if last_symbol == None or last_module == None:
                pass
            elif not exclude_module(words[0], options.exclude_modules):
                module = get_module(words[0], modules)
                add_dependency(last_module, module, last_symbol, modules)
        else:
            print 'error: syntax of line: ' + l
        l = inmap.readline()
    
    print 'modules# = %d' % (len(modules))
    print 'symbols# = %d' % (len(symbols))
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
            if options.entry:
                modules = get_cref_from_entry(modules, options.entry)
            if len(args) >= 2:
                create_dot(modules, args[1])
            else:
                plot(modules)
            sys.exit(0)
        l = inmap.readline()
    print 'error: cross reference table not found.'
    sys.exit(1)

