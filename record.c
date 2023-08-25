#include "./include/headers.h"

void insertcommandinrecord(int pid,char* cn)
{
    struct recordOfCommands* nw=(struct recordOfCommands*)malloc(sizeof(struct recordOfCommands));
    if(nw==NULL)
    {
        fprintf(stderr,RED"malloc failed\n"RESET);
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