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

ifeq ($(EXE),)
$(error Please set EXE before including common.mk)
endif

.PHONY:all
all:

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
OD = $(CROSS_COMPILE)objdump
OC = $(CROSS_COMPILE)objcopy
SPLINT = splint


SRC_C = $(filter %.c,$(SRC))
SRC_S = $(filter %.S,$(SRC))
SRC_s = $(filter %.s,$(SRC))

OBJ_C = $(patsubst %.c,%.o,$(SRC_C))
OBJ_S = $(patsubst %.S,%.o,$(SRC_S))
OBJ_s = $(patsubst %.s,%.o,$(SRC_s))
OBJ = $(OBJ_C) $(OBJ_S) $(OBJ_s)

CLEAN_LIST += $(OBJ)



DEP = $(patsubst %.o,%.d,$(OBJ_C) $(OBJ_S))

-include $(DEP)

CPPFLAGS += -MMD -MP

CLEAN_LIST += $(DEP)

$(OBJ): $(filter-out $(DEP), $(MAKEFILE_LIST))



all: $(EXE)

$(EXE): $(OBJ)
	$(LINK.o) $(sort $(OBJ)) $(LOADLIBES) $(LDLIBS) -o $@


CLEAN_LIST += $(EXE)

.PHONY: clean
clean:
	rm -f $(CLEAN_LIST)



%.bin: %
	$(OC) -O binary $< $@

%.dis: %
	$(OD) -dS $< >$@

%.c.splint.log: %.c
	$(SPLINT) -partial $(SPLINTFLAGS) $< &> $@ || :

SPLINTFLAGS += $(filter -D% -I%,$(subst -D ,-D,$(subst -I ,-I,$(CPPFLAGS))))

.PHONY: splint
splint:
	$(SPLINT) $(SPLINTFLAGS) $(SRC_C)




