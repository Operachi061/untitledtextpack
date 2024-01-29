#include <stdio.h>
#include <argp.h>
#include <string.h>

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define CYAN    "\033[0;36m"
#define END     "\033[0;0m"

#define MAX_SIZE 999

int i = 0;
int nmbcheck = 0;
char *func;
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
        default:
            return ARGP_ERR_UNKNOWN;
    }
}
static struct argp argp = { options, parse_opt, NULL, doc };
void utbsinf() { printf("%sUtbs -> %s", BLUE, END); }
int main(int argc, char **argv) {
    argp_parse (&argp, argc, argv, 0, 0, 0);
    printf("You started utbs.\n");
    utbsinf(); printf("Preparing process\n");
    printf("%sUtbsource file check -> %s", CYAN, END);
    FILE *fp = fopen(path, "r");
    FILE *fpt = fopen(path, "r");
    if (fp == NULL) {
        printf("%snot found%s\n", RED, END);
        printf("Exiting.\n");
        return 0;
    } else {
        printf("%sfound%s\n", GREEN, END);
    }
    printf(" Finding functions in parser\n");
    if (func == NULL) {
        printf("  FUNCTIONS NOT FOUND\n");
        printf("Exiting.\n");
        return 0;
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
            printf("%s[ LINE: %d ]%s %s\n", RED, i, END, "NOT FOUND");
            nmbcheck = 1;
        } else {
            position[strlen(chk)] = '\0';
            printf("%s[ LINE: %d ]%s \'%s\' %s->%s %sfound%s\n", RED, i, END, position, CYAN, END, GREEN, END);
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
        file[x] = '\t';
    }
    for (int y = 0; y < strlen(file); y++) {
        if (file[y] == '>') {
            file[y] = '\0';
        }
    }
    file[strlen(file) - 1] = '\0';
    utbsinf(); printf("Starting %s process\n", func);
    system(file);
    printf("Exiting.\n");
    return 0;
}