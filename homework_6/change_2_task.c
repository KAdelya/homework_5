#include <stdio.h>
#include <unistd.h>
#include <time.h>

static int createAndPrintProcess(int id, int old_id, int i, int number_of_generations, int number_of_descendants, int parent);

int main(int argc, char *argv[]) {
  int first_argv = *argv[1] - '0';
  int second_argv = *argv[2] - '0';
  return createAndPrintProcess(1, 1, 0, first_argv, second_argv, getppid());
}

static int createAndPrintProcess(int id, int old_id, int i, int number_of_generations, int number_of_descendants, int parent) {
  if (i <= number_of_generations) {
    for (int j = 0; j < number_of_descendants; j++) {
      pid_t pid = fork();
      if (pid == -1) {
        return 1;
      } else if (pid == 0) {
        old_id = id + 1;
        parent = getppid();
        return createAndPrintProcess(id * number_of_descendants + 1, old_id, i + 1,
                                number_of_generations, number_of_descendants, parent);
      }
      id++;
    }
    while(1) {
        time_t currentTime;
        time(&currentTime);
        struct tm *localTime = localtime(&currentTime);
        int hours = localTime -> tm_hour;
        int minutes  = localTime -> tm_min;
        int seconds = localTime -> tm_sec;
        struct timespec startTime;
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        int msec = startTime.tv_nsec / 1000000;
        usleep(old_id * 200 * 1000);
        int mseconds = 1000 * (hours * 60 * 60 + minutes * 60 + seconds) + msec;
        printf("Process number: %d, PID:%d, PPID:%d, msec: %d\n", old_id,
           getpid(), parent, mseconds);
    }
  }
  return 0;
}