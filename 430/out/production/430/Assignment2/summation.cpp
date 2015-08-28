#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int sum;    /*this data is shared by the thread(s) */
void *runner(void *params); //the thread

int main(int argc, char * argv[])
{
    pthread_t tid; //thread identifier
    pthread_attr_t attr; //set of thread attributes

    if (argc != 2)
    {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0)
    {
        fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }

    // get the default attributes
    pthread_attr_init(&attr);

    //create the thread
    pthread_create(&tid, &attr, runner, argv[1]);

    //wait for the thread to exit
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}

void *runner(void *params)
{
    int i , upper = atoi((char *)params);
    sum = 0;

    for (i = 1; i <= upper; i++)
        sum += i;

    pthread_exit(0);
}



