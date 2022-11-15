#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void getPid(pid_t pid) {
    int hours, minutes, seconds;
    time_t current_time;
    time(&current_time);
    struct tm *localTime = localtime(&current_time);
    struct timespec startTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    if (pid == 0) {
        printf("Это Дочерний процесс, его pid=%d, time: %d:%d:%d:%ld\n", getpid(), localTime -> tm_hour, localTime -> tm_min, localTime -> tm_sec, startTime.tv_nsec / 1000000);
        printf("А pid его Родительского процесса=%d, time: %d:%d:%d:%ld\n", getppid(), localTime -> tm_hour, localTime -> tm_min, localTime -> tm_sec, startTime.tv_nsec / 1000000);
    } else if (pid > 0)
        printf("Это Родительский процесс pid=%d, time: %d:%d:%d:%ld\n", getpid(), localTime -> tm_hour, localTime -> tm_min, localTime -> tm_sec, startTime.tv_nsec / 1000000);
    else {
        printf("Ошибка вызова fork, потомок не создан\n");
        return;
    }

}

int main() {
    pid_t pid_1, pid_2;
    pid_1 = fork();
    getPid(pid_1);
    if (pid_1 != 0) {
        pid_2 = fork();
        getPid(pid_2);
    }
    system("ps -x");
    return 0;
}