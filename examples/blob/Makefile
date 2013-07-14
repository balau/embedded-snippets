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

