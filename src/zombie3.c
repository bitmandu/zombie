/**
 * zombie3.c
 *
 * Handle zombie processes from fork() using waitpid().
 */

#include <sys/wait.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "memory.h"

static pid_t *child_pid;

static void handler(int signum)
{
    pid_t pid;
    int errno_ = errno;

    errno = 0;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        ;

    if (pid == -1 && errno != ECHILD)
        _exit(1);

    errno = errno_;
}

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

    action.sa_handler = handler;
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

    while ((result = nanosleep(&dt, NULL)) == -1 && errno == EINTR)
        continue;

    if (result == -1)
        perror("nanosleep");

    printf("child PID = %ld\n", (long)*child_pid);

    // if the child is a zombie kill() will succeed: return error (1)
    result = (kill(*child_pid, 0) == 0);

error_memory:
    memory_free(child_pid, sizeof(*child_pid));

error:
    return result;
}
