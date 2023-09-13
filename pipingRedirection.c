#include "./include/headers.h"

int invalidPipe(char* string)
{
    int size=strlen(string);
    if(string[0]=='|')
    {
        return 1;
    }
    else if(string[size-1]=='|')
    {
        return 1;
    }
    for(int i=1;i<size;i++)
    {
        if(string[i]=='|' && string[i-1]=='|')
        {
            return 1;
        }
    }
    return 0;
}
char **redirection(struct redirCommands *bhejRahaHuArray, int pos, char *string)
{
    // printf("%s\n",string);
    char **result = (char **)malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        result[i] = (char *)malloc(sizeof(char) * 500);
        result[i][0] = '\0';
    }
    int size = strlen(string);
    char *copyhelper = (char *)malloc(sizeof(char) * 500);
    char *filename = (char *)malloc(sizeof(char) * 500);
    char *command = (char *)malloc(sizeof(char) * 500);
    filename[0] = '\0';
    command[0] = '\0';
    copyhelper[0] = '\0';
    int flag = -1;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (string[i] == '<')
        {
            // if (count >= 1 && (strcmp(result[count - 1], ">") == 0 || strcmp(result[count - 1], "<") == 0 || strcmp(result[count - 1], ">>") == 0))
            // {
            //     printf("invalid redirection!\n");
            //     return NULL;
            // }
            if (strlen(copyhelper) == 0)
            {
                fprintf(stderr,RED"invalid redirection command!\n"RESET);
                return NULL;
            }
            else
            {
                catenate(result[count++], trim(copyhelper), 0);
                catenate(result[count++], "<", 0);
                for (int j = 0; j < 500; j++)
                {
                    copyhelper[j] = '\0';
                }
            }
        }
        else if (string[i] == '>')
        {
            // if (count >= 1 && (strcmp(result[count - 1], ">") == 0 || strcmp(result[count - 1], "<") == 0 || strcmp(result[count - 1], ">>") == 0))
            // {
            //     printf("haha from here invalid redirection!\n");
            //     return NULL;
            // }
            if (i + 1 >= size)
            {
                fprintf(stderr,RED"invalid redirection command!\n"RESET);
                return NULL;
            }
            else
            {
                if (string[i + 1] == '>')
                {
                    if (i + 2 >= size)
                    {
                        fprintf(stderr,RED"invalid redirection command!\n"RESET);
                        return NULL;
                    }
                    catenate(result[count++], trim(copyhelper), 0);
                    catenate(result[count++], ">>", 0);
                    for (int j = 0; j < 500; j++)
                    {
                        copyhelper[j] = '\0';
                    }
                    i = i + 1;
                }
                else
                {
                    catenate(result[count++], trim(copyhelper), 0);
                    catenate(result[count++], ">", 0);
                    for (int j = 0; j < 500; j++)
                    {
                        copyhelper[j] = '\0';
                    }
                }
            }
        }
        else
        {
            char t[1];
            t[0] = string[i];
            catenate(copyhelper, t, 0);
        }
    }
    catenate(result[count++], trim(copyhelper), 0);

    for (int i = 0; i < 500; i++)
    {
        bhejRahaHuArray[pos].command[i] = '\0';
        if (i < 100)
        {
            bhejRahaHuArray[pos].inputfrom[i] = '\0';
            bhejRahaHuArray[pos].outputfrom[i] = '\0';
        }
    }
    bhejRahaHuArray[pos].append = 0;
    int inpflag = 0;
    int outflag = 0;
    int appendflag = 0;
    for (int i = 0; i < count; i++)
    {
        if (i == 0)
        {
            catenate(bhejRahaHuArray[pos].command, result[i], 0);
        }
        else
        {
            if (strcmp(result[i], "<") == 0)
            {
                if (inpflag == 1)
                {
                    fprintf(stderr,RED"multiple input output redirection detected\n"RESET);
                    return NULL;
                }
                inpflag = 1;
                catenate(bhejRahaHuArray[pos].inputfrom, trim(result[i + 1]), 0);
                i = i + 1;
            }
            else if (strcmp(result[i], ">") == 0)
            {
                if (outflag == 1 || appendflag == 1)
                {
                    fprintf(stderr,RED"multiple input output redirection detected\n"RESET);
                    return NULL;
                }
                outflag = 1;
                catenate(bhejRahaHuArray[pos].outputfrom, trim(result[i + 1]), 0);
                i = i + 1;
            }
            else if (strcmp(result[i], ">>") == 0)
            {
                if (outflag == 1 || appendflag == 1)
                {
                    fprintf(stderr,RED"multiple input output redirection detected\n"RESET);
                    return NULL;
                }
                appendflag = 1;
                bhejRahaHuArray[pos].append = 1;
                catenate(bhejRahaHuArray[pos].outputfrom, trim(result[i + 1]), 0);
                i = i + 1;
            }
        }
    }

    return result;
}

