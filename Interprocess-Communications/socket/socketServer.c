#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


#define SOCK_PATH "mySocket.server"
#define DATA "Hello from serverrr"

int main(void) {

    struct sockaddr_un serverAdd;
    struct sockaddr_un clientAdd;
    int serverSock, clientSock, len, rc;
    int bytesRec = 0;

    char buf[256];
    int backlog = 10; //space for queue
    memset(&serverAdd, 0, sizeof(struct sockaddr_un));
    memset(&clientAdd, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);

    //creating unix domain stream socket
    serverSock = socket(AF_UNIX, SOCK_STREAM, 0); //serverSock = file descriptor for the new socket
    if (serverSock == -1){
        perror("Error creating server socket: "); exit(1);
    }
    //setting up server address by giving it a file path to bind to
    serverAdd.sun_family = AF_UNIX;   
    strcpy(serverAdd.sun_path, SOCK_PATH); 
    len = sizeof(serverAdd);

    unlink(SOCK_PATH);

    if (((rc = bind(serverSock, (struct sockaddr*)&serverAdd, len)) == -1)){
        perror("Bind error: ");
        close(serverSock);
        exit(1);
    }

    //socket binded to the file path
    //now we will listen to client socket
    if ((rc = listen(serverSock, backlog)) == -1){
        perror("Listen error: ");
        close(serverSock);
        exit(1);
    }
    printf("Socket is listening........\n");

    //accepting a connection
    clientSock = accept(serverSock, (struct sockaddr*) &clientAdd, &len);
    if (clientSock == -1){
        perror("Accept error: ");
        close(serverSock); close(clientSock); exit(1);
    }
    printf("accepted!\n");
    //getting name of connected socket
    len = sizeof(clientAdd);
    rc = getpeername(clientSock, (struct sockaddr *) &clientAdd, &len);
    if (rc == -1){
        perror("Getting peername error: ");
        close(serverSock);
        close(clientSock);
        exit(1);
    }
    else {
        printf("Client socket filepath: %s\n", clientAdd.sun_path);
    }

    //reading and printing data coming from client
    // ssize_t recv(int socket, void *buffer, size_t length, int flags);
    // The recv() function shall receive a message from a connection-mode or connectionless-mode
    //    socket. It is normally used with connected sockets because it does not permit the  appli‐
    //    cation to retrieve the source address of received data.

    //    The recv() function takes the following arguments:

    //    socket    Specifies the socket file descriptor.

    //    buffer    Points to a buffer where the message should be stored.

    //    length    Specifies the length in bytes of the buffer pointed to by the buffer argument.

    //    flags     Specifies  the type of message reception. Values of this argument are formed by
    //              logically OR'ing zero or more of the following values: MSG_PEEK, MSG_OOB, MSG_WAITALL

    printf("waiting to read...\n");
    bytesRec = recv(clientSock, buf, sizeof(buf), 0);
    if (bytesRec == -1) {
        perror("Receive error: ");
        close(serverSock); close(clientSock); exit(1);
    } else {
        printf("Data received = %s\n", buf);
    }

    //now sending data back to the connected host[client]

    memset(buf, 0, 256);
    strcpy(buf, DATA);
    printf("sending data.....\n");
    if ((rc = send(clientSock, buf, strlen(buf), 0)) == -1){
        perror("Send error: ");
        close(serverSock);
        close(clientSock);
        exit(1);
    } else {
        printf("data sent\n");
    }

    //closing sockets and the end
    close(serverSock);
    close(clientSock);
    return 0;
}