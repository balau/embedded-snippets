/*
 * Copyright (c) 2013 Francesco Balducci
 *
 * This file is part of embedded-snippets.
 *
 *    embedded-snippets is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    embedded-snippets is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with embedded-snippets.  If not, see <http://www.gnu.org/licenses/>.
 */

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

