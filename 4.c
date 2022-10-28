#include <stdio.h>

int main (int arg, char *argv[]){
    int ch;
    FILE *first_file = fopen(argv[1], "r");
    FILE *second_file = fopen(argv[2], "a");
    if (first_file == NULL) {
        printf("Ошибка в открытии первого файла");
        return -1;
    }
    if (second_file == NULL) {
        printf("Ошибка в открытии второго файла");
        return -1;
    }
    while ((ch = getc(first_file)) != EOF){
        fputc(ch, second_file); 
    }
    int first_file_close = fclose(first_file);
    int second_file_close = fclose(second_file);
    if (first_file_close != 0) {
        printf("Ошибка в закрытии первого файла");
    }
    if (second_file_close != 0) {
        printf("Ошибка в закрытии второго файла");
    }
    return 0;
}
