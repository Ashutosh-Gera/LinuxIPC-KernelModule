#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

//mutex array to be declared static?

// Each chopstick is shared by two philosophers, hence, is a shared resource. This is a race condition
// To prevent this problem we will consider each chopstick as a shared item protected by mutex lock.
// Each philosopher, before he can eat, locks his left chopstick and locks his right chopstick.
// If acquisition of both locks are successful, the philosopher now owns 2 locks (2 chopsticks) and can eat.
// After he finishes eating, he releases both of the locks(chopsticks) and starts thinking again!

//Since we need to lock and unlock a chopstick, each chopstick is associated with a mutex lock
//5 philsophers who think and eat simultaneously => 5 threads
//Since each philospher must have access to its left and right chopsticks(locks), all locks are global variables

// For part A, our solution assigns a partial order to the resources (the forks, in this case), and establishes the convention 
// that all resources will be requested in order, and that no two resources unrelated by order will ever be used by 
// a single unit of work at the same time. Here, the resources (forks) will be numbered 1 through 5 and each unit of 
// work (philosopher) will always pick up the lower-numbered fork first, and then the higher-numbered fork, from among 
// the two forks they plan to use. The order in which each philosopher puts down the forks does not matter. In this case, 
// if four of the five philosophers simultaneously pick up their lower-numbered fork, only the highest-numbered fork will 
// remain on the table, so the fifth philosopher will not be able to pick up any fork. Moreover, only one philosopher will 
// have access to that highest-numbered fork, so he will be able to eat using two forks. This can intuitively be thought of 
// as having one "left-handed" philosopher at the table, who -- unlike all the other philosophers -- takes his fork from the left first.

#define PHILOSOPHERS 5

#define MAX_BUFFERS 10
char buf[MAX_BUFFERS][100];
int bufferInd;
int bufferPrintInd;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t buf_condTwo = PTHREAD_COND_INITIALIZER;
int buffersAvail = MAX_BUFFERS;
int lines_to_print = 0;


pthread_mutex_t Chopstick[PHILOSOPHERS];
pthread_mutex_t bowlCounter[2];

void* philosopher(void* phNum);
void* bufferThread(void* arg);
void printString(const char *const str);


