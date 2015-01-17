#include <iostream>
#include <unistd.h>    //for fork, pipe
#include <stdlib.h>    //for exit
#include <sys/wait.h>  //for wait
#include <string.h>
using namespace std;

int main(int argc, char ** argv)
{

    int pid, status;
    int fd1[2], fd2[2]; // file descriptors for pipes
   const int READ = 0, WRITE = 1;
    if (argc < 2)
    {
        perror("ERROR: Too Few Arguments");
        return 0;
    }


    if(pipe(fd1) < 0) perror("ERROR: Bad Pipe1") ;       // create pipe1
    if(pipe(fd2) < 0) perror("ERROR: Bad Pipe2") ;       // create pipe2

    //TODO: Create better Structure

    if ((pid = fork()) < 0) // Create Child Process
    {
        perror("ERROR: Bad Fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        //grep argv
        // fd1(read) --> fd2(write)
        close(fd2[READ]);
        close(fd1[WRITE]);
        dup2(fd2[WRITE], WRITE);
        dup2(fd1[READ], READ);
        execlp("grep", "grep", argv[1],NULL);

    }

    if ((pid = fork()) < 0) // Create Child Process
    {
        perror("ERROR: Bad Fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        // fd2(read) --> stdout

        close(fd2[WRITE]);
        close(fd1[WRITE]);
        close(fd1[READ]);
        dup2(fd2[READ], READ);
        execlp("wc", "wc", "-l" ,NULL);

    }

    if ((pid = fork()) < 0) // Create Child Process
    {
        perror("ERROR: Bad Fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        // stdin --> fd1(write)
        close(fd2[READ]);
        close(fd2[WRITE]);
        close(fd1[READ]);
        dup2(fd1[WRITE], WRITE);
        execlp("ps", "ps", "-A" ,NULL);
    //TODO: OFF By One Error????
    }

    wait(&status);
    return EXIT_SUCCESS;
}