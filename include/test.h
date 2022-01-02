/**
 * @file test.h
 *
 * Zombie process tests.
 */

#pragma once

/**
 * Test whether a zombie process is handled properly.
 *
 * @return If no zombie process is created (i.e., it is handled
 * properly) return 0, otherwise 1.
 */
int test_zombie(void);