int main(int argc, char* argv[]) {

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&Chopstick[i], NULL);
    }
    for (int j = 0; j < 2; j++){
        pthread_mutex_init(&bowlCounter[j], NULL);
    }

    printf("Dining philosophers in C with strict ordering of resource requests with 2 shared sauce bowls\n");

    pthread_t philosopherTid[PHILOSOPHERS];
    pthread_t bufferTid;
    bufferInd = bufferPrintInd = 0;
    int rc;

    //create buffer thread to store output
    if ((rc == pthread_create(&bufferTid, NULL, bufferThread, NULL)) != 0) {
        perror("error: "); exit(1);
    }

    //creating 5 philosopher threads
    int threadNum[PHILOSOPHERS];
    for (int i = 0; i < PHILOSOPHERS; i++) {
        threadNum[i] = i;
        rc = pthread_create(&philosopherTid[i], NULL, philosopher, &threadNum[i]);
        if (rc != 0) {
            perror("Error: ");
            exit(1);
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

    while (lines_to_print) sleep (1);
    if ((rc = pthread_cancel (bufferTid)) != 0) {
        perror("error: "); exit(1);
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
    char output[100];

    while (true) {//think or eat
        bool eat = rand() % 2;

        if (eat) {
            sprintf(output, "P %d will try to eat\n", phId);
            printString(output);

            lStick = (phId == 4) ? 0 : phId; //get the first chopStick and lock it
            if ((rc = pthread_mutex_lock(&Chopstick[lStick])) != 0) {
                perror("error: ");
                exit(1);
            }
            //get 2nd stick and lock it
            rStick = (phId == 4) ? 4 : phId + 1;
            if ((rc = pthread_mutex_lock(&Chopstick[rStick])) != 0){
                perror("error: ");
                exit(1);
            }

            sprintf(output, "P %d got sticks %d and %d\n", phId, lStick, rStick);
            printString(output);

            sprintf(output, "P %d will try to eat from bowl 0\n", phId);
            printString(output);

            if ((rc = pthread_mutex_trylock(&bowlCounter[0])) != 0) {
                fprintf (stderr, "Error, [cannot take bowl 0] = %d (%s)\n", rc, strerror (rc));
                sprintf(output, "P  %d will try to pick bowl 1 now\n", phId);
                printString(output);

                if ((rc = pthread_mutex_trylock(&bowlCounter[1])) != 0){
                    fprintf (stderr, "Error, [cannot take bowl 1 too] = %d (%s)\n", rc, strerror (rc));
                    sprintf(output, "P %d will not eat as no bowl is free\n", phId);
                    printString(output);

                    //release first stick
                    if ((rc = pthread_mutex_unlock(&Chopstick[lStick])) != 0){
                        perror("error: ");
                        exit(1);
                    }
                    //release second stick
                    if ((rc = pthread_mutex_unlock(&Chopstick[rStick])) != 0){
                        perror("error: ");
                        exit(1);
                    } 
                } else {
                    sprintf(output, "P %d is eating from bowl 1\n", phId);
                    printString(output);

                    sleep (rand() % 5 + 1);


                    sprintf(output, "P %d has finished eating from bowl 1\n", phId);
                    printString(output);

                    if ((rc = pthread_mutex_unlock(&bowlCounter[1])) != 0){
                        perror("error: "); exit(1);
                    }
                    //release first stick
                    if ((rc = pthread_mutex_unlock(&Chopstick[lStick])) != 0){
                        perror("error: ");
                        exit(1);
                    }
                    //release second stick
                    if ((rc = pthread_mutex_unlock(&Chopstick[rStick])) != 0){
                        perror("error: ");
                        exit(1);
                    } 
                }




            } else {
                sprintf(output, "P %d is eating from bowl 0\n", phId);
                printString(output);

                sleep (rand() % 5 + 1);


                sprintf(output, "P %d has finished eating from bowl 0\n", phId);
                printString(output);

                if ((rc = pthread_mutex_unlock(&bowlCounter[0])) != 0){
                    perror("error: "); exit(1);
                }
                //release first stick
                if ((rc = pthread_mutex_unlock(&Chopstick[lStick])) != 0){
                    perror("error: ");
                    exit(1);
                }
                //release second stick
                if ((rc = pthread_mutex_unlock(&Chopstick[rStick])) != 0){
                    perror("error: ");
                    exit(1);
                } 
            }
        } else {
            //thinking
            sprintf(output, "P %d is thinking...\n", phId);
            printString(output);
            sleep (rand() % 5 + 1);
            sprintf(output, "P %d has finished thinking\n", phId);
            printString(output);
        }

        // sprintf(output, "P %d finished %s", phId, (eat) ? "eating\n" : "thinking\n");
        // printString(output); 
    }
}

void printString(const char *const str) {

    int rc;

    //lock buffferrr
    if ((rc = pthread_mutex_lock (&buf_mutex)) != 0) {
        perror("error: "); exit (1);
    }
    while (!buffersAvail) {
        pthread_cond_wait(&buf_cond, &buf_mutex);
    }
    int j = bufferInd;
    if (++bufferInd == MAX_BUFFERS){
        bufferInd = 0;
    }
    buffersAvail--;

    strcpy(buf[j], str);
    lines_to_print++;

    pthread_cond_signal(&buf_condTwo);

    if ((rc = pthread_mutex_unlock(&buf_mutex)) != 0){
        perror("error: "); exit(1);
    }
}

void* bufferThread(void* arg) {
    int rc;

    while (true) {
        if ((rc = pthread_mutex_lock(&buf_mutex)) != 0){
            perror("error: "); exit(1);
        }
        while (!lines_to_print){
            pthread_cond_wait(&buf_condTwo, &buf_mutex);
        }
        printf ("%s", buf [bufferPrintInd]);
        lines_to_print--;
        if (++bufferPrintInd == MAX_BUFFERS){
            bufferPrintInd = 0;
        }
        buffersAvail += 1;
        pthread_cond_signal(&buf_cond);

        if ((rc = pthread_mutex_unlock(&buf_mutex)) != 0){
            perror("error: "); exit(1);
        }
    }
}