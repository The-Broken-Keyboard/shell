#ifndef RAWMODE_H
#define RAWMODE_H
#include "headers.h"

void die(const char *s);
void disableRawMode();
void enableRawMode();
char* inputTaker();

#endif