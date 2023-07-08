#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <ctype.h>
#include <sys/sem.h>

//Now we will be doing same question using semaphores for access of resources
#define PHILOSOPHERS 5

sem_t counter;
sem_t Chopstick[PHILOSOPHERS];

void* philosopher(void* phNum);

int main(int argc, char* argv[]){

    for (int i = 0; i < PHILOSOPHERS; i++){
        sem_init(&Chopstick[i], 0, 1); //all binary semaphores for each chopstick in the array
    }
    sem_init(&counter, 0, 4); //initiliasing the counter
    
    printf("Dining philosophers in C with utlization of semaphores for shared resources!\n");

    pthread_t philosopherTid[PHILOSOPHERS];
    int rc;

    //creating philospher threads
    int threadNum[PHILOSOPHERS];
    for (int i = 0; i < PHILOSOPHERS; i++) {
        threadNum[i] = i;
        if ((rc = pthread_create(&philosopherTid[i], NULL, philosopher, &threadNum[i])) != 0){
            perror("error: "); exit(1);
        }
    }

    //join the threads
    for (int i = 0; i < PHILOSOPHERS; i++) {
        rc = pthread_join(philosopherTid[i], NULL);
        if (rc == -1) {
            perror("Error: ");
            exit(1);
        }
    }
    return 0;
}


//philosopher 0 can use sticks 0 & 1
//philosopher 1 can use sticks 1 & 2
//philosopher 2 can use sticks 2 & 3
//philosopher 3 can use sticks 3 & 4
//philosopher 4 can use sticks 0 & 4
void* philosopher(void* phNum) {

    int lStick, rStick;
    int rc;
    int phId = *((int*)phNum);


    while (1) {
        
        bool eat = rand() % 2;

        if (eat) {
            printf("P %d wants to eat\n", phId);
            sem_wait(&counter); // to check if resources are available

            lStick = (phId == 4) ? 0 : phId; //which chopstick to take as left
            //tries to take left chopstick
            if ((rc = sem_wait(&Chopstick[lStick])) != 0){
                perror("error:"); exit(1);
            }

            rStick = (phId == 4) ? 4 : phId + 1;
            if ((rc = sem_wait(&Chopstick[rStick])) != 0){
                perror("error: "); exit(1);
            }

            printf("P %d got sticks %d and %d \n", phId, lStick, rStick);
            printf("P %d is eating\n", phId);

            sleep(rand() % 5 + 1);

            printf("P %d has finished eating \n", phId);

            if ((rc = sem_post(&Chopstick[rStick])) != 0){
                perror("error: "); exit(1);
            }
            if ((rc = sem_post(&Chopstick[lStick])) != 0){
                perror("error: "); exit(1);
            }
            if ((rc = sem_post(&counter)) != 0){
                perror("error: "); exit(1);
            }
        }
        else {
            printf("p %d is thinking...\n", phId);
            sleep(rand() % 5 + 1);
            printf("P %d has finished thinking\n", phId);
        }
    }
}