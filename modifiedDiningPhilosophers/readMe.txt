To compile : write make and run ./OneA, ./OneB, ./OneC, ./OneD respectively for all the 4 parts!!

In this question: 
1(a) : solving Dining philosphers problem with strict ordering of requests-
Each chopstick is shared by two philosophers, hence, is a shared resource. This is a race condition
To prevent this problem we will consider each chopstick as a shared item protected by mutex lock.
Each philosopher, before he can eat, locks his left chopstick and locks his right chopstick.
If acquisition of both locks are successful, the philosopher now owns 2 locks (2 chopsticks) and can eat.
After he finishes eating, he releases both of the locks(chopsticks) and starts thinking again!

Since we need to lock and unlock a chopstick, each chopstick is associated with a mutex lock
5 philsophers who think and eat simultaneously => 5 threads
Since each philospher must have access to its left and right chopsticks(locks), all locks are global variables

For part A, our solution assigns a partial order to the resources (the forks, in this case), and establishes the convention 
that all resources will be requested in order, and that no two resources unrelated by order will ever be used by 
a single unit of work at the same time. Here, the resources (forks) will be numbered 1 through 5 and each unit of 
work (philosopher) will always pick up the lower-numbered fork first, and then the higher-numbered fork, from among 
the two forks they plan to use. The order in which each philosopher puts down the forks does not matter. In this case, 
if four of the five philosophers simultaneously pick up their lower-numbered fork, only the highest-numbered fork will 
remain on the table, so the fifth philosopher will not be able to pick up any fork. Moreover, only one philosopher will 
have access to that highest-numbered fork, so he will be able to eat using two forks. This can intuitively be thought of 
as having one "left-handed" philosopher at the table, who -- unlike all the other philosophers -- takes his fork from the left first.

We are using a total of 4 functions in our program:
main -> to create 5 threads 
philosopher -> subroutine for each threads
bufferThread -> a buffer thread so as to lock before each printing and then unlock so that printing is also ordered
printString -> to print the string outputs we store using sprint();

1(b):
Similar to 1(a) except that we are using semaphores [in total 6] instead of mutex . for chopstick -> binary semaphore and then a counter semaphore 
and only 2 functions(main and philosopher) required as we are utilising sem_wait and sem_post now!

1(c):
Same as 1(a) except we are using 2 saucebowls so rotating them also like chopsticks and locking and unlocking them acc to requirements.

1(d):

Same as 1(b) except we are using 2 saucebowls so rotating them also like chopsticks and locking and unlocking them acc to requirements.
Resources used:
https://www.cse.iitb.ac.in/~mythili/os/
Lecture notes
https://en.wikipedia.org/wiki/Dining_philosophers_problem
https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html
https://www.scaler.com/topics/operating-system/dining-philosophers-problem-in-os/
https://man7.org/linux/man-pages/man3/sem_init.3.html
https://man7.org/linux/man-pages/man3/sem_wait.3.html
https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
https://www.cse.iitb.ac.in/~mythili/os/references/LittleBookOfSemaphores.pdf
