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

int main(void) {
    int res = mkfifo("fifo2", 0777); //creates a named pipe with name fifo1
    printf("named pipe created!\n");
}



