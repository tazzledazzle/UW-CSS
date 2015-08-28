#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void* ThreadFunc(void *);

int main(int argc, char *argv[])
{
   pthread_attr_t attr;
   pthread_t tid;

   pthread_attr_init(&attr);
   pthread_create(&tid, &attr, ThreadFunc, (void *) argv[1]);

   for (int i = 0; i < 10; i++)
   {
      sleep(1);
      cout << "Parent: count " << i << endl;
   }

   pthread_join(tid, NULL);

   return 1;
}

void* ThreadFunc(void *arg)
{
    cout << "Child argument is " << (char *) arg << endl;

    for (int i = 0; i < 3; i++)
    {
        sleep(2);
        cout << "Child: count "<< i << endl;
    }
}
