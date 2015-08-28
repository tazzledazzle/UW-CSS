
/*
* example program which shows usage of a pipe for communication
*/

#include <stdlib.h>  //exit
#include <stdio.h>   //perror
#include <unistd.h>  //fork, pipe
#include <sys/wait.h>   //wait
#include <iostream>
using namespace std;

const int BUF_SIZE = 4096;

int main()
{
   enum {READ, WRITE};
   pid_t pid;
   int pipeFD[2];

   if (pipe(pipeFD) < 0)
   {
      perror("Error in creating pipe");
      exit(EXIT_FAILURE);
   }

   pid = fork();
   if (pid < 0)
   {
      perror("Error during fork");
      exit(EXIT_FAILURE);
   }

   if (pid == 0)  //Child
   {
      close(pipeFD[READ]); 
      dup2(pipeFD[WRITE], 1);   //stdout is now child's read pipe
      execlp("/bin/ls", "ls", "-l", NULL);
      // process is overlayed so does not execut past here...
   }
   else   //Parent 
   {
      wait( NULL );
      char buf[BUF_SIZE];
      int n = read(pipeFD[READ], buf, BUF_SIZE);
      buf[n] = '\0';
      cout << buf;
      cout << "Parent exiting" <<endl;
   }
   exit(EXIT_SUCCESS);
} 
