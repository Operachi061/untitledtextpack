#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    char input[99];
    while(1) {
        char path[999] = "/usr/bin/";
        printf("$ ");
        scanf("%s", &input);
        fflush(stdout);
        strcat(path, input);
        if (input == "exit") { 
            return 0;
        }
        FILE *fp = fopen(path, "r");
        if (fp == NULL) {
            printf("utsh => Command %s not found.\n", path);
        } else {
            int status;
            pid_t argv = fork();
            if (argv == 0) {
                execl(path, input, NULL);
            }
            //exit(1);
           // waitpid(argv, &status, 0);
        }
    }
}
