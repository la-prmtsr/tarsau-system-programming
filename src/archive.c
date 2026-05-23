#include "../include/tarsau.h"

void createArchive(int fileCount, char *files[], char *outputName)
{
    FILE *archive;

    FILE *inputFile;

    char metadata[4096] = "";

    char temp[512];

    char buffer[1024];

    int i;

    long fileSize;

    struct stat fileStat;

    archive = fopen(outputName, "w");

    if(archive == NULL)
    {
        printf("Arsiv dosyasi olusturulamadi!\n");
        return;
    }

    /* METADATA OLUSTUR */

    for(i = 0; i < fileCount; i++)
    {
        inputFile = fopen(files[i], "r");

        if(inputFile == NULL)
        {
            printf("%s dosyasi acilamadi!\n", files[i]);
            fclose(archive);
            return;
        }

        stat(files[i], &fileStat);

        fseek(inputFile, 0, SEEK_END);

        fileSize = ftell(inputFile);

        rewind(inputFile);

        sprintf(temp, "|%s,%o,%ld|",
                files[i],
                fileStat.st_mode & 0777,
                fileSize);

        strcat(metadata, temp);

        fclose(inputFile);
    }

    /* ILK 10 BYTE = METADATA BOYUTU */

    fprintf(archive, "%010ld", strlen(metadata));

    /* METADATA YAZ */

    fprintf(archive, "%s", metadata);

    /* DOSYA ICERIKLERI */

    for(i = 0; i < fileCount; i++)
    {
        inputFile = fopen(files[i], "r");

        if(inputFile == NULL)
        {
            continue;
        }

        while(fgets(buffer, sizeof(buffer), inputFile))
        {
            fprintf(archive, "%s", buffer);
        }

        fclose(inputFile);
    }

    fclose(archive);

    printf("Dosyalar birlestirildi.\n");
}