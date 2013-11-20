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

.PHONY: all run printarch

all: test_blob

run: test_blob
	./test_blob

test_blob: test_blob.o blob.o

blob.o: blob.bin
	objcopy -I binary -O elf32-i386 -B i386 $< $@
	objdump -t $@

blob.bin:
	dd if=/dev/urandom of=$@ bs=1 count=16
	hexdump -C $@

printarch:
	> arch.c
	gcc -c arch.c -o arch.o
	objdump -f arch.o
	rm -f arch.c arch.o

clean:
	rm -f blob.bin blob.o
	rm -f test_blob test_blob.o

