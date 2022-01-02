/**
 * @file memory.c
 *
 * Shared memory allocation.
 */

#include <sys/mman.h>
#include <sys/stat.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void *memory_alloc(size_t size)
{
    int fd;
    const char name[] = "/zombie";
    void *addr = MAP_FAILED;

    if ((fd = shm_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        perror("shm_open");
        goto error;
    }

    if (ftruncate(fd, size) == -1) {
        perror("ftruncate");
        goto error_shm;
    }

    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

error_shm:
    if (shm_unlink(name) == -1)
        perror("shm_unlink");
error:
    return addr;
}

int memory_free(void *addr, size_t size)
{
    return munmap(addr, size);
}
