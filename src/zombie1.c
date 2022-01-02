/**
 * zombie1.c
 *
 * Handle zombie processes from fork() by SIG_IGN.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "memory.h"

static pid_t *child_pid;

int main(void)
{
    pid_t pid;
    struct sigaction action = {0};
    struct timespec dt = {.tv_sec = 1};
    int result = 1;

    child_pid = memory_alloc(sizeof(*child_pid));
    if (child_pid == (void *)-1) {
        perror("memory_alloc");
        goto error;
    }

    // equivalent to: signal(SIGCHLD, SIG_IGN);
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGCHLD, &action, NULL) == -1) {
        perror("sigaction");
        goto error_memory;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        goto error_memory;
    }

    if (pid == 0) {
        *child_pid = getpid();
        exit(EXIT_SUCCESS);
    }

    if (nanosleep(&dt, NULL) == -1) {
        perror("nanosleep");
        goto error_memory;
    }

    printf("child PID = %ld\n", (long)*child_pid);

    // if the child is a zombie kill() will succeed: return error (1)
    result = (kill(*child_pid, 0) == 0);

error_memory:
    memory_free(child_pid, sizeof(*child_pid));

error:
    return result;
}
