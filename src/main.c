#include "../include/tarsau.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Kullanim hatasi!\n");
        return 1;
    }

    if(strcmp(argv[1], "-b") == 0)
    {
        printf("Arsivleme modu secildi.\n");
    }
    else if(strcmp(argv[1], "-a") == 0)
    {
        printf("Arsiv acma modu secildi.\n");
    }
    else
    {
        printf("Gecersiz parametre!\n");
    }

    return 0;
}