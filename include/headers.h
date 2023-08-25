#ifndef HEADERS_H_
#define HEADERS_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
extern int flag;
extern int pasteventsFlag;
extern char* commandsname;
extern time_t timetaken;
extern char* shellpath;
struct commandnode{
    char command[200];
    bool bg;
    struct commandnode* next;
    struct commandnode* prev;
};
struct recordOfCommands{
    int pid;
    char commandname[200];
    struct recordOfCommands* next;
    struct recordOfCommands* prev;
};
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
extern struct recordOfCommands* recordHead;
#include "error.h"
#include "execVP.h"
#include "extract_command.h"
#include "parse.h"
#include "prompt.h"
#include "warp.h"
#include "freelist.h"
#include "record.h"
#include "pastevents.h"
#include "proclore.h"
#include "peek.h"
#include "seek.h"
#endif