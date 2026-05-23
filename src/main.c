#include "../include/tarsau.h"

int main(int argc, char *argv[])
{
    int i;

    if(argc < 2)
    {
        printf("Kullanim hatasi!\n");
        return 1;
    }

    /* ARCHIVE CREATE MODE */
    if(strcmp(argv[1], "-b") == 0)
    {
        char *outputName = "a.sau";

        int fileCount = 0;
        char *files[32];

        for(i = 2; i < argc; i++)
        {
            if(strcmp(argv[i], "-o") == 0)
            {
                if(i + 1 < argc)
                {
                    outputName = argv[i + 1];
                    break;
                }
                else
                {
                    printf("Cikti dosya adi eksik!\n");
                    return 1;
                }
            }

            files[fileCount++] = argv[i];
        }

        printf("Arsivleme modu secildi.\n");

        printf("Dosyalar:\n");

        for(i = 0; i < fileCount; i++)
        {
            printf("%s\n", files[i]);
        }

        printf("Cikti arsivi: %s\n", outputName);

        createArchive(fileCount, files, outputName);
    }

    /* ARCHIVE EXTRACT MODE */
    else if(strcmp(argv[1], "-a") == 0)
    {
        if(argc < 3)
        {
            printf("Arsiv dosyasi eksik!\n");
            return 1;
        }

        char *archiveName = argv[2];

        char *directoryName = ".";

        if(argc >= 4)
        {
            directoryName = argv[3];
        }

        printf("Arsiv acma modu secildi.\n");
        printf("Arsiv: %s\n", archiveName);
        printf("Hedef dizin: %s\n", directoryName);

        extractArchive(archiveName, directoryName);
    }

    else
    {
        printf("Gecersiz parametre!\n");
        return 1;
    }

    return 0;
}