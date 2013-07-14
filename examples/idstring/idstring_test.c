#include <stdio.h>

#include "idstring.h"

#ifdef IDSTRING_SECTION
void printidstring(intptr_t id)
{
    printf("0x%08X\n", id);
}
#else /* !IDSTRING_EXPAND_TO_ID */
void printidstring(char *str)
{
    fputs(str, stdout);
}
#endif /* IDSTRING_EXPAND_TO_ID */

int main(void)
{
    printidstring(_("Hello World!\n"));
    printidstring(_(
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "\n"
                "\n"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "0123456789abcdef"
                "\n"
                ));
    printidstring(_("Hello World!\n"));
    return 0;
}

