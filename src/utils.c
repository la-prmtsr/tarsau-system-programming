#include "../include/tarsau.h"

int hasSauExtension(char *fileName)
{
    int len = strlen(fileName);

    if(len < 5)
    {
        return 0;
    }

    return strcmp(fileName + len - 4, ".sau") == 0;
}