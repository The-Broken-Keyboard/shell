#include "./include/headers.h"
struct recordOfCommands *recordHead;
char *input;
char *shellpath;
int main()
{
    // struct sigaction sa;
    // sa.sa_handler = &handle_c;
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGINT, &sa, NULL);
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    struct sigaction sa2;
    sa2.sa_handler = &neonatefunc;
    sa2.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa2, NULL);
    // signal(SIGINT, &handle_c);
    // signal(SIGTSTP, &handle_z);
    recordHead = (struct recordOfCommands *)malloc(sizeof(struct recordOfCommands));
    shellpath = (char *)malloc(sizeof(char) * 500);
    recordHead->next = recordHead;
    recordHead->prev = recordHead;
    originalpath();
    x();
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt();
        input = (char *)malloc(sizeof(char) * 5000);
        sleepflag = 0;
        // char input[4096];
        // fgets(input, 4096, stdin);
        input = inputTaker();
        printf("\n");
        // parse function returns a linkedlist of separate command lines
        struct commandnode *result = parse(input);
        if (result == NULL)
        {
            fprintf(stderr, RED "ERROR: Syntax error! Please enter valid command\n" RESET);
        }
        else
        {
            int returnvalue = commandExtraction(result);
            if (returnvalue == -1)
                break;
            destroylist(&result);
        }
        printfinished();
        // destroylist(&result);
    }
}
