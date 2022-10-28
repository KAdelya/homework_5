#include <stdio.h>

int main (int arg, char *argv[]){
    int n = 0;
    int ch;
    int count_line = 0;
    FILE *fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("Ошибка в открытии файла");
        return -1;
    }
    if (argv[2] != NULL) {
        n = *argv[2];
    }
    n = n - '0';
    while ((ch = getc(fd)) != EOF){
        printf("%c", ch);
        if (ch == 10) {
            count_line++;
        }
        if (n != 0 && count_line == n){
            getc(stdin);
            count_line = 0;
        }
    }
    int file_close = fclose(fd);
    if (file_close != 0) {
        printf("Ошибка в закрытии файла");
    }
    return 0;
}
