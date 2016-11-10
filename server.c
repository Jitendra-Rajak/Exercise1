#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen,n;
     char buffer[256] ;
     char str[256];
     char str1[256];
     struct sockaddr_in serv_addr, cli_addr;
     strcpy(str,"bye\n");
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        while(1)
        {

                bzero(buffer,256);
                read(newsockfd,buffer,256);
                strcpy(str1,buffer);
                n=strcmp(str1,str);
                if(n!=0)
                {
                printf("message is: %s\n",buffer);
                bzero(buffer,256);
                }
                else
                {
                printf("last  message: %s\n",buffer);
                bzero(buffer,256);
                break;
                }

        }
     return 0;
}


