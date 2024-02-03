#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "parallel.h"

int status;

void parallel(char *cmd) {
    pid_t forking = fork();
    if (forking == 0) {
        system(cmd);
    }
    sleep(0.1);
    kill(forking, SIGTERM);
    while (waitpid(forking, &status, WNOHANG) == 0) {
        wait(NULL);
    }
}
