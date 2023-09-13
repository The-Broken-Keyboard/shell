#include "./include/headers.h"

int compareBypid(const void *a, const void *b)
{
    struct recordOfCommands *recordA = *(struct recordOfCommands **)a;
    struct recordOfCommands *recordB = *(struct recordOfCommands **)b;
    return recordA->pid > recordB->pid;
}
void activities()
{
    if (recordHead->next == recordHead)
    {
        printf(YELLOW"no activities found!\n"RESET);
        return;
    }
    int countnodes = 0;
    struct recordOfCommands *temp = recordHead->next;
    struct recordOfCommands *next;
    while (temp != recordHead)
    {
        countnodes++;
        next = temp->next;
        temp = next;
    }
    temp = recordHead->next;
    next = NULL;
    int pos = 0;
    struct recordOfCommands **arrayofroc = (struct recordOfCommands **)malloc(sizeof(struct recordOfCommands *) * countnodes);
    while (temp != recordHead)
    {
        next = temp->next;
        arrayofroc[pos++] = temp;
        temp = next;
    }
    qsort(arrayofroc, countnodes, sizeof(struct recordOfCommands *), compareBypid);
    for (int i = 0; i < countnodes; i++)
    {
        char path[500];
        sprintf(path, "/proc/%d/stat", arrayofroc[i]->pid);
        FILE *fptr = fopen(path, "r");
        if (fptr == NULL)
        {
            fprintf(stderr, RED "file didn't open\n" RESET);
            error1();
        }
        char string[5000];
        fread(string, sizeof(char), 5000, fptr);
        char garb[100];
        char status;
        sscanf(string, "%s %s %c", garb, garb, &status);
        if (status == 'Z' || status == 'T')
        {
            printf(WHITE"%d : %s - %s\n"RESET, arrayofroc[i]->pid, arrayofroc[i]->commandname, "Stopped");
            // removenodeFromRecordlist(temp);
        }
        else if (status == 'S' || status == 'R')
        {
            printf(WHITE"%d : %s - %s\n"RESET, arrayofroc[i]->pid, arrayofroc[i]->commandname, "Running");
        }
    }
    // for (int i = 0; i < countnodes; i++)
    // {
    //     char path[500];
    //     sprintf(path, "/proc/%d/stat", arrayofroc[i]->pid);
    //     FILE *fptr = fopen(path, "r");
    //     if (fptr == NULL)
    //     {
    //         fprintf(stderr, RED "file didn't open\n" RESET);
    //         error1();
    //     }
    //     char string[5000];
    //     fread(string, sizeof(char), 5000, fptr);
    //     char garb[100];
    //     char status;
    //     sscanf(string, "%s %s %c", garb, garb, &status);
    //     if (status == 'Z')
    //     {
    //         printf("%s [%d] exited normally\n", arrayofroc[i]->commandname, arrayofroc[i]->pid);
    //         removenodeFromRecordlist(arrayofroc[i]);
    //     }

    //     // }
    //     // while (temp != recordHead)
    //     // {
    //     //     next = temp->next;
    //     //     char path[500];
    //     //     sprintf(path, "/proc/%d/stat", temp->pid);
    //     //     FILE *fptr = fopen(path, "r");
    //     //     if (fptr == NULL)
    //     //     {
    //     //         fprintf(stderr, RED "file didn't open\n" RESET);
    //     //         error1();
    //     //     }
    //     //     char string[5000];
    //     //     fread(string, sizeof(char), 5000, fptr);
    //     //     char garb[100];
    //     //     char status;
    //     //     sscanf(string, "%s %s %c", garb, garb, &status);
    //     //     if (status == 'Z')
    //     //     {
    //     //         printf("%s [%d] exited normally\n", temp->commandname, temp->pid);
    //     //         removenodeFromRecordlist(temp);
    //     //     }
    //     //     temp = next;
    //     // }
    // }
}