#ifndef MODULE_IO_H
#define MODULE_IO_H

#include <stdio.h>

int saveScan(int *input);
char *charInput(int flag);
char *charInputFromFile(FILE *f);
int charInputInFile(FILE *f, char *write);
void str_output(char *str);
char *s21_strcat(char *str1, char *str2);

#endif