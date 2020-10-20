#include <sys/mman.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <fcntl.h>       /* For O_* constants */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MSGSIZE 16 

int main(int argc, char **argv)
{
    int n; 
    int d;
    int k;
    int pid;
    int p[2];
    char inbuf[MSGSIZE];
    int nbytes;
    char kd[MSGSIZE];   

    n = atoi(argv[1]);
    d = atoi(argv[2]);
    
    if (pipe(p) < 0) exit(1);

    pid = fork();

    if (pid > 0) 
    {
        // Luke, I am your father
        wait(NULL); // wait child to finish
        close(p[1]);
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) 
        {
            printf("%s \n", inbuf);
        }
        if (nbytes < 0) exit(1);
        printf("Finished reading\n"); 
        return 0;
    } 
    else if (pid == 0)
    {
        // Luke: Noooooooo~!
        close(p[0]);
        for (k = 0; k < n; k++)
        {
            sprintf(kd, "%d", k*d);
            write(p[1], kd, MSGSIZE);
        }
        exit(0);
    } else {
        return -1;
    }
    return 0;
}

