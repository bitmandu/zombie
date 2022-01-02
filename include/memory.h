/**
 * @file memory.h
 *
 * Shared memory allocation.
 */

#pragma once

#define MEMORY_FAIL ((void *)-1)

/**
 * Allocate shared memory.
 *
 * @param size Number of bytes
 *
 * @return Pointer to memory on success, otherwise the value
 * MEMORY_FAIL is returned and errno is set.
 */
void *memory_alloc(size_t size);

/**
 * Free shared memory.
 *
 * @param addr Pointer to memory
 * @param size Number of bytes
 *
 * @return On success 0, otherwise -1 and errno is set.
 */
int memory_free(void *addr, size_t size);
