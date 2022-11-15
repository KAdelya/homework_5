#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void createProcesses(int number_of_generations, pid_t parent_pid, int number_of_descendants, struct timespec startTime) {
        int i = 0;
        if (number_of_generations != 0) {
                while (i < number_of_descendants) {
                clock_gettime(CLOCK_MONOTONIC, &startTime);
                        pid_t child_pid = fork();
                        i++;
                        sleep(3);
                        if (child_pid == 0) {
                          printf("pid: %d, ppid: %d, msec: %ld\n", getpid(), parent_pid, startTime.tv_nsec / 1000000);
                        }
                        if (parent_pid != getpid()) {
                          number_of_generations--;              
                                createProcesses(number_of_generations, getpid(), number_of_descendants, startTime);
                                break;
                        }
                }
        }
}

int main(int argc, char *argv[]) {
    struct timespec startTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    pid_t pid = getpid();
	printf("Родитель: pid: %d, ppid: %d, msec: %ld\n", pid, getppid(), startTime.tv_nsec / 1000000);
	createProcesses(atoi(argv[1]), getpid(), atoi(argv[2]), startTime);
}