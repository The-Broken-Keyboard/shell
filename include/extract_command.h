#ifndef EXTRACT_COMMAND_H
#define EXTRACT_COMMAND_H
#include "headers.h"

void commandExtraction(struct commandnode *result);
int validtoken(char *token);
int iswarp(char *token);
char *commandName(char *command);

#endif