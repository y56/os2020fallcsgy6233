#include <sys/mman.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <fcntl.h>       /* For O_* constants */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MSGSIZE 256

int main(int argc, char **argv)
{
    int pid;
    int p_p2c[2]; // pipe, parent to child
    int p_c2p[2]; // pipe, child to parent
    char inbuf_c2p[MSGSIZE];
    char inbuf_p2c[MSGSIZE];
    int nbytes_c2p;
    int nbytes_p2c;

    char c_R[MSGSIZE];   
    char parent_user_input[MSGSIZE];

    volatile int p2cOK = 0;

    
    if (pipe(p_p2c) < 0) exit(1);
    if (pipe(p_c2p) < 0) exit(1);

    pid = fork();

    if (pid > 0) 
    {
        // parent reads
        int a=1;
        while (strcmp(inbuf_c2p, "R")!=0 && a) {
        	printf("%s\n", "parent start reading from child\n");
	        close(p_c2p[1]);
	        while ((nbytes_c2p = read(p_c2p[0], inbuf_c2p, 128)) > 0 && a) 
	        {
	        	printf("%s\n", "parent reading from child\n");
	        	a=0;
	            printf(">>>> %s\n", inbuf_c2p);
	            
	        }
	        if (nbytes_c2p < 0) exit(1);
	        // *inbuf_c2p = "X"; // if not "R", will keep reading
            printf("%s\n", "parent finish reading from child\n");
	    }
	    printf("%s\n", "paren got child's R\n");

        printf("user plz type:");
	    scanf("%255s", parent_user_input); // truncated
	    printf("your input:   %s\n", parent_user_input);

	    // parent start sending to child
	    close(p_p2c[0]);
        //sprintf(kd, "%d", k*d);
        int c;
        srand(time(NULL));
        c= rand()%2;
        printf("%d\n", c);
        sleep(c);
        write(p_p2c[1], parent_user_input, MSGSIZE);
        p2cOK=1;


        


        wait(NULL); // wait child to finish

         
        return 0;
    } 
    else if (pid == 0)
    {
        // Luke: Noooooooo~!


        // child writes 'R'
        close(p_c2p[0]);
        printf("%s\n", "child sending R\n");
        sprintf(c_R, "%s", "R");
        write(p_c2p[1], c_R, MSGSIZE);

        printf("ch start reading\n"); 
        close(p_p2c[1]);
        int b =1;
        while ((nbytes_p2c = read(p_p2c[0], inbuf_p2c, 128)) > 0 && b) 
        {
        	printf("ch reading\n"); 
            printf("%s \n", inbuf_p2c);
            b= 0;
        }
        if (nbytes_p2c < 0) exit(1);
        printf("ch Finished reading\n"); 




        exit(0);
    } else {
        return -1;
    }
    return 0;
}

