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

import networkx as nx
import matplotlib.pyplot as plt

def print_usage():
    print 'read_cref.py <in.map>'
    pass

def init_symbols():
    return []

def init_modules():
    return nx.MultiDiGraph()

def get_symbol(name, symbols):
    if not name in symbols:
        symbols.append(name)
    return name

def get_module(name, modules):
    if not modules.has_node(name):
        modules.add_node(name)
    return name

def add_dependency(needed_module, dependent_module, symbol, modules):
    modules.add_edge(dependent_module, needed_module, name=symbol);

def read_cref(inmap):
    
    l = inmap.readline()
    while len(l) > 0:
        words = l.split()
        if len(words) == 2:
            if words[0] == 'Symbol' and words[1] == 'File':
                break
        l = inmap.readline()
    
    symbols = init_symbols()
    modules = init_modules()
    last_symbol = None
    last_module = None
    l = inmap.readline()
    while len(l) > 0:
        words = l.split()
        if len(words) == 2:
            last_symbol = get_symbol(words[0], symbols)
            last_module = get_module(words[1], modules)
        elif len(words) == 1:
            if last_symbol == None or last_module == None:
                print 'error: ' + l
                continue
            module = get_module(words[0], modules)
            add_dependency(last_module, module, last_symbol, modules)
        else:
            print 'error: ' + l
        l = inmap.readline()
    
    print '#modules = %d' % (len(modules))
    print '#symbols = %d' % (len(symbols))
    nx.draw_spring(modules)
    plt.show()
    return


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print_usage()
        sys.exit(1)
    inmap = io.open(sys.argv[1], 'r')
    l = inmap.readline()
    while len(l) > 0:
        if l.strip() == 'Cross Reference Table':
            read_cref(inmap)
            sys.exit(0)
        l = inmap.readline()
    print 'error: cross reference table not found.'
    sys.exit(1)

