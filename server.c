/*************************//***
*A Server Program
******************************/
/**
 *This file is a part of a simple client server application where all the 
 *input provided by the client will be visible at the server end. Once the
 *client will say bye both the client and server will be terminated.
 **/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
     /* ---------- INITIALIZING VARIABLES ---------- */
     int sockfd, newsockfd;/*!< sockfd and newsockfd are two file descriptors. */
     int  portno, clilen,n;
     char buffer[256] ;/*!< server reads characters from the socket connection into a dynamic variable (buffer). */
     char str[256];
     char str1[256];
     struct sockaddr_in serv_addr, cli_addr;
     strcpy(str,"bye\n");
     //! Socket function
    /*!
        * AF_INET: address domain of the socket.
        * SOCK_STREAM: Type of socket. a stream socket in which characters are read in a continuous stream (TCP).
        * Third is a protocol argument: should always be 0. The OS will choose the most appropiate protocol.
        * This will return a small integer and is used for all references to this socket. If the socket call fails, 
          it returns -1.
    */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);//socket() function creates a new socket.
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));/*!< The bind() system call binds a socket to an address. */
     //! listen() system call	
    /*! 
        \ The listen system call allows the process to listen on the socket for connections. 
        \ The program will be stay idle here if there are no incomming connections.
        \ The first argument is the socket file descriptor,and the second is the size for the number of clients 
          i.e the number of connections that the server can handle while the process is handling a particular connection.
        \ The maximum size permitted by most systems is 5.
    */ 
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     //! accept() system call
    /*!
        \ The accept() system call causes the process to block until a client connects to the server. Thus, it wakes 
          up the process when a connection from a client has been successfully established. 
        \ It returns a new file descriptor,and all communication on this connection should be done using the new file descriptor.
        \ The second argument is a reference pointer to the address of the client on the other end of the connection.
        \ The third argument is the size of this structure.
    */
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     /*! 
            \ Note that we would only get to this point after a client has successfully connected to our server. 
            \ This reads from the socket. Note that the read() will block until there is something to read 
              in the socket, i.e. after the client has executed a write().
            \ It will read the total number of characters in the socket or size of buffer.
        */
     /*! 
            Once the client presses "bye" to end the connection,the loop will break and it will close the server 
            socket connection and the client connection.
        */
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


