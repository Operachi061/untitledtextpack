#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char table[999999999];
void save() {
   char name[999];
   printf("Save as: ");
   scanf("%s", &name);
   char *file = name;
   FILE *fp = fopen(file, "w");
   fprintf(fp, table);
   fclose(fp);
   command();
}
void help() {
   printf("e - exit\n"
          "t - type\n"
          "s - save\n"
         //  "o - open\n"
          "h - help\n");
   command();
}
// void open() {
   // char name[999];
   // printf("File: ");
   // scanf("%s", &name);
   // return 1;
// }
void command() { 
   char utw;
   printf("utw> ");
   scanf("%s", &utw);
   if (utw == ' ') {
      command();
   } else {
      if (utw == 'e') {
         exit(1);
      } else if (utw == 't') {
         window();
      } else if (utw == 's') {
         save();
      } else if (utw == 'h') {
         help();
      // } else if (utw == 'o') {
         // open();
      } else {
         printf("Not found: %c\n", utw);
         command();
      }
   }
}
void window() {
   system("clear");
   while(1) {
      static int num = 1;
      char column[999] = "";
      printf("%d ", num++);
      // if (open == 1) {
         // printf("File opened!\n");
      // } else {
         // NULL;
      // }
      scanf("%c", &column);
      fgets(column, sizeof column, stdin);
      if (getc(stdin) == 27) {
         command();
      } else if (column[0] == "\r\n") {
         strcat(table, column);
         window();
      } else if (column[0] == NULL) {
         strcat(table, column);
         window();
      } else {
         strcat(table, column);
      }
   }
}
int main() {
   system("clear");
   printf("Welcome to Untitled Text Writer!\n"
          "For help write \"h\"\n");
   printf("utw> \r");
   command();
}