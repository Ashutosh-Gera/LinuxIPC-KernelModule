to compile go to each folder [fifo/sharedMem/socket] and type make
Write two programs P1 and P2. The first program P1 needs to generate an
array of 50 random strings (of characters) of fixed length each. P1 then sends
a group of five consecutive elements of the array of strings to P2 along with
the ID’s of the strings, where the ID is the index of the array corresponding
to the string. The second program P2 needs to accept the received strings,
and send back the highest ID received back to P1 to acknowledge the strings
received. The program P2 simply prints the ID’s and the strings on the console.
On receiving the acknowledged packet, P1 sends the next five strings, with the
string elements starting from the successor of the acknowledged ID.

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


Resources used:
Beej's guide to UNIX IPC [book]
IBM documentation for sockets: https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=considerations-unix-domain-sockets
Manpages
https://man7.org/linux/man-pages/man3/mkfifo.3.html

