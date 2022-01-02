/**
 * @file test.c
 *
 * Zombie process tests.
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "memory.h"

#define SLEEP 1 /**< Amount of time to wait for child (seconds) */

int test_zombie(void)
{
    pid_t *child_pid, pid;
    struct timespec dt = {.tv_sec = SLEEP};
    int result = 1;

    child_pid = memory_alloc(sizeof(*child_pid));
    if (child_pid == MEMORY_FAIL) {
        perror("memory_alloc");
        goto bail;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        goto cleanup;
    }

    if (pid == 0) {
        *child_pid = getpid();
        exit(EXIT_SUCCESS);
    }

    // give the child some time to exit; restart if interrupted by SIGCHLD
    while ((result = nanosleep(&dt, NULL)) == -1 && errno == EINTR)
        continue;

    if (result == -1) {
        perror("nanosleep");
        goto cleanup;
    }

    printf("child PID = %ld\n", (long)*child_pid);

    // if the child is a zombie kill() will succeed: return error (1)
    result = (kill(*child_pid, 0) == 0);

cleanup:
    memory_free(child_pid, sizeof(*child_pid));

bail:
    return result;
}
