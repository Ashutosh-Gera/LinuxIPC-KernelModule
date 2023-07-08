#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//shmget() function is used to create the shared memory segment 
//while shmat() function is used to attach the shared segment with the address space of the process.
//int shmget(key_t key, size_t size, int shmflg);
//void *shmat(int shmid, const void *shmaddr, int shmflg);
//The  shmget()  function shall return the
//shared memory identifier associated with
//key.
// Upon   successful  completion,  shmget()
//        shall  return  a  non-negative  integer,
//        namely  a shared memory identifier; oth‐
//        erwise, it shall return -1 and set errno
//        to indicate the error.

// Upon  successful  completion,   shmat()
//        shall increment the value of shm_nattch
//        in the data structure  associated  with
//        the  shared  memory  ID of the attached
//        shared memory segment  and  return  the
//        segment's  start  address.   Also,  the
//        shm_atime timestamp shall be set to the
//        current  time

//char randstrs[50][4] = {{0}};

int main(){

    char randstrs[50][4] = {{0}};                  /* 2D array initialized all zero */
    //we will use this array to generate 50 random string each of length 3
    //Hence, our array randstrs is the array of 50 strings, we required
    
    srand (time(NULL));                             /* seed random number generator */
    
    for (int i = 0; i < 3; i++)                    /* fill 2D array columnwise */
        for (int j = 0; j < 50; j++)
            randstrs[j][i] = rand() % 26 + 65;      /* all Uppercase alphabets */
    
    // for (int i = 0; i < 50; i++){                    /* output results */
    //     printf ("%s\n", randstrs[i]);
    // }
     //we will write this whole array in shared memory => need atleast 200 byte space
     //we will allocate 1024 bytes of memory space for safety

    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("error in generating key! ");
        exit(1);
    }

    char* sharedMemory;
    char buff[50][4];
    for (int i = 0; i < 50; i++){
        strcpy(buff[i], randstrs[i]);
    }

    //for (int i = 0; i < 50; i++){                   /* output results */
    //    printf ("%s\n", buff[i]);
    //}
    int shmid;

    shmid = shmget((key_t)key, 1024, 0666|IPC_CREAT); 
    if (shmid == -1){
        perror("error in creating memory segment");
        exit(1);
    }
    //creates shared memory segment with key "key", having size 1024 bytes. IPC_CREAT is used to create the shared segment if it does not exist. 
    //0666 are the permisions on the shared segment

    printf("Key of shared memory is %d\n", shmid);

    sharedMemory = (char*)shmat(shmid, NULL, 0);

    if (*(int*)sharedMemory == -1){
        perror("failed to attach shared memory segment to process address");
    }

    printf("Process attached at %p\n",sharedMemory); //this prints the address where the segment is attached with this process

    for (int i = 0; i < 10; i++){

        int strIds[5]; //strIds can range from 0 to 49
        for (int i = 0; i < 5; i++){
            strIds[i] = rand()%50;
            //printf("%d\n", strIds[i]);
        }
        sleep(1);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                sharedMemory[3*i+j] = buff[strIds[i]][j];
            }
        }
        sharedMemory[16] = '\0';
        for (int i = 0; i < 5; i++){
            sharedMemory[17+i] = strIds[i];
        }

        printf("You wrote : %s\n",(char *)sharedMemory);
        int maxId = (int) sharedMemory[17];
        for (int i = 1; i < 5; i++) {
            int tmp = (int)sharedMemory[17+i];
            maxId = maxId > tmp ? maxId : tmp;
            //maxId = (int)sharedMemory[17+i] > (int)sharedMemory[17 + i + 1] ? (int)sharedMemory[17+i] : (int)sharedMemory[17+i+1];
            //printf("%d\n", (int)sharedMemory[17+i]);
        }
        printf("Maxed array ID sent = %d\n", maxId);
        sleep(1);
        if (maxId == (int)sharedMemory[23]){
            continue;
        }
        sleep(1);
    }  
    shmdt(sharedMemory);//detach
    return 0;
}

//  int strIds[5]; //strIds can range from 0 to 49
//     for (int i = 0; i < 5; i++){
//         strIds[i] = rand()%50;
//         //printf("%d\n", strIds[i]);
//     }
//     //this array contains random 5 ids of array that need to be shared
//     for (int i = 0; i < 5; i++){
//          for (int j = 0; j < 3; j++){
//              sharedMemory[3*i+j] = buff[strIds[i]][j];
//          }
//     }
//     sharedMemory[16] = '\0';
//     for (int i = 0; i < 5; i++){
//         sharedMemory[17+i] = strIds[i];
//     }
//     //shared memory is a pointer
//     printf("You wrote : %s\n",(char *)sharedMemory);
//     int maxId = (int) sharedMemory[17];
//     for (int i = 1; i < 5; i++){
//         int tmp = (int)sharedMemory[17+i];
//         maxId = maxId > tmp ? maxId : tmp;
//         //maxId = (int)sharedMemory[17+i] > (int)sharedMemory[17 + i + 1] ? (int)sharedMemory[17+i] : (int)sharedMemory[17+i+1];
//         //printf("%d\n", (int)sharedMemory[17+i]);
//     }
//     shmdt(sharedMemory);//detach
//     printf("Maxed array Id sent = %d\n", maxId);
//     return 0;