#include "header.h"

int main(void)
{
    char    watched_buf[MAX_LEN];
    FILE    *f_watched;
    HANDLE  hConsole;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    if ((f_watched = fopen("watched_repositories.txt", "rb")) == NULL)
    {
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error! opening Watched file");
        exit(1);         
    }
    while (fgets(watched_buf, sizeof(watched_buf), f_watched) != NULL)
    {
        if (strlen(trim_end(watched_buf)) > 0 && watched_buf[0] != '#')
        {
            printf("-------------------------------------------------------------\n");
            printf("Synchronisation du dossier %s\n\n", getFolderName(trim_end(watched_buf)));
            fflush(stdout);
            launchCopy(trim_end(watched_buf), hConsole, saved_attributes);
        }
    }
    fclose(f_watched);
    
    printf("===========================================================\n");
    printf("Appuyer sur une touche pour quitter le programme\n");
    getchar();   

    return (0);
}

char    *trim_end(char str[MAX_LEN])
{
    int     i;

    i = strlen(str) - 1;
    while (i >= 0 && (str[i] == 10 || str[i] == 13 || str[i] == 32))
    {
        str[i] = '\0';
        i--;
    }
    return (str);
}
int    launchCopy(char path[MAX_LEN], HANDLE hConsole, WORD saved_attributes)
{
    FILE    *f_drive;
    char    drive_buf[MAX_LEN];
    char    cmd_str[MAX_LEN];

    system("echo %CD:~0,3% > trash/drive.txt");
    if ((f_drive = fopen("trash/drive.txt", "r")) == NULL)
    {
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error! opening drive file");
        exit(1);         
    }
    fgets(drive_buf, sizeof(drive_buf), f_drive);
    snprintf(cmd_str, sizeof(cmd_str), "xcopy \"%s\\*.*\" \"%s%s\" /C/E/H/R/K/D/M/Y/I", path, trim_end(drive_buf), getFolderName(path));
    SetConsoleTextAttribute(hConsole, 15);
    printf("Votre PC vers %s :\n  ", trim_end(drive_buf));
    SetConsoleTextAttribute(hConsole, saved_attributes);
    system(cmd_str);
    snprintf(cmd_str, sizeof(cmd_str), "xcopy \"%s%s\" \"%s\\*.*\" /C/E/H/R/K/D/M/Y/I", trim_end(drive_buf), getFolderName(path), path);
    SetConsoleTextAttribute(hConsole, 15);
    printf("%s vers votre PC :\n  ", trim_end(drive_buf));
    SetConsoleTextAttribute(hConsole, saved_attributes);
    system(cmd_str);
    fflush(stdout);
    SetConsoleTextAttribute(hConsole, 10);
    printf("\nSucces\n");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    fflush(stdout);
    fclose(f_drive);
    return (0);
}

char    *getFolderName(char path[MAX_LEN])
{
    int     i;
    char*   s;
    if ((s = (char*)malloc(MAX_LEN * sizeof(char))) == NULL)
    {
        exit(1);
    }
    s[0] = '\0';
    i = strlen(path) - 1;
    while (i >= 0 && path[i] != '\\')
    {
        prepend(s, path[i]);
        i--;
    }

    return (s);
}

void prepend(char* s, char t)
{
    size_t i;

    memmove(s + 1, s, strlen(s) + 1);

    for (i = 0; i < 1; ++i)
        s[i] = t;
}
