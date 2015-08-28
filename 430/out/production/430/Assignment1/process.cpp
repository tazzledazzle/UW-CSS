#include <stdio.h>
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

    if(pipe(fd1) < 0) perror("ERROR: Bad Pipe1") ; // create pipe1
    if(pipe(fd2) < 0) perror("ERROR: Bad Pipe2") ; // create pipe2

    if ((pid = fork()) < 0) // Create New Child Process
    {
      perror("ERROR: Bad Fork");
      return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
     if ((pid = fork()) < 0) // Create New Child Process
     {
       perror("ERROR: Bad Fork");
       return EXIT_FAILURE;
     }
     else if (pid == 0)
     {
        if ((pid = fork()) < 0) // Create New Child Process
       {
         perror("ERROR: Bad Fork");
         return EXIT_FAILURE;
       }
       else if (pid == 0)
       {
          //child
          close(fd2[WRITE]); 
          close(fd1[WRITE]);  
          close(fd1[READ]);
          dup2(fd2[READ], READ);
          execlp("wc", "wc", "-l" ,NULL);
       }
       else
       {
          //grand child
          close(fd2[READ]);   
          close(fd1[WRITE]);
          dup2(fd2[WRITE], WRITE);
          dup2(fd1[READ], READ);
          execlp("grep", "grep", argv[1],NULL);
        }
      }
      else
      {
       //great grand child
       close(fd2[READ]);
       close(fd2[WRITE]);
       close(fd1[READ]);
       dup2(fd1[WRITE], WRITE);
       execlp("ps", "ps", "-A" ,NULL);
     }
    }
    else
    {
      //parent 
      wait(&status);
    }
    return 0;
    //EXIT_SUCCESS;

}