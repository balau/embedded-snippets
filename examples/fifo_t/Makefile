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

CPPFLAGS += -I$(ES_ROOT)include/fifo/
LDFLAGS += -Wall -Wextra -pthread
CFLAGS += -Wall -Wextra

fifo_test: fifo_test.o fifo_uint8.o

fifo_test.o: $(ES_ROOT)include/fifo/fifo.h

$(ES_ROOT)src/fifo/fifo.o: $(ES_ROOT)include/fifo/fifo.h

clean:
	rm -rf $(ES_ROOT)src/fifo/fifo.o fifo_test.o fifo_test fifo_uint8.o

splint:
	splint -standard $(CPPFLAGS) fifo_test.c fifo_uint8.c

