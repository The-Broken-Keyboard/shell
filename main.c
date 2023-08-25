#include "./include/headers.h"
struct recordOfCommands* recordHead;
char* shellpath;
int main()
{
    // Keep accepting commands
    recordHead=(struct recordOfCommands*)malloc(sizeof(struct recordOfCommands));
    shellpath=(char*)malloc(sizeof(char)*500);
    recordHead->next=recordHead;
    recordHead->prev=recordHead;
    originalpath();
    x();
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        char input[4096];
        fgets(input, 4096, stdin);
        // parse function returns a linkedlist of separate command lines
        struct commandnode *result = parse(input);
        if(result==NULL)
        {
            fprintf(stderr,RED"ERROR: Syntax error! Please enter valid command\n"RESET);
            continue;
        }
        commandExtraction(result);
        destroylist(&result);
    }
}
