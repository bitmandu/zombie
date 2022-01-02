/**
 * @file memory.h
 *
 * Shared memory.
 */

#pragma once

/**
 * Allocate shared memory.
 *
 * @param size Size (bytes)
 *
 * @return Pointer to memory on success, otherwise the value ((void *)
 * -1) is returned and errno is set.
 */
void *memory_alloc(size_t size);

/**
 * Free shared memory.
 *
 * @param addr Point to memory address
 * @param size Size (bytes)
 *
 * @return On success 0, otherwise -1 and errno is set.
 */
int memory_free(void *addr, size_t size);
