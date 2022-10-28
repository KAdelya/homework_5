#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void print_content_in_dir(DIR *folder) {
    struct dirent *de;
    while (de = readdir(folder))
        printf("%s\n", de->d_name);
}

int main(int argc, char *argv[]) {
    DIR *current_dir;
    DIR *argv_dir;
    if ((current_dir = opendir(".")) == NULL ) {
        printf("Ошибка в открытии текущего каталога\n");
        return -1;
    }
    if ((argv_dir = opendir(argv[1])) == NULL ) {
        printf("Ошибка в открытии каталога, прописанного в параметрах запуска программы\n");
        return -1;
    }
    printf("%s\n", "Текущая директория:");
    print_content_in_dir(current_dir);
    printf("Директория %s:\n", argv[1]);
    print_content_in_dir(argv_dir);
    int current_dir_close = closedir(current_dir);
    int argv_dir_close = closedir(argv_dir);
    if (current_dir_close != 0) {
        printf("Ошибка в закрытии текущего каталога\n");
    }
    if (argv_dir_close != 0) {
        printf("Ошибка в закрытии каталога, прописанного в параметрах запуска программы\n");
    }
    return 0;
}
