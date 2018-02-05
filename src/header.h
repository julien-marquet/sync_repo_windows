#ifndef HEADER_H

# define HEADER_H
# define MAX_LEN 255
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <windows.h>   // WinApi header


int     check_last_modification(char path[MAX_LEN], FILE *f_modified);
char    *trim_end(char str[MAX_LEN]);
int    launchCopy(char path[MAX_LEN], HANDLE hConsole, WORD saved_attributes);
char    *getFolderName(char path[MAX_LEN]);
void prepend(char* s, char t);

#endif