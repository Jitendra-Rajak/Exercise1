/***********************************************************
 *This file is a part of a simple client server application.
 **********************************************************/

/**
 *@file 	client.c
 *@breif
 *This file wil be used for connecting to the server and sending
 *the data to the server.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    /* ---------- INITIALIZING VARIABLES ---------- */
    int sockfd;/*!< File descriptor to store the values returned by the socket system call and the accept system call. */
    int  portno,/*!< NOTE that the port number is same for both client and server. */
    int  n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];/*!< client reads characters from the socket connection into a dynamic variable (buffer). */
    char str[256]="bye\n";
    portno = atoi(argv[2]);
     //! Socket function
    /*!
        * AF_INET: address domain of the socket.
        * SOCK_STREAM: Type of socket. a stream socket in which characters are read in a continuous stream (TCP).
        * Third is a protocol argument: should always be 0. The OS will choose the most appropiate protocol.
        * This will return a small integer and is used for all references to this socket. If the socket call fails, 
          it returns -1.
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);/*!< Socket function creates a new socket.It takes three arguments. */
    server = gethostbyname(argv[1]);
    bzero((char *) &serv_addr, sizeof(serv_addr));
     /*! 
        * The variable serv_addr is a structure of sockaddr_in. sin_family contains a code for the address family. 
        * It should always be set to AF_INET.
        * htons() converts the port number from host byte order to a port number in network byte order.
    */
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    /*-----Once it reaches here,the client can send a message first-----*/
    /*! 
        * Once the client presses "bye" to end the connection,the loop will break and it will close the server 
          socket connection and the client connection.
    */
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

