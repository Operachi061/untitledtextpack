#include <stdio.h>
#include <sys/types.h>
main() {
    FILE *portlist = fopen("./sources/portlist", "a+");
    while (fgets(print, 100, portlist) != NULL) {
          execl("/usr/bin/hostname", NULL, NULL), execl("/usr/bin/pwd", NULL, NULL), "%s-%s %s $ ");
    }
}
