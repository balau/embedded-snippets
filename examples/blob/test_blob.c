#include <stdio.h>

extern unsigned char _binary_blob_bin_start;
extern unsigned char _binary_blob_bin_end;
extern unsigned char _binary_blob_bin_size;

int main()
{
    unsigned char *pblob = &_binary_blob_bin_start;
    while(pblob < &_binary_blob_bin_end)
    {
        printf("%d: %02X\n", pblob - &_binary_blob_bin_start, *pblob);
        pblob++;
    }
    printf("size: %d\n", &_binary_blob_bin_size);

    return 0;
}

