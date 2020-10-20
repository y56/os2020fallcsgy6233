#include <sys/mman.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <fcntl.h>       /* For O_* constants */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int n = 5; 
    int d = 2;
    int k;
    int pid;
    int fd = shm_open("posixsm", O_CREAT | O_RDWR, 0666);
    int *p = mmap(NULL, 0x400000,
                  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ftruncate(fd, 0x400000);
    pid = fork();

    if (pid > 0) 
    {
        // Luke, I am your father
        wait(NULL); // wait child to finish
        for (k = 0; k < n; k++)
        {
            printf("%d ",p[k]);
        }
        printf("\n");
        munmap(p, 0x400000); // release shared mem
    } 
    else if (pid == 0)
    {
        // Luke: Noooooooo~!
        for (k = 0; k < n; k++)
        {
            p[k] = k * d;
        }
    } else {
        return -1;
    }
    return 0;
}

