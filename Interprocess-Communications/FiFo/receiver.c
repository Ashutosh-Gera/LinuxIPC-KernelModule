#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {

    int res, n;
    char buffer[1024];

    res = open("fifo1", O_RDONLY);
    n = read(res, buffer, 1024);

    printf("Reader process %d started\n", getpid());
    printf("Data received by receiver %d is: %s\n",getpid(), buffer);

    
}