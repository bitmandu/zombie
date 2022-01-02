/**
 * @file zombie0.c
 *
 * Don't handle zombie processes.
 */

#include "test.h"

int main(void)
{
    return !test_zombie();
}
