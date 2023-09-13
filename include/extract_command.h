#ifndef EXTRACT_COMMAND_H
#define EXTRACT_COMMAND_H
#include "headers.h"

int commandExtraction(struct commandnode *result);
int isPipeOrRedirection(char* input);
int validtoken(char *token);
int iswarp(char *token);
char *commandName(char *command);

#endif