#include "headers.h"

int main()
{
    FILE *fptr = fopen("hello.bin", "a");
    if (fptr == NULL)
        printf("file not found\n");
    char line[500];
    // strcpy(line, "hello ji");
    // fwrite(line, sizeof(char), 500, fptr);
    // strcpy(line, "okay ji");
    // fwrite(line, sizeof(char), 500, fptr);
    // strcpy(line, "achha ji");
    // fwrite(line, sizeof(char), 500, fptr);
    // strcpy(line, "oh ji");
    // fwrite(line, sizeof(char), 500, fptr);
    fclose(fptr);
    fptr = fopen("hello.bin", "r");
    char buff[500];
    int count = 0;
    while (fread(buff, sizeof(char), 500, fptr))
        count++;
    fseek(fptr,0,SEEK_SET);
    int totallines = count;
    count = 0;
    char readfile[500];
    int lineno = totallines - 2+ 1;
    while (fread(readfile, sizeof(char), 500, fptr))
    {
        count++;
        if (count == lineno)
        {
            printf("%s\n", readfile);
            break;
        }
    }

    fclose(fptr);
}