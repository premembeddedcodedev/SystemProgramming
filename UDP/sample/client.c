#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MYPORT 4950
#define MAXBUFLEN 500
int main(int argc, char *argv[])

{
        int sockfd;
        struct sockaddr_in my_addr;
        struct sockaddr_in their_addr;
        int addr_len, numbytes;
        char buf[MAXBUFLEN];
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
                perror("Server-socket() sockfd error lol!");
                exit(1);
        } else
                printf("Server-socket() sockfd is OK...\n");
        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(MYPORT);
        my_addr.sin_addr.s_addr = INADDR_ANY;
        memset(&(my_addr.sin_zero), '\0', 8);
        if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
                perror("Server-bind() error lol!");
                exit(1);
        } else
                printf("Server-bind() is OK...\n");

        addr_len = sizeof(struct sockaddr);

        while(1) {
                if((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
                {
                        perror("Server-recvfrom() error lol!");
                        exit(1);
                } else {
                        printf("Server-Waiting and listening...\n");
                        printf("Server-recvfrom() is OK...\n");
                }
                printf("Server-Got packet from %s\n", inet_ntoa(their_addr.sin_addr));
                printf("Server-Packet is %d bytes long\n", numbytes);
                buf[numbytes] = '\0';
                printf("Server-Packet contains \"%s\"\n", buf);
        }
        if(close(sockfd) != 0)
                printf("Server-sockfd closing failed!\n");
        else
                printf("Server-sockfd successfully closed!\n");
        return 0;

}
