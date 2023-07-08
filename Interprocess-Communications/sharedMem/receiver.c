#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {

    char* sharedMemory;
    int shmid;

    key_t key = ftok("shmfile", 65);

    shmid = shmget((key_t) key, 1024, 0666 | IPC_CREAT);

    printf("Key of shared memory is %d\n", shmid);
    sharedMemory = (char*) shmat(shmid, NULL, 0); //attach the shared memory
    printf("Process attached at %p\n", sharedMemory);

    //reading shared memory pointer;
    for (int i = 0; i < 10; i++){

        sleep(1);
        printf("Strings received from sender: \n");
        int idCounter = 0;
        for (int i = 0; i < 16; i++){
            printf("%c", sharedMemory[i]);
            if ((i+1) % 3 == 0){
                printf("        ID = %d\n", (int)sharedMemory[17+(idCounter++)]);
            }
        }
        int maxId = (int) sharedMemory[17];
        for (int i = 1; i < 5; i++){
            int tmp = (int)sharedMemory[17+i];
            maxId = maxId > tmp ? maxId : tmp;
        }
        printf("Maxed array Id received = %d\n", maxId);
        sleep(1);
        sharedMemory[23] = maxId;
        sleep(1);
    }

    shmdt(sharedMemory); //detach
    shmctl(shmid, IPC_RMID, NULL); //destroy
    return 0;    
}



//   printf("Strings received from sender: \n");
//     for (int i = 0; i < 16; i++){
//         printf("%c", sharedMemory[i]);
//         if ((i+1) % 3 == 0){
//             printf("\n");
//         }
//     }
//     int maxId = (int) sharedMemory[17];
//     for (int i = 1; i < 5; i++){
//         int tmp = (int)sharedMemory[17+i];
//         maxId = maxId > tmp ? maxId : tmp;
//     }
//     printf("Maxed array Id received = %d\n", maxId);