char *Piping(char *string, int pipeinpipeflag, int so, int si)
{
    char *pipingfinalresult = (char *)malloc(sizeof(char) * 4096);
    pipingfinalresult[0] = '\0';
    // printf("%s\n",string);
    if(invalidPipe(string))
    {
        fprintf(stderr,RED"Invalid use of pipe\n"RESET);
        return pipingfinalresult;
    }
    int cnt = 0;
    // printf("%s\n",string);
    char **result = (char **)malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; i++)
    {
        result[i] = (char *)malloc(sizeof(char) * 500);
        result[i][0] = '\0';
    }
    char *token;
    char *ptr_in = NULL;
    char *temp = (char *)malloc(sizeof(char) * 500);
    temp[0] = '\0';
    catenate(temp, string, 0);
    char del[] = "|";
    token = __strtok_r(temp, del, &ptr_in);
    int count = 0;
    while (token != NULL)
    {

        catenate(result[count++], token, 0);
        token = __strtok_r(NULL, del, &ptr_in);
    }

    // for(int i=0;i<count;i++)
    // {
    //     printf("%s\n",result[i]);
    // }
    struct redirCommands *bhejRahaHuArray = (struct redirCommands *)malloc(sizeof(struct redirCommands) * count);

    // printf("%d\n",count);
    int pipefd[2];
    int oldin = dup(STDIN_FILENO);
    int oldout = dup(STDOUT_FILENO);
    int prev;
    if (pipeinpipeflag)
        prev = si;
    else
        prev = STDIN_FILENO;
    int ipfile;
    int opfile;
    int ipflag = 0;
    int opflag = 0;
    int blankfile;
    for (int i = 0; i < count; i++)
    {
        // fprintf(stderr,"%d %d\n",i,count);
        result[i] = trim(result[i]);
        char *resultSpaceOrg = spaceOrganiser(result[i]);
        // printf("%s\n",resultSpaceOrg);
        char **rs = redirection(bhejRahaHuArray, i, resultSpaceOrg);
        if (strlen(bhejRahaHuArray[i].inputfrom) != 0)
        {
            strcmp(bhejRahaHuArray[i].inputfrom, trim(bhejRahaHuArray[i].inputfrom));
        }
        if (strlen(bhejRahaHuArray[i].outputfrom) != 0)
        {
            strcmp(bhejRahaHuArray[i].outputfrom, trim(bhejRahaHuArray[i].outputfrom));
        }
        if (strlen(bhejRahaHuArray[i].command) != 0)
        {
            // fprintf(stderr, "%s\n", bhejRahaHuArray[i].command);
            strcmp(bhejRahaHuArray[i].command, trim(bhejRahaHuArray[i].command));
        }
        // fprintf(stderr,"%s\n",bhejRahaHuArray[i].outputfrom);
        if (rs == NULL)
        {
            fprintf(stderr,RED"Command No. %d contains invalid redirection\n"RESET, i + 1);
            return pipingfinalresult;
        }
        if (strcmp(bhejRahaHuArray[i].command, "pastevents") == 0 || strcmp(bhejRahaHuArray[i].command, "pastevents purge") == 0)
            pasteventsFlag = 1;
        else if (strstr(bhejRahaHuArray[i].command, "pastevents execute") == bhejRahaHuArray[i].command)
        {
            // handle pastevents execute
            char *changedCommand = pasteventsExecute(bhejRahaHuArray[i].command);
            changedCommand[strlen(changedCommand) - 1] = '\0';
            strcpy(bhejRahaHuArray[i].command, changedCommand);
            if (strlen(bhejRahaHuArray[i].command) == 0)
            {

                continue;
            }
        }
        if (pasteventsFlag == 0)
        {
            if (cnt == 0)
            {
                catenate(pipingfinalresult, bhejRahaHuArray[i].command, 0);
                if (strlen(bhejRahaHuArray[i].inputfrom) != 0)
                {
                    catenate(pipingfinalresult, "<", 1);
                    catenate(pipingfinalresult, bhejRahaHuArray[i].inputfrom, 1);
                }
                if (strlen(bhejRahaHuArray[i].outputfrom) != 0)
                {
                    if (bhejRahaHuArray[i].append)
                        catenate(pipingfinalresult, ">>", 1);
                    else
                        catenate(pipingfinalresult, ">", 1);
                    catenate(pipingfinalresult, bhejRahaHuArray[i].outputfrom, 1);
                }
                cnt++;
            }
            else
            {
                catenate(pipingfinalresult, "|", 1);
                catenate(pipingfinalresult, bhejRahaHuArray[i].command, 1);
                if (strlen(bhejRahaHuArray[i].inputfrom) != 0)
                {
                    catenate(pipingfinalresult, "<", 1);
                    catenate(pipingfinalresult, bhejRahaHuArray[i].inputfrom, 1);
                }
                if (strlen(bhejRahaHuArray[i].outputfrom) != 0)
                {
                    if (bhejRahaHuArray[i].append)
                        catenate(pipingfinalresult, ">>", 1);
                    else
                        catenate(pipingfinalresult, ">", 1);
                    catenate(pipingfinalresult, bhejRahaHuArray[i].outputfrom, 1);
                }
            }
        }

        if (pipe(pipefd) == -1)
        {
            fprintf(stderr,RED"couldn't pipe\n"RESET);
            return pipingfinalresult;
        }

        if (strlen(bhejRahaHuArray[i].inputfrom) == 0){
            // fprintf(stderr,"wc is here and %d is input fd\n",prev);
            dup2(prev, STDIN_FILENO);
        }
        else if (strlen(bhejRahaHuArray[i].inputfrom) != 0)
        {
            // fprintf(stderr,"here i am for input from a.txt\n");
            ipflag = 1;
            if (prev != 0 && prev != oldin)
            {
                close(prev);
            }
            ipfile = open(bhejRahaHuArray[i].inputfrom, O_RDONLY, 0);
            if (ipfile == -1)
            {
                fprintf(stderr, RED"input file %s didn't found\n"RESET, bhejRahaHuArray[i].inputfrom);
                if (prev != 0 && prev != oldin)
                    close(prev);
                close(pipefd[1]);
                close(pipefd[0]);
                dup2(oldin, STDIN_FILENO);
                dup2(oldout, STDOUT_FILENO);
                return pipingfinalresult;
            }
            dup2(ipfile, STDIN_FILENO);
        }
        // fprintf(stderr,"%d %d\n",i,count);
        if (i == count - 1)
        {
            // fprintf(stderr,"%d\n",strlen(bhejRahaHuArray[i].outputfrom));
            if (strlen(bhejRahaHuArray[i].outputfrom) == 0)
            {
                // fprintf(stderr,"%d %d\n",pipefd[0],pipefd[1]);
                // fprintf(stderr,"%d is the oldout\n",oldout);
                close(pipefd[0]);
                close(pipefd[1]);
                if (pipeinpipeflag)
                    dup2(so, STDOUT_FILENO);
                else{
                    // fprintf(stderr,"yeah\n");
                    dup2(oldout, STDOUT_FILENO);
                }
            }
            else
            {
                // fprintf(stderr,"here i am for output to b.txt\n");
                opflag = 1;
                if (bhejRahaHuArray[i].append == 1)
                    opfile = open(bhejRahaHuArray[i].outputfrom, O_APPEND | O_WRONLY | O_CREAT, 0644);
                else
                    opfile = open(bhejRahaHuArray[i].outputfrom, O_WRONLY | O_CREAT, 0644);
                if (opfile == -1)
                {
                    if (prev != 0 && prev != oldin)
                        close(prev);
                    close(pipefd[1]);
                    close(pipefd[0]);
                    dup2(oldin, STDIN_FILENO);
                    dup2(oldout, STDOUT_FILENO);
                    fprintf(stderr, RED"outputfile didn't open\n"RESET);
                    return pipingfinalresult;
                }
                close(pipefd[1]);
                close(pipefd[0]);
                dup2(opfile, STDOUT_FILENO);
            }
        }
        else
        {
            if (strlen(bhejRahaHuArray[i].outputfrom) == 0)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                // fprintf(stderr, "i am here and the stdout_fileno is %d\n", pipefd[1]);
            }
            else
            {
                // fprintf(stderr,"here i am for output to b.txt\n");
                opflag = 1;
                if (bhejRahaHuArray[i].append == 1)
                    opfile = open(bhejRahaHuArray[i].outputfrom, O_APPEND | O_WRONLY | O_CREAT, 0644);
                else
                    opfile = open(bhejRahaHuArray[i].outputfrom, O_WRONLY | O_CREAT, 0644);
                if (opfile == -1)
                {
                    if (prev != 0 && prev != oldin)
                        close(prev);
                    close(pipefd[1]);
                    close(pipefd[0]);
                    dup2(oldin, STDIN_FILENO);
                    dup2(oldout, STDOUT_FILENO);
                    fprintf(stderr,RED"output file didn't open\n"RESET);
                    return pipingfinalresult;
                }
                close(pipefd[1]);
                // close(pipefd[0]);
                dup2(opfile, STDOUT_FILENO);
            }
        }
        if (isPipeOrRedirection(bhejRahaHuArray[i].command))
        {
            if (ipflag && opflag)
            {
                // fprintf(stderr, "i am here 1 1\n");
                // fprintf(stderr, "%d\n", opfile);
                // fprintf(stderr, "%d\n", ipfile);
                Piping(bhejRahaHuArray[i].command, 1, opfile, ipfile);
            }
            else if (ipflag && !opflag)
            {
                // fprintf(stderr, "i am here 1 0\n");
                // fprintf(stderr, "%d\n", pipefd[1]);
                // fprintf(stderr, "%d\n", ipfile);
                Piping(bhejRahaHuArray[i].command, 1, pipefd[1], ipfile);
            }
            else if (!ipflag && opflag)
            {
                // fprintf(stderr, "i am here 0 1\n");
                // fprintf(stderr, "%d\n", opfile);
                // fprintf(stderr, "%d\n", prev);
                Piping(bhejRahaHuArray[i].command, 1, opfile, prev);
            }
            else if (!ipflag && !opflag)
            {
                // fprintf(stderr, "i am here 0 0\n");
                // fprintf(stderr, "%d %d\n", pipefd[1],pipefd[0]);
                // fprintf(stderr, "%d\n", prev);
                Piping(bhejRahaHuArray[i].command, 1, pipefd[1], prev);
            }
        }
        else if (strcmp(bhejRahaHuArray[i].command, "pastevents purge") == 0)
        {
            pasteventsPurge();
        }
        else if (strcmp(bhejRahaHuArray[i].command, "pastevents") == 0)
        {
            pastevents();
        }
        else if (strstr(bhejRahaHuArray[i].command, "pastevents execute") == bhejRahaHuArray[i].command)
        {
            // printf("%s\n", bhejRahaHuArray[i].command);
            pasteventsExecuteExtraction(bhejRahaHuArray[i].command);
        }
        else if (strstr(bhejRahaHuArray[i].command, "proclore") == bhejRahaHuArray[i].command)
        {
            proclore(bhejRahaHuArray[i].command);
        }
        else if (strstr(bhejRahaHuArray[i].command, "peek") == bhejRahaHuArray[i].command)
        {
            peek(bhejRahaHuArray[i].command);
        }
        else if (strstr(bhejRahaHuArray[i].command, "seek") == bhejRahaHuArray[i].command)
        {
            seek(bhejRahaHuArray[i].command);
        }
        else if (strcmp(bhejRahaHuArray[i].command, "activities") == 0)
        {
            activities();
        }
        // printf("%s\n",next->command);

        else if (strstr(bhejRahaHuArray[i].command, "warp") == bhejRahaHuArray[i].command)
        {
            warp(bhejRahaHuArray[i].command);
        }
        else
        {
            execVP(bhejRahaHuArray[i].command, 0);
        }

        if (ipflag != 1 && i != 0 && (prev != 0 && prev != oldin))
        {
            close(prev);
        }
        else if (ipflag == 1)
        {
            close(ipfile);
            ipflag = 0;
        }
        if (opflag != 1)
        {
            close(pipefd[1]);
            // fprintf(stderr,"i am here\n");
            prev = pipefd[0];
            // fprintf(stderr,"i am here %d %d\n",prev,pipefd[1]);
        }
        else
        {
            opflag = 0;
            close(opfile);
            // int tempblank=open("blank.txt",O_WRONLY|O_CREAT,0666);
            // close(tempblank);
            // blankfile = open("blank.txt", O_RDONLY | O_CREAT, 0666);
            prev = pipefd[0];
        }
    }
    if (pipeinpipeflag == 1){
        dup2(so,STDOUT_FILENO);
        close(oldin);
        close(oldout);
        return pipingfinalresult;
    }
    
    dup2(oldin, STDIN_FILENO);
    dup2(oldout, STDOUT_FILENO);

    return pipingfinalresult;
}