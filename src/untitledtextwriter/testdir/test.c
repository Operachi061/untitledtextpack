#include <stdio.h>
main() {
   /* static int i;
    char table[999];
    char column[999];
    for (i = 0; i < 3; i++) {
        printf("Write text: ");
        scanf("%c", &column);
        fgets(column, sizeof column, stdin);
        char firstl[2] = {0};
        firstl[1] = column[1];
        strcat(table, firstl);
        strcat(table, column);
    }
   // while (table != NULL) {
    printf("%c\n", table);
    char *file = "test.txt";
    FILE *fp = fopen(file, "w");
    fprintf(fp, table);
    fclose(fp); 
 //  } */
  void open() {
    printf("Open\n");
    return 1;
  }
  void window() {
    open;
    if (open == 1) {
      printf("Hi!\n");
    } else {
      printf("%d\n", open);
    }
  }
  window();
}