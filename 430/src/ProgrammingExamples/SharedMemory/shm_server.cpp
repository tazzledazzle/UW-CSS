#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define SHMSZ     27

int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 3456;

    /*
     *  Create the segment
     */
    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
    if (shmid  < 0) 
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Attach the segment to our data space.
     */
    shm = (char *) shmat(shmid, NULL, 0);

    /*
     * Now put some things into the memory for the other process to read.
     */
    s = shm;

    for (c = 'a'; c <= 'z'; c++)
    {
        *s++ = c;
    }
    *s = 0;

    /*
     * Wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
        sleep(1);

    exit(0);
}
