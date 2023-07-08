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

int main() {

    int res;
    int n;

    res = open("fifo1", O_WRONLY);
    // write(res, "message", 7);
    // printf("Sender process %p sent the data\n", getpid());
    //generating random array of strings

    char randstrs[50][4] = {{0}};

    srand(time(NULL));

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 50; j++){
            randstrs[j][i] = rand()%26 + 65;
        }
    }   

    for (int i = 0; i < 10; i++){
        int strIds[5];
        for (int j = 0; j < 5; j++){
            strIds[i] = rand()%50;
        }

        //sleep(1);
        for (int k = 0; k < 5; k++){
            write(res, randstrs[strIds[k]], sizeof(randstrs[strIds[k]]));
        }
    }

    printf("Sender process %p has sent the data\n", getpid());
}