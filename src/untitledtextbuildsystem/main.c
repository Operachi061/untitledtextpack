#include <stdio.h>
#include <argp.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "loadbar.h"

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define CYAN    "\033[0;36m"
#define END     "\033[0;0m"

#define MAX_SIZE 999

int i = 0;
int cmd;
int nwlnc = 0; 
int nmbcheck = 0;
int cparallel;
int yes;
int status;
char *func;
char *parser;
char *modpath;
char chk[MAX_SIZE];
char strchk[MAX_SIZE];
char rfile[MAX_SIZE];
char file[MAX_SIZE];
char path[MAX_SIZE];

static char doc[] = "UntitledTextBuildSystem - utbs. Part of UntitledTextPack";
static struct argp_option options[] = {
  { "path", 'p', "<path>", 0, "Path to Utbsource file." },
  { "function", 'f', "<function>", 0, "Function in Utbsource file to start." },
  { "yes", 'y', 0, 0, "Confirming question." },
  { "paraller", 'P', 0, 0, "Parallel process (faster)." },
  { 0 }
};
static error_t
parse_opt (int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'f':
            func = arg;
            break;
        case 'p':
            modpath = arg;
            strcpy(path, modpath);
            strcat(path, "/Utbsource");
            break;
        case 'y':
            yes = 'p';
            break;
        case 'P':
            cparallel = 'P';
            break; 
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
static struct argp argp = { options, parse_opt, NULL, doc };
void utbsinf(void) { printf("%sUtbs -> %s", BLUE, END); }
int system(const char *command);
void loadbar(const int count);
int main(int argc, char **argv) {
    argp_parse (&argp, argc, argv, 0, 0, 0);
    printf("You started utbs.\n");
    utbsinf(); printf("Preparing process\n");
    printf("%s Utbsource file check -> %s", CYAN, END);
    FILE *fp = fopen(path, "r");
    FILE *fpt = fopen(path, "r");
    if (fp == NULL) {
        printf("%snot found%s\n", RED, END);
        printf("Exiting.\n");
        return 0;
    } else {
        printf("%sfound%s\n", GREEN, END);
    }
    printf("  Finding functions in parser\n");
    if (func == NULL) {
        printf("    FUNCTION NOT FOUND\n");
        printf("Exiting.\n");
        return 0;
    } else {
        printf("    FUNCTION FOUND\n");
    }
    strcat(chk, func);
    strcat(chk, " <");
    while (fgets(rfile, sizeof rfile, fp) != NULL) {
        char *position = strstr(rfile, chk);
        if (position == chk) {
            break;
        } else {
            i++;
        }
        if (position == NULL) {
            printf("  %s/Utbsource >> %s[ LINE: %d]%s %s\n", modpath, RED, i, END, "NOT FOUND");
            nmbcheck = 1;
        } else {
            position[strlen(chk)] = '\0';
            printf("  %s/Utbsource >> %s[ LINE: %d]%s \'%s\' %s->%s %sfound%s\n", modpath, RED, i, END, position, CYAN, END, GREEN, END);
            nmbcheck = 2;
            break;
        }
        strcat(strchk, rfile);
    }
    if (nmbcheck == 1) {
        printf("  function named '%s' not found.\n", func);
        printf("Exiting.\n");
        return 0;
    } else if (nmbcheck == 2) {
        NULL;
    } else {
        NULL;
    }
    while (fgets(rfile, sizeof rfile, fpt) != NULL) {
        strcat(file, rfile);  
    }
    for (int x = 0; x < strlen(strchk) + strlen(chk) + 1; x++) {
        file[x] = ' ';
    }
    for (int y = 0; y < strlen(file); y++) {
        if (file[y] == '>') {
            file[y] = '\0';
        }
    }
    file[strlen(file) - 1] = '\0';
    printf("%sProcess to be maked%s %s->%s       \n", BLUE, END, CYAN, END);
    printf("%s\n", file);
    if (yes == 'y') {
        printf("%sHint: You can skip question via adding \'-y\' option.%s\n", YELLOW, END);
        printf("%sMake this process ?%s %s|%s %sN%s%s/%s%sy%s ", BLUE, END, CYAN, END, GREEN, END, YELLOW, END, RED, END);
        scanf("%c", parser);
        if (!strcmp(parser, "N")) {
            printf("Exiting.\n");
            return 0;
        } else if (!strcmp(parser, "n")) {
            printf("Exiting.\n");
            return 0;
        } else if (!strcmp(parser, "Y")) {
            NULL;
        } else if (!strcmp(parser, "y")) {
            NULL;
        } else {
            printf("Exiting.\n");
            return 0;
        }
    } else {
        printf("%sUSED%s %s-y%s %sOPTION%s\n", GREEN, END, YELLOW, END, GREEN, END);
    }
    utbsinf(); printf("Starting %s process\n", func);
    for (int cfile = 0; cfile < strlen(file); cfile++) {
        if (file[cfile] == ':') {
            nwlnc++;
        }
    }
    int countf = nwlnc + 1;
    int pid;
    for (int tcfile = 0; tcfile < strlen(file); tcfile++) {
        if (file[tcfile] == ':') {
            char tcfilef[MAX_SIZE];
            strcpy(tcfilef, file);
            tcfilef[tcfile] = '\0';
            if (cparallel == 'P') {
                pid = fork();
                if (pid == 0) {
                    system(tcfilef);
                    while (waitpid(pid, &status, WNOHANG) == 0) {
                        // wait(&status);
                        kill(pid, SIGTERM);
                    }
                }
            } else {
                system(tcfilef);
                if (countf > 0) {
                    countf--;
                    loadbar(countf);
                }
            }
            for (int tcfileb = 0; tcfileb < tcfile; tcfileb++) {
                file[tcfileb] = ' ';
            }
        }
    }
    utbsinf(); printf("Finished %s process\n", func);
    printf("Exiting.\n");
    return 0; 
}
