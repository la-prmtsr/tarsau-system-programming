#ifndef TARSAU_H
#define TARSAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILES 32
#define MAX_TOTAL_SIZE 209715200 // 200 MB

int hasSauExtension(char *fileName);
void createArchive(int fileCount, char *files[], char *outputName);
void extractArchive(char *archiveName, char *directoryName);

#endif