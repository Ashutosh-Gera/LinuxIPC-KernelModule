#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_PATH "mySocket.server"
#define CLIENT_PATH "mySocket.client"
#define DATA "Hello from client"

int main(void) {

    int clientSock, rc, len;
    struct sockaddr_un serverAdd; 
    struct sockaddr_un clientAdd; 
    char buf[256];
    memset(&serverAdd, 0, sizeof(struct sockaddr_un));
    memset(&clientAdd, 0, sizeof(struct sockaddr_un));

    clientSock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSock == -1) {
        perror("Socket error: ");
        exit(1);
    }

    //we will do similar steps as we did on server side
    clientAdd.sun_family = AF_UNIX;
    strcpy(clientAdd.sun_path, CLIENT_PATH);
    len = sizeof(clientAdd);

    unlink(CLIENT_PATH);    

    if ((rc = bind(clientSock, (struct sockaddr*) &clientAdd, len)) == -1){
        perror("connect error!");
        close(clientSock);
        exit(1);
    }

    serverAdd.sun_family = AF_UNIX;
    strcpy(serverAdd.sun_path, SERVER_PATH);
    rc = connect(clientSock, (struct sockaddr *) &serverAdd, len);
    if(rc == -1){
        perror("connect error: ");
        close(clientSock);
        exit(1);
    }

    //send data to server socket
    strcpy(buf, DATA);                 
    printf("Sending data...\n");
    rc = send(clientSock, buf, strlen(buf), 0);
    if (rc == -1) {
        perror("Send error: ");
        close(clientSock);
        exit(1);
    }   
    else {
        printf("Data sent!\n");
    }

    //read data received from server and print it
    printf("Waiting to recieve data...\n");
    memset(buf, 0, sizeof(buf));
    rc = recv(clientSock, buf, sizeof(buf), 0);
    if (rc == -1) {
        perror("Recv error! ");
        close(clientSock);
        exit(1);
    }   
    else {
        printf("DATA RECEIVED = %s\n", buf);
    }

    close(clientSock);
    
    return 0;
}