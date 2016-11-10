#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char str[256]="bye\n";
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(argv[1]);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
        while(1)
        {
                printf("Please enter the message: ");
                bzero(buffer,256);
                fgets(buffer,256,stdin);
                n=strcmp(buffer,str);
                if(n!=0)
                {
                write(sockfd,buffer,strlen(buffer));
                bzero(buffer,256);
                }
                else
                {
                 write(sockfd,buffer,strlen(buffer));
                 bzero(buffer,256);
                 break;
                }

        }
    return 0;
}

