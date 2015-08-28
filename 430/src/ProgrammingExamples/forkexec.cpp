
#include <iostream>    //for cout, endl
#include <unistd.h>    //for fork, pipe
#include <stdlib.h>    //for exit
#include <sys/wait.h>  //for wait
using namespace std;

int main(int argc, char *argv[])
{
   int status;

   int pid = fork();
   if (pid < 0) 
   {
      cerr << "Error: Fork Failed" << endl;
      exit(EXIT_FAILURE);
   }   
   else if (pid == 0)  // Child
   {
      cout << "Child Sleeping: " << endl; 
      sleep(10);
      int rc = execlp("/bin/ls", "ls", "-l", (char *) 0);
      if (rc == -1)
      {
         cerr << "Error on execl" << endl;
      }
      exit(EXIT_SUCCESS);
   }
   else  // parent
   {
      cout << "Parent Waiting" << endl;
      wait(&status);
      cout << "Parent Sleeping" << endl;
      sleep(3);
      exit(EXIT_SUCCESS);
   }
}
