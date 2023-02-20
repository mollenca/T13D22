#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void menu();

void read_f(char *fname, int *flag);
void addinfo_f(char *fname, int *flag);
void path_f(char *fname);
void path_check(char *fname, int *flag);
void shift(int *shiftt);
void finder(char *dir_path, int shift);
void caesar(char *cs_in, char *cs_out, int shift);
void flag_checker(int flag);

int main() {
    menu();
    return 0;
}

void menu() {
    int signal = 0, s_res = 0, flag = 0, shift1;
    s_res = scanf("%d", &signal);
    char fname[256];
    while (signal != -1) {
        if (s_res == 1 && (signal == 1 || signal == 2 || signal == 3)) {
            switch (signal) {
                case 1: {
                    path_f(fname);
                    path_check(fname, &flag);
                    read_f(fname, &flag);
                    flag_checker(flag);
                    break;
                }
                case 2: {
                    addinfo_f(fname, &flag);
                    read_f(fname, &flag);
                    flag_checker(flag);
                    break;
                }
                case 3: {
                    path_f(fname);
                    shift(&shift1);
                    finder(fname, shift1);
                    break;
                }
                default:
                    printf("n/a\n");
                    break;
            }
        } else {
            printf("n/a\n");
            scanf("%*[^\n]");
        }
        s_res = scanf("%d", &signal);
    }
}

void flag_checker(int flag) {
    if (flag == 1) printf("n/a\n");
}

void path_f(char *fname) { scanf("%s", fname); }

void shift(int *shiftt) { scanf("%d", shiftt); }

void path_check(char *fname, int *flag) {
    int sn = strlen(fname);
    if (fname[sn - 1] == 't' && fname[sn - 2] == 'x' && fname[sn - 3] == 't' && fname[sn - 4] == '.')
        *flag = 0;
    else
        *flag = 1;
}

void read_f(char *fname, int *flag) {
    FILE *ptrf = fopen(fname, "r");
    char ch;
    if (ptrf != NULL) {
        ch = fgetc(ptrf);
        if (ch != EOF) {
            while (ch != EOF) {
                putchar(ch);
                ch = fgetc(ptrf);
            }
            putchar('\n');
        } else {
            *flag = 0;
            printf("n/a\n");
        }
    } else {
        *flag = 1;
    }
    fclose(ptrf);
}

void addinfo_f(char *fname, int *flag) {
    char ch, ch1;
    if (*flag != 1) {
        FILE *ptrf = fopen(fname, "a");
        if (ptrf != NULL) {
            ch1 = getchar();
            while ((ch = getchar()) != '\n') {
                fputc(ch, ptrf);
            }
        } else {
            *flag = 1;
            ch1 = getchar();
            ch1 = ' ';
            while (ch1 != '\n') {
                ch1 = getchar();
            }
        }
        fclose(ptrf);
    } else {
        ch1 = getchar();
        ch1 = ' ';
        while (ch1 != '\n') {
            ch1 = getchar();
        }
    }
}

void finder(char *dir_path, int shift) {
    char *ptr1, *ptr2, *cs_in, *clean_in;
    char dir_path_cp[256], dir_path_cp1[256];
    DIR *dr;
    int rn;
    struct dirent *drr;
    dr = opendir(dir_path);
    if (dr != NULL) {
        while ((drr = readdir(dr)) != NULL) {
            ptr1 = strtok(drr->d_name, ".");
            ptr2 = strtok(NULL, ".");
            if (ptr2 != NULL) {
                rn = strcmp(ptr2, "c");
                if (rn == 0) {
                    cs_in = strcat(ptr1, ".c");
                    strcpy(dir_path_cp, dir_path);
                    cs_in = strcat(dir_path_cp, cs_in);
                    caesar(cs_in, ptr1, shift);
                    remove(cs_in);
                    rename(ptr1, cs_in);
                }
                rn = strcmp(ptr2, "h");
                if (rn == 0) {
                    clean_in = strcat(ptr1, ".h");
                    strcpy(dir_path_cp1, dir_path);
                    clean_in = strcat(dir_path_cp1, clean_in);
                    FILE *cl_aim = fopen(clean_in, "wb");
                    fclose(cl_aim);
                }
            }
        }
        closedir(dr);
    } else {
        printf("n/a\n");
    }
}

void caesar(char *cs_in, char *cs_out, int shift) {
    FILE *file1, *file2;
    file1 = fopen(cs_in, "r");
    file2 = fopen(cs_out, "w");
    char ch;
    ch = getc(file1);
    while (ch != EOF) {
        ch = ((ch + shift) % 125);
        fputc(ch, file2);
        ch = getc(file1);
    }
    fclose(file1);
    fclose(file2);
}
