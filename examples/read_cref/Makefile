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

LDFLAGS += -static
#LDFLAGS += -nostdlib

program.o: program.h
module1.o: program.h
module2.o: program.h

.PHONY: read_cref
read_cref: $(PROGRAM).map
	$(ES_ROOT)/tools/read_cref.py -e "libc\.a" -e "libgcc.*\.a" -e "crt.*\.o" $<

all: $(PROGRAM)
all: $(PROGRAM).map
all: read_cref

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


