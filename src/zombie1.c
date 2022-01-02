/**
 * @file zombie1.c
 *
 * Handle zombie processes using SIG_IGN.
 */

#include <signal.h>
#include <stdio.h>

#include "test.h"

int main(void)
{
    // equivalent to: signal(SIGCHLD, SIG_IGN);
    struct sigaction action = {.sa_handler = SIG_IGN};
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGCHLD, &action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    return test_zombie();
}
