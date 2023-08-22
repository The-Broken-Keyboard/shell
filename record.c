#include "headers.h"

void insertcommandinrecord(int pid,char* cn)
{
    struct recordOfCommands* nw=(struct recordOfCommands*)malloc(sizeof(struct recordOfCommands));
    if(nw==NULL)
    {
        printf("malloc failed\n");
        return;
    }
    strcpy(nw->commandname,cn);
    nw->pid=pid;
    nw->prev=recordHead->prev;
    recordHead->prev->next=nw;
    nw->next=recordHead;
    recordHead->prev=nw;
    return;
}