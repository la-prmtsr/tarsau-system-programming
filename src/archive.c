#include "../include/tarsau.h"
#include <ctype.h>

void createArchive(int fileCount, char *files[], char *outputName)
{
    FILE *archive;

    FILE *inputFile;

    char metadata[4096] = "";

    char temp[512];

    char buffer[1024];

    int i;

    long fileSize;

    long totalSize = 0;

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

        int ch;

        while((ch = fgetc(inputFile)) != EOF)
        {
            if(!isprint(ch) && !isspace(ch))
            {
                printf("%s giris dosyasinin formati uyumsuzdur!\n",
                    files[i]);

                fclose(inputFile);
                fclose(archive);

                return;
            }
        }

        rewind(inputFile);

        if(inputFile == NULL)
        {
            printf("%s dosyasi acilamadi!\n", files[i]);
            fclose(archive);
            return;
        }

        stat(files[i], &fileStat);

        fseek(inputFile, 0, SEEK_END);

        fileSize = ftell(inputFile);

        totalSize += fileSize;

        if(totalSize > MAX_TOTAL_SIZE)
        {
            printf("Toplam dosya boyutu 200 MB'i geciyor!\n");

            fclose(inputFile);
            fclose(archive);

            return;
        }

        rewind(inputFile);

        sprintf(temp, "%s,%o,%ld|",
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