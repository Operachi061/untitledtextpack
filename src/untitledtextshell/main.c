#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    char input[99];
    char option[99];
    while (1) {
        char path[999] = "/usr/bin/";
        printf("$ ");
        scanf("%s", input);
        fflush(stdout);
        if (!strcmp(input, "exit")) { 
            return 0;
        }
        strcat(path, input);
        /*if (!strcmp(input, "SET=./")) {
            strcat(path, input); 
        } else {
            strcat(path, "SET=/usr/bin/");
            strcat(path, input);
        } */
        FILE *fp = fopen(path, "r");
        strcpy(option, path);
        for (int i = 0; i < strlen(option); i++) {
            if (option[i] == '\0') {
                break;
            } else {
                for (int x = strlen(option) - 1; x > 0; x--) {
                    if (option[x] == '\n') {
                        option[x] = ' ';
                    } else {
                        NULL;
                    }
                }
            }
        }
        if (fp == NULL) {
            char localpath[99] = "./";
            strcat(localpath, input);
            FILE *lfp = fopen(localpath, "r");
            if (lfp == NULL) {
                printf("utsh -> Command %s not found.\n", input);
            } else { 
                printf("%s\n", option);
                int lstatus;
                pid_t largv = fork();
                if (largv == 0) {              
                    execl(localpath, input, option);
                }
                while(waitpid(largv, &lstatus, 0) == 0) {
                    NULL;
                }
            }
        } else {
            int status;
            pid_t argv = fork();
            if (argv == 0) {              
                execl(path, input, NULL);
            }
            while(waitpid(argv, &status, 0) == 0) {
                NULL;
            }
        }
    }
}
