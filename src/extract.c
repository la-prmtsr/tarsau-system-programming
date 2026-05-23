#include "../include/tarsau.h"

void extractArchive(char *archiveName, char *directoryName)
{
    if(!hasSauExtension(archiveName))
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        return;
    }

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

    archive = fopen(archiveName, "r");

    if(archive == NULL)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        return;
    }

    if(fread(metadataSizeStr, 1, 10, archive) != 10)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        fclose(archive);
        return;
    }

    metadataSizeStr[10] = '\0';
    metadataSize = atol(metadataSizeStr);

    if(metadataSize <= 0 || metadataSize > 100000)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        fclose(archive);
        return;
    }

    metadata = (char *)malloc(metadataSize + 1);

    if(metadata == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        fclose(archive);
        return;
    }

    if(fread(metadata, 1, metadataSize, archive) != (size_t)metadataSize)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        fclose(archive);
        free(metadata);
        return;
    }

    metadata[metadataSize] = '\0';

    if(strlen(metadata) == 0)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        fclose(archive);
        free(metadata);
        return;
    }

    mkdir(directoryName, 0777);

    fseek(archive, 0, SEEK_END);
    long archiveSize = ftell(archive);

    long contentSize = archiveSize - (10 + metadataSize);

    if(contentSize < 0)
    {
        printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
        fclose(archive);
        free(metadata);
        return;
    }

    fseek(archive, 10 + metadataSize, SEEK_SET);

    content = (char *)malloc(contentSize);

    if(content == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        fclose(archive);
        free(metadata);
        return;
    }

    fread(content, 1, contentSize, archive);

    fclose(archive);

    long offset = 0;

    token = strtok(metadata, "|");

    while(token != NULL)
    {
        if(strlen(token) > 0)
        {
            if(sscanf(token, "%[^,],%o,%ld", fileName, &permissions, &fileSize) != 3)
            {
                printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
                free(metadata);
                free(content);
                return;
            }

            if(offset + fileSize > contentSize)
            {
                printf("Arsiv dosyasi uygunsuz veya bozuk!\n");
                free(metadata);
                free(content);
                return;
            }

            sprintf(fullPath,
                    "%s/%s",
                    directoryName,
                    strrchr(fileName, '/') ?
                    strrchr(fileName, '/') + 1 :
                    fileName);

            outputFile = fopen(fullPath, "w");

            if(outputFile == NULL)
            {
                printf("%s dosyasi olusturulamadi!\n", fullPath);
                free(metadata);
                free(content);
                return;
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