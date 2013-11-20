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

CFLAGS += -I$(ES_ROOT)include/idstring/
LDFLAGS += -Xlinker -Map=idstring_test.map

ifeq ($(IDSTRING),1)
IDSTRING_SECTION = .idstrings
CFLAGS += -DIDSTRING_EXPAND_TO_ID
CFLAGS += -DIDSTRING_SECTION=$(IDSTRING_SECTION)
endif

OBJDUMP_IDSTRINGS = $(shell objdump -h idstring_test -j $(IDSTRING_SECTION)|grep $(IDSTRING_SECTION))
WORD_N_VMA = 5
IDSTRINGS_OFFSET = 0x$(word $(WORD_N_VMA), $(OBJDUMP_IDSTRINGS))


BUILDCC = cc
BUILDTARGET = $(word 3, $(shell $(BUILDCC) -c -x c -o tmp.o - </dev/null && objdump -f tmp.o | grep -o "file format .*$$" && rm tmp.o))
comma:=,
BUILDARCH = $(subst $(comma),,$(word 2, $(shell $(BUILDCC) -c -x c -o tmp.o - </dev/null && objdump -f tmp.o | grep -o "architecture: .*," && rm tmp.o)))

all:

all: idstring_test

idstring_test: idstring_test.o

idstring_test.o: $(ES_ROOT)include/idstring/idstring.h


idstring_test.idstrings.bin: idstring_test
	objcopy -O binary -j $(IDSTRING_SECTION) $< $@

idstring_test.idstrings.o: idstring_test.idstrings.bin
	objcopy -I binary -O $(BUILDTARGET) -B $(BUILDARCH)\
		--redefine-sym _binary_idstring_test_idstrings_bin_start=_binary_idstrings_bin_start\
		--redefine-sym _binary_idstring_test_idstrings_bin_end=_binary_idstrings_bin_end\
		--redefine-sym _binary_idstring_test_idstrings_bin_size=_binary_idstrings_bin_size\
		$< $@

ifeq ($(IDSTRING),1)
all: idstring_test.id2string
endif

idstring_test.id2string: idstring_test.idstrings.o
	$(BUILDCC) -DIDSTRINGS_OFFSET=$(IDSTRINGS_OFFSET) $(ES_ROOT)tools/id2string.c idstring_test.idstrings.o -o $@

idstring_test.id2string: CFLAGS += -DIDSTRINGS_OFFSET=$(IDSTRINGS_OFFSET)

clean:
	rm -rf $(ES_ROOT)src/idstring/idstring.o idstring_test.o idstring_test
	rm -rf idstring_test.idstrings.bin idstring_test.idstrings.o
	rm -rf idstring_test.id2string
	rm -rf idstring_test.map

