#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>       /* For O_* constants */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd = shm_open("posixsm", O_RDONLY, 0666);
    ftruncate(fd, 0x400000);
    
    int *p = mmap(NULL, 0x400000,
                  PROT_READ, MAP_SHARED, fd, 0);  
    printf("read: %d, %d\n", p[0], p[1]);
    
    munmap(p, 0x400000);
    
    return 0;
}
