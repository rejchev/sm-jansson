#include "utils.h"

unsigned int strncopy(char *dest, const char *src, size_t count)
{
    if (!count)
    {
        return 0;
    }

    char *start = dest;
    while ((*src) && (--count))
    {
        *dest++ = *src++;
    }
    *dest = '\0';

    return (dest - start);
}