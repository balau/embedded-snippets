#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern char _binary_idstrings_bin_start;
extern char _binary_idstrings_bin_end;
extern char _binary_idstrings_bin_size;

int main(int argc, char *argv[])
{
    unsigned long id;
    char *s;

    if(argc < 2)
    {
        s = &_binary_idstrings_bin_start;
        while(*s == '\0')
            s++;
        while(s < &_binary_idstrings_bin_end)
        {
            size_t len;
            id = (s - &_binary_idstrings_bin_start) + IDSTRINGS_OFFSET;
            len = strlen(s);
            printf("%p %u %s\n",
                    id, len, s);
            s += len;
            while(*s == '\0')
                s++;
        }
        return 0;
    }
    id = strtoul(argv[1], NULL, 0);
    id -= IDSTRINGS_OFFSET;
    if(id < 0)
        return 1;
    if(id >= (unsigned long)&_binary_idstrings_bin_size)
        return 2;
    s = &_binary_idstrings_bin_start;
    s += id;
    fputs(s, stdout);
    return 0;
}

