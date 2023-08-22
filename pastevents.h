#ifndef PASTEVENTS_H
#define PASTEVENTS_H

#include "headers.h"
void catenate(char *result, char *token, int spaceflag);
char* handlePastEvents(char *input);
char* pasteventsExecute(char* input);
void pasteventsExecuteExtraction(char *input);
void pasteventsPurge();
void pastevents();
#endif