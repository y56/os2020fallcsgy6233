#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>

#define SERV_TCP_PORT 8000 /* server's port */

int main(int argc, char * argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    char * serv_host = "localhost";
    // char * serv_host = "127.0.0.1";
    struct hostent * host_ptr;
    int port;
    int buff_size = 0;
    int n;
    int d;
    char tmp_k_d[12];
    unsigned int microseconds;

    srand(time(0)); 

    if (argc != 3)
        perror("exactly 2 inputs, n and d");
        
    n = atoi(argv[1]);
    d = atoi(argv[2]);
    
    port = SERV_TCP_PORT;

    
    for (int k = 0; k < (n + 1); k++)
        {
            printf("k: %d\n", k);

            /* get the address of the host */
            if ((host_ptr = gethostbyname(serv_host)) == NULL) {
                perror("gethostbyname error");
                exit(1);
            }

            if (host_ptr -> h_addrtype != AF_INET) {
                perror("unknown address type");
                exit(1);
            }

            bzero((char * ) & serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr =
                ((struct in_addr * ) host_ptr -> h_addr_list[0]) -> s_addr;
            serv_addr.sin_port = htons(port);

            /* open a TCP socket */
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("can't open stream socket");
                exit(1);
            }

            /* connect to the server */
            if (connect(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
                perror("can't connect to server");
                exit(1);
            }

            if (k == n) {
                snprintf(tmp_k_d, 12, "%d", -1);
            } else {
                snprintf(tmp_k_d, 12, "%d", k * d);
            }

            /* write a message to the server */
            write(sockfd, tmp_k_d, sizeof(tmp_k_d));

            close(sockfd);

            microseconds = rand() % 1000000;
            printf("wait in microseconds: %d\n", microseconds);
            usleep(microseconds);
        }
}
