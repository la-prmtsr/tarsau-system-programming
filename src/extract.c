#include "../include/tarsau.h"

void extractArchive(char *archiveName, char *directoryName)
{
    FILE *archive;

    FILE *outputFile;

    char metadataSizeStr[11];

    long metadataSize;

    char *metadata;

    char *token;

    char fileName[256];

    int permissions;

    long fileSize;

    char fullPath[512];

    char *content;

    // int i;

    archive = fopen(archiveName, "r");

    if(archive == NULL)
    {
        printf("Arsiv dosyasi acilamadi!\n");
        return;
    }

    /* ILK 10 BYTE OKU */

    fread(metadataSizeStr, 1, 10, archive);

    metadataSizeStr[10] = '\0';

    metadataSize = atol(metadataSizeStr);

    /* METADATA OKU */

    metadata = (char *)malloc(metadataSize + 1);

    fread(metadata, 1, metadataSize, archive);

    metadata[metadataSize] = '\0';

    /* KLASOR OLUSTUR */

    mkdir(directoryName, 0777);

    /* DOSYA ICERIKLERINI BELLEGE AL */

    fseek(archive, 10 + metadataSize, SEEK_SET);

    fseek(archive, 0, SEEK_END);

    long archiveSize = ftell(archive);

    long contentSize = archiveSize - (10 + metadataSize);

    fseek(archive, 10 + metadataSize, SEEK_SET);

    content = (char *)malloc(contentSize);

    fread(content, 1, contentSize, archive);

    fclose(archive);

    long offset = 0;

    /* METADATA PARSE */

    token = strtok(metadata, "|");

    while(token != NULL)
    {
        if(strlen(token) > 0)
        {
            sscanf(token,
                   "%[^,],%o,%ld",
                   fileName,
                   &permissions,
                   &fileSize);

            sprintf(fullPath,
                    "%s/%s",
                    directoryName,
                    strrchr(fileName, '/') ?
                    strrchr(fileName, '/') + 1 :
                    fileName);

            outputFile = fopen(fullPath, "w");

            if(outputFile == NULL)
            {
                token = strtok(NULL, "|");
                continue;
            }

            fwrite(content + offset, 1, fileSize, outputFile);

            fclose(outputFile);

            chmod(fullPath, permissions);

            offset += fileSize;

            printf("%s dosyasi acildi.\n", fullPath);
        }

        token = strtok(NULL, "|");
    }

    free(metadata);

    free(content);

    printf("Arsiv acma tamamlandi.\n");
}