/**
 * @file zombie2.c
 *
 * Handle zombie processes from fork() using SIG_NOCLDWAIT flag.
 */

#include <signal.h>
#include <stdio.h>

#include "test.h"

int main(void)
{
    struct sigaction action = {.sa_flags = SA_NOCLDWAIT};
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGCHLD, &action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    return test_zombie();
}
