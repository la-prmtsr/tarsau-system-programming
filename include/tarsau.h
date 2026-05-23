#ifndef TARSAU_H
#define TARSAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void createArchive(int fileCount, char *files[], char *outputName);
void extractArchive(char *archiveName, char *directoryName);

#endif