#ifndef SEEK_H
#define SEEK_H
#include "headers.h"

void seek(char* input);
void letsSearch(char **arr, char **finalresult, char **searchpath, int searchpathPos);
void writefinalanswer(char **finalanswer, char **searchpath,int searchpathPos, char *filename);
int isdirectory(char *filename, char *path);
int isdirectory2(char *path);
int isexecutable(char *filename, char *path);
char* dotRemoval(char*string, char* actualpath);
#endif