
/*
* example program which shows usage of a pipe for communication
*/

#include <stdlib.h>  //exit
#include <stdio.h>   //perror
#include <unistd.h>  //fork, pipe
#include <sys/wait.h>   //wait
#include <iostream>
using namespace std;

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
      close(pipeFD[WRITE]); 
      dup2(pipeFD[READ], 0);   //stdin is now child's read pipe
      
      char buf[256];
//    would cin work here?   Why or why not?
      int n = read(pipeFD[READ], buf, 256);
      cout << buf << endl << "Child read and wrote from parent." << endl;
      sleep(5);
   }
   else   //Parent 
   {
      close(pipeFD[READ]);
      dup2(pipeFD[WRITE], 2);  //stderr is now parents write
     
      cerr << "News from the parent:  Hello!!" << endl;
      wait( NULL );
      cout << "Parent exiting" <<endl;
   }
   exit(EXIT_SUCCESS);
} 
