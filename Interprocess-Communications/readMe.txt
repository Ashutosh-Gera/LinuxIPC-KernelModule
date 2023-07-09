For fifo:
    Creating 2 pipes, one for each sender and receiver since we want duplex communication hence we require 2 pipes 

For sharedMem:
    Having a common block of memory attacked to both the sender and the receiver and writing and reading the memoryblock acc to requirements

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

For sockets:
    same logic, just using sockets simultaneously and they are 2 way communication so it works!

