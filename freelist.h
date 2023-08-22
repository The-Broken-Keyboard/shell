#ifndef FREELIST_H
#define FREELIST_H
#include "headers.h"
void destroylist(struct commandnode** head);
void destroystringlist(char** list,int size);
void destroyRecordlist(struct recordOfCommands** head);
void removenodeFromRecordlist(struct recordOfCommands* node);
#endif

