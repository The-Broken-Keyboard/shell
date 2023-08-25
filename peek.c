#include "./include/headers.h"

char *tildaDothandler(char *string)
{
    int size = strlen(string);
    char *result = (char *)malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++)
        result[i] = '\0';
    int pos = 0;
    for (int i = 1; i < size; i++)
        result[pos++] = string[i];
    result[pos] = '\0';
    if (strlen(result) > 0)
        return result;
    return NULL;
}
static int myCompare(const void *a, const void *b)
{

    // setting up rules for comparison
    return strcmp(*(const char **)a, *(const char **)b);
}
void sort(const char *arr[], int n)
{
    // calling qsort function to sort the array
    // with the help of Comparator
    qsort(arr, n, sizeof(const char *), myCompare);
}
int block(char *filename, char *path)
{
    struct stat buff;
    char filepath[100];
    for (int i = 0; i < 100; i++)
        filepath[i] = '\0';
    catenate(filepath, path, 0);
    catenate(filepath, "/", 0);
    catenate(filepath, filename, 0);
    // printf("%s\n", array[j]);
    stat(filepath, &buff);
    return buff.st_blocks;
}
void peek(char *com)
{

    int z = 0;
    char **arr = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        arr[i] = (char *)malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++)
        strcpy(arr[i], "nothing");
    char t[100];
    char *token;
    char *ptr_out = NULL;
    char del[] = " \t\f\v\r\n";
    token = NULL;
    ptr_out = NULL;
    strcpy(t, com);
    token = __strtok_r(t, del, &ptr_out);
    z = 3;
    while (token != NULL)
    {
        if (strcmp(token, "peek") == 0)
            strcpy(arr[0], token);
        else if (strcmp(token, "-l") == 0)
            strcpy(arr[1], "-l");
        else if (strcmp(token, "-a") == 0)
            strcpy(arr[2], "-a");
        else if (strcmp(token, "-al") == 0)
        {
            strcpy(arr[1], "-l");
            strcpy(arr[2], "-a");
        }
        else if (strcmp(token, "-la") == 0)
        {
            strcpy(arr[1], "-l");
            strcpy(arr[2], "-a");
        }
        else
        {
            strcpy(arr[z++], token);
        }
        token = __strtok_r(NULL, del, &ptr_out);
    }

    // for (int i = 0; i < 100; i++)
    // {
    //     if (i >= 3 && strcmp(arr[i], "nothing") == 0)
    //         break;
    //     else
    //     {
    //         if (strcmp(arr[i], "nothing") == 0)
    //             continue;
    //         else
    //         {
    //             printf("%s\n", arr[i]);
    //         }
    //     }
    // }
    z = 3;
    if (strcmp(arr[z], "nothing") != 0)
    {
        while (strcmp(arr[z++], "nothing") != 0)
        {
            // printf("%s\n", arr[z - 1]);
            char path[100];
            for (int i = 0; i < 100; i++)
                path[i] = '\0';
            if (arr[z - 1][0] != '/')
            {
                if (arr[z - 1][0] == '~')
                {
                    catenate(path, shellpath, 0);
                    char *result = tildaDothandler(arr[z - 1]);
                    if (result != NULL)
                        catenate(path, result, 0);
                }
                else if (arr[z - 1][0] == '.')
                {
                    getcwd(path, 99);
                    char *result = tildaDothandler(arr[z - 1]);
                    if (result != NULL)
                        catenate(path, result, 0);
                }
                else
                {
                    getcwd(path, 99);
                    catenate(path, "/", 0);
                    catenate(path, arr[z - 1], 0);
                }
            }
            else
            {
                strcpy(path, arr[z - 1]);
            }
            char **array = (char **)malloc(sizeof(char *) * 5000);
            for (int i = 0; i < 5000; i++)
                array[i] = (char *)malloc(sizeof(char) * 100);
            int i = 0, j = 0, k = 0;
            DIR *dir;
            struct dirent *dent;
            char buffer[50];
            // char path[100];
            // for (int i = 0; i < 100; i++)
            //     path[i] = '\0';
            // getcwd(path, 99);
            strcpy(buffer, path);
            dir = opendir(buffer); // this part
            if (dir != NULL)
            {
                while ((dent = readdir(dir)) != NULL)
                {
                    //     printf("%s\n", dent->d_name);
                    strcpy(array[i], dent->d_name);
                    i++;
                    k++;
                }
                closedir(dir);
            }
            else
            {
                fprintf(stderr,RED"Directory didn't open\n"RESET);
            }
            sort((const char **)array, i);
            if (strcmp(arr[1], "nothing") == 0)
            {

                for (int j = 0; j < i; j++)
                {
                    if (strcmp(arr[2], "-a") != 0)
                    {
                        if (array[j][0] == '.')
                            continue;
                    }
                    if (isdirectory(array[j], path))
                        printf(BLUE "%s\n" RESET, array[j]);
                    else if (isexecutable(array[j], path))
                        printf(GREEN "%s\n" RESET, array[j]);
                    else
                        printf(WHITE "%s\n", array[j]);
                }
            }
            else
            {
                int pos = 0;
                int totalblocksum = 0;
                for (int l = 0; l < k; l++)
                {
                    if (strcmp(arr[2], "-a") != 0)
                    {
                        if (array[l][0] == '.')
                            continue;
                    }
                    totalblocksum += block(array[l], path);
                }
                printf("total %d\n", totalblocksum);
                for (int j = 0; j < k; j++)
                {
                    if (strcmp(arr[2], "-a") != 0)
                    {
                        if (array[j][0] == '.')
                            continue;
                    }
                    struct stat buff;
                    char filepath[100];
                    for (int i = 0; i < 100; i++)
                        filepath[i] = '\0';
                    catenate(filepath, path, 0);
                    catenate(filepath, "/", 0);
                    catenate(filepath, array[j], 0);
                    // printf("%s\n", array[j]);
                    // printf("%s\n",filepath);
                    stat(filepath, &buff);
                    struct group *g;
                    g = getgrgid(buff.st_gid);
                    if (g == NULL)
                    {
                        fprintf(stderr,RED"gid %d not found\n"RESET, buff.st_gid);
                        continue;
                    }
                    struct passwd *pd;
                    pd = getpwuid(buff.st_uid);
                    if (pd == NULL)
                    {
                        fprintf(stderr,RED"getpwuid error\n"RESET);
                        continue;
                    }

                    printf("-");
                    if (buff.st_mode & S_IRUSR)
                        printf("r");
                    else
                        printf("-");
                    if (buff.st_mode & S_IWUSR)
                        printf("w");
                    else
                        printf("-");
                    if (buff.st_mode & S_IXUSR)
                        printf("x");
                    else
                        printf("-");

                    // putchar('\n');
                    if (buff.st_mode & S_IRGRP)
                        printf("r");
                    else
                        printf("-");
                    if (buff.st_mode & S_IWGRP)
                        printf("w");
                    else
                        printf("-");
                    if (buff.st_mode & S_IXGRP)
                        printf("x");
                    else
                        printf("-");
                    if (buff.st_mode & S_IROTH)
                        printf("r");
                    else
                        printf("-");
                    if (buff.st_mode & S_IWOTH)
                        printf("w");
                    else
                        printf("-");
                    if (buff.st_mode & S_IXOTH)
                        printf("x");
                    else
                        printf("-");
                    printf(" ");
                    printf("%ld ", buff.st_nlink);
                    printf("%s ", pd->pw_name);
                    printf("%s  ", g->gr_name);
                    printf("%ld ", buff.st_size);
                    char tm[100];
                    strcpy(tm, ctime(&buff.st_mtime));
                    tm[strlen(tm) - 1] = '\0';
                    if (isdirectory(array[j], path))
                        printf("%s " BLUE "%s\n" RESET, tm, array[j]);
                    else if (isexecutable(array[j], path))
                        printf("%s " GREEN "%s\n" RESET, tm, array[j]);
                    else
                        printf("%s " WHITE "%s\n" RESET, tm, array[j]);
                }
            }
        }
    }
    else
    {
        char **array = (char **)malloc(sizeof(char *) * 5000);
        for (int i = 0; i < 5000; i++)
            array[i] = (char *)malloc(sizeof(char) * 100);
        int i = 0, j = 0, k = 0;
        DIR *dir;
        struct dirent *dent;
        char buffer[50];
        char path[100];
        for (int i = 0; i < 100; i++)
            path[i] = '\0';
        getcwd(path, 99);
        strcpy(buffer, path);
        dir = opendir(buffer); // this part
        if (dir != NULL)
        {
            while ((dent = readdir(dir)) != NULL)
            {
                //     printf("%s\n", dent->d_name);
                strcpy(array[i], dent->d_name);
                i++;
                k++;
            }
            closedir(dir);
        }
        else
        {
            fprintf(stderr,RED"Directory didn't open\n"RESET);
        }
        sort((const char **)array, i);

        if (strcmp(arr[1], "nothing") == 0)
        {

            for (int j = 0; j < i; j++)
            {
                if (strcmp(arr[2], "-a") != 0)
                {
                    if (array[j][0] == '.')
                        continue;
                }
                if (isdirectory(array[j], path))
                    printf(BLUE "%s\n" RESET, array[j]);
                else if (isexecutable(array[j], path))
                    printf(GREEN "%s\n" RESET, array[j]);
                else
                    printf(WHITE "%s\n", array[j]);
            }
        }
        else
        {
            int pos = 0;
            int totalblocksum = 0;
            for (int l = 0; l < k; l++)
            {
                if (strcmp(arr[2], "-a") != 0)
                {
                    if (array[l][0] == '.')
                        continue;
                }
                totalblocksum += block(array[l], path);
            }
            printf("total %d\n", totalblocksum);
            for (int j = 0; j < k; j++)
            {
                if (strcmp(arr[2], "-a") != 0)
                {
                    if (array[j][0] == '.')
                        continue;
                }
                struct stat buff;
                char filepath[100];
                for (int i = 0; i < 100; i++)
                    filepath[i] = '\0';
                catenate(filepath, path, 0);
                catenate(filepath, "/", 0);
                catenate(filepath, array[j], 0);
                // printf("%s\n", array[j]);
                // printf("%s\n",filepath);
                stat(filepath, &buff);
                struct group *g;
                g = getgrgid(buff.st_gid);
                if (g == NULL)
                {
                    fprintf(stderr,RED"gid %d not found\n"RESET, buff.st_gid);
                    continue;
                }
                struct passwd *pd;
                pd = getpwuid(buff.st_uid);
                if (pd == NULL)
                {
                    fprintf(stderr,RED"getpwuid error\n"RESET);
                    continue;
                }

                // printf("-");
                switch (buff.st_mode & __S_IFMT)
                {
                case __S_IFREG:
                    printf("-");
                    break;
                case __S_IFDIR:
                    printf("d");
                    break;
                case __S_IFBLK:
                    printf("b");
                    break;
                case __S_IFCHR:
                    printf("c");
                    break;
                case __S_IFIFO:
                    printf("p");
                    break;
                case __S_IFLNK:
                    printf("l");
                    break;
                case __S_IFSOCK:
                    printf("s");
                    break;
                default:
                    printf("?"); // Unknown file
                }
                if (buff.st_mode & S_IRUSR)
                    printf("r");
                else
                    printf("-");
                if (buff.st_mode & S_IWUSR)
                    printf("w");
                else
                    printf("-");
                if (buff.st_mode & S_IXUSR)
                    printf("x");
                else
                    printf("-");

                // putchar('\n');
                if (buff.st_mode & S_IRGRP)
                    printf("r");
                else
                    printf("-");
                if (buff.st_mode & S_IWGRP)
                    printf("w");
                else
                    printf("-");
                if (buff.st_mode & S_IXGRP)
                    printf("x");
                else
                    printf("-");
                if (buff.st_mode & S_IROTH)
                    printf("r");
                else
                    printf("-");
                if (buff.st_mode & S_IWOTH)
                    printf("w");
                else
                    printf("-");
                if (buff.st_mode & S_IXOTH)
                    printf("x");
                else
                    printf("-");
                printf(" ");
                printf("%ld ", buff.st_nlink);
                printf("%s ", pd->pw_name);
                printf("%s  ", g->gr_name);
                printf("%ld ", buff.st_size);
                char tm[100];
                strcpy(tm, ctime(&buff.st_mtime));
                tm[strlen(tm) - 1] = '\0';
                if (isdirectory(array[j], path))
                    printf("%s " BLUE "%s\n" RESET, tm, array[j]);
                else if (isexecutable(array[j], path))
                    printf("%s " GREEN "%s\n" RESET, tm, array[j]);
                else
                    printf("%s " WHITE "%s\n" RESET, tm, array[j]);
                // printf("%s %s\n", tm, array[j]);
            }
        }
    }
}
