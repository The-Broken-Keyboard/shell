#include "headers.h"

void destroylist(struct commandnode** head)
{
    struct commandnode * temp=(*head)->prev;
    struct commandnode* prev;
    while(temp!=*head)
    {
       prev=temp->prev;
       free(temp);
       temp=prev;
    }
    free(temp);
    return;
}
void destroyRecordlist(struct recordOfCommands** head)
{
    struct recordOfCommands * temp=(*head)->prev;
    struct recordOfCommands* prev;
    while(temp!=*head)
    {
       prev=temp->prev;
       free(temp);
       temp=prev;
    }
    free(temp);
    return;
}
void removenodeFromRecordlist(struct recordOfCommands* node)
{
    struct recordOfCommands* prev=node->prev;
    struct recordOfCommands* next=node->next;
    prev->next=next;
    next->prev=prev;
    free(node);
    return;
}
void destroystringlist(char** list,int size)
{
    for(int i=0;i<size;i++)
    free(list[i]);
    free(list);
    return;
}