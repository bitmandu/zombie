/**
 * @file zombie3.c
 *
 * Handle zombie processes using waitpid().
 */

#include <sys/wait.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "test.h"

static void handler(int signum)
{
    pid_t pid;
    int errno_ = errno;

    (void)signum;
    errno = 0;

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        ;

    if (pid == -1 && errno != ECHILD)
        _exit(1);

    errno = errno_;
}

int main(void)
{
    struct sigaction action = {.sa_handler = handler};
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGCHLD, &action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    return test_zombie();
}
