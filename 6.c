#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void to_print_file_info(int argc, char *argv[], int count_view_dir_and_files) {
    struct stat fileStat;
    stat(argv[2], &fileStat);
    char *path = realpath(argv[2], NULL);
    printf("Полный путь к файлу %s: %s\n", argv[2], path);
    printf("Имя файла: %s\n", argv[2]);
    printf("Размер файла: %ld bytes\n", fileStat.st_size);
    printf("Время последнего изменения файла: %s", ctime(&fileStat.st_mtime));
    printf("Права доступа: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("Номер индексного дескриптора: %ld\n", fileStat.st_ino);
    printf("Общее количество просмотренных каталогов и файлов: %d\n", count_view_dir_and_files);
}

void searchInDirectory(char *dirname, char *filename, int argc, char *argv[], int count_view_dir_and_files){
    DIR *dir;
    struct dirent *de;
    dir = opendir(dirname);
    chdir(dirname);
    while((de = readdir(dir)) != NULL) {
        count_view_dir_and_files++;
        if(de -> d_type == 4) {
            if(strcmp(de -> d_name, ".") == 0 || strcmp(de -> d_name, "..") == 0) {
                continue;
            }
            searchInDirectory(de -> d_name, filename, argc, argv, count_view_dir_and_files);
        }
        else {
            if (strcmp(de -> d_name, filename) == 0) {
               to_print_file_info(argc, argv, count_view_dir_and_files);
               break;
            }
        }
    }
    chdir("..");
    closedir(dir);
}

int main(int argc, char *argv[]) {
    searchInDirectory(argv[1], argv[2], argc, argv, 0);
    return 0;
}
