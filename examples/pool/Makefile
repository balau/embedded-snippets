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

ES_ROOT = ../../
EXE = pool_test

CPPFLAGS += -I$(ES_ROOT)include/pool
WFLAGS += -Wall -Wextra
LDFLAGS += $(WFLAGS)
CFLAGS += $(WFLAGS)

SRC += pool_test.c
SRC += $(ES_ROOT)src/pool/pool.c
SRC += $(ES_ROOT)src/pool/pool_alloc.c

include $(ES_ROOT)tools/common.mk

