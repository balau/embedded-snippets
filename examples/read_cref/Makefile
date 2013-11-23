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

all:

.PHONY: all clean


PROGRAM = program

SRC += program.c
SRC += module1.c
SRC += module2.c

#DEFINES += NDEBUG
INCLUDES += ./

LDFLAGS += -Xlinker -Map=$(PROGRAM).map -Xlinker -cref

$(PROGRAM).map: $(PROGRAM)
CLEAN_LIST += $(PROGRAM).map

#LDFLAGS += -static
#LDFLAGS += -nostdlib

program.o: program.h
module1.o: program.h
module2.o: program.h

READ_CREF = $(ES_ROOT)/tools/read_cref.py
READ_CREF_FLAGS += -e main
#READ_CREF_FLAGS = -x "libc\.a" -x "libgcc.*\.a" -x "crt.*\.o"

.PHONY: plot
plot: $(PROGRAM).map
	$(READ_CREF) $(READ_CREF_FLAGS) $<

%.dot: %.map
	$(READ_CREF) $(READ_CREF_FLAGS) $< $@

DOT = dot
DOT_FLAGS = 

#DOT = neato
#DOT_FLAGS = -Goverlap=scale

%.png: %.dot
	$(DOT) $(DOT_FLAGS) -Tpng $< -o $@

all: $(PROGRAM)
all: $(PROGRAM).png
#all: plot

CLEAN_LIST += $(PROGRAM).png

SRC_C = $(filter %.c, $(SRC))
SRC_S = $(filter %.S, $(SRC))
SRC_s = $(filter %.s, $(SRC))

OBJ  = $(patsubst %.c,%.o,$(SRC_C))
OBJ += $(patsubst %.S,%.o,$(SRC_S))
OBJ += $(patsubst %.s,%.o,$(SRC_s))

DEFINE_FLAGS = $(addprefix -D,$(DEFINES))
INCLUDE_FLAGS =  $(addprefix -I,$(INCLUDES))

CPPFLAGS += $(DEFINE_FLAGS) $(INCLUDE_FLAGS)

$(PROGRAM): $(OBJ)

CLEAN_LIST += $(PROGRAM)
CLEAN_LIST += $(OBJ)

clean:
	rm -rf $(CLEAN_LIST)


