#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *fd = fopen(argv[1],"w");
    int input;
    char file_write;
    if (fd == NULL) {
        printf("Ошибка в открытии файла\n");
        return -1;
    }
    while (1) {
      input = getc(stdin);
      if (input == 6) {
          break;
        }
        file_write = fputc(input, fd);
        if (!file_write) {
            printf("Символ '%c' не может быть записан в файл\n", file_write);
            return 1;
        }
    }
    if (fclose(fd) != 0) {
        printf("Ошибка в закрытии файла\n");
    }
    return 0;
}
