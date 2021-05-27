/*Name: Samiksha Modi
Roll No:2019331
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define k 5         //No of philosphers
int thread_id[k];       //Philosphers

/*Done using pthread library
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/
Used to learn the correct syntax of locking and unlocking the pthread_mutex_t mutex
Also referred to manpages for the syntax
https://www.geeksforgeeks.org/semaphores-in-process-synchronization/
Used to learn the implementation of a counting sempahore and wait and signal operations
NPTEL Lecture 25: Multiple producer-multiple consumer queue, Semaphore by Prof Sorav Bansal
http://www.cse.iitd.ernet.in/os-lectures
Used to learn sempahores and how to implement my own counting sempahore using lock and cv
Then implemented them using the pthread library
*/

/*My own semaphore called my_semaphore
It has field count, an associated mutex lock
*/

typedef struct
{
    volatile unsigned count;
    pthread_mutex_t mutex;
} my_semaphore;

my_semaphore forks[k], bowls[2];

/*Initiliazing the corresponding fields
https://linux.die.net/man/3/pthread_cond_init
https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html
Referred to the above links for how to initialise
*/
void sema_init(my_semaphore *sema, int N)
{
    sema->count = N;
    pthread_mutex_init(&sema->mutex, NULL);
}

int sema_wait(my_semaphore *sema)
{
    if(pthread_mutex_trylock(&sema->mutex) == 0)
    {
        if(sema->count < 0)
        {
            return 1;
        }
        sema->count -= 1;
        pthread_mutex_unlock(&sema->mutex);
        return 0;
    }
    return 1;
}

void sema_signal(my_semaphore *sema)
{
    pthread_mutex_lock(&sema->mutex);
    {
        sema->count += 1;
        pthread_mutex_unlock(&sema->mutex);
    }
}

/*signal(printValue) operation
Used to debugging to print the value of count
*/
void sema_print_signal(my_semaphore *sema)
{
    pthread_mutex_lock(&sema->mutex);
    printf("%d\n", sema->count );
    pthread_mutex_unlock(&sema->mutex);
}


/*keeping the fork down thereby releasing the resource*/
void keepForksDown(int phil)
{
    sema_signal(&forks[(phil + 1) % k]);
    sema_signal(&forks[phil]);
}

/*keeping the bowl down thereby releasing the resource*/
void keepBowlsDown()
{
    sema_signal(&bowls[0]);
    sema_signal(&bowls[1]);
}


/*wait to get both forks A philosopher at an even position should pick the
right chopstick and then the left chopstick while a philosopher at an odd
position should pick the left chopstick and then the right chopstick. Thus avoiding deadlock
If philospher picks the first chopstick, he tries to pick the second chopstick. If he gets the second
chopstick he tries  to pick the sauce bowls. If he does not get the second chopstick, he release the
first chopstick
Then he waits to get both bowls. If the philospher can get the first bowl, he tries to get the second bowl. If he gets the
second bowl then he eats and releases both the  bowls and both the forks. if the philopsher can't get the second bowl
then he releases the first bowl 
*/
void pickUp(int phil)
{

    if(phil % 2 == 0)
    {
        if(sema_wait(&forks[(phil + 1) % k]) == 0)
        {
            if(sema_wait(&forks[phil]) == 0)
            {
                if(sema_wait(&bowls[0]) == 0)
                {
                    if(sema_wait(&bowls[1]) == 0)
                    {
                        printf("Philosopher %d eats using forks %d and %d\n", phil, phil, (phil + 1) % k);
                        keepForksDown(phil);
                        keepBowlsDown();
                    }
                    else
                    {
                        sema_signal(&bowls[0]);
                    }

                }
            }
            else
            {
                sema_signal(&forks[(phil + 1) % k]);
            }
        }
    }
    else
    {
        if(sema_wait(&forks[phil]) == 0)
        {
            if(sema_wait(&forks[(phil + 1) % k]) == 0)
            {
                if(sema_wait(&bowls[0]) == 0)
                {
                    if(sema_wait(&bowls[1]) == 0)
                    {
                        printf("Philosopher %d eats using forks %d and %d\n", phil, phil, (phil + 1) % k);
                        keepForksDown(phil);
                        keepBowlsDown();
                    }
                    else
                    {
                        sema_signal(&bowls[0]);
                    }

                }
            }
            else
            {
                sema_signal(&forks[phil]);
            }
        }
    }
}

void *thread_func(void *philID)
{
    while(1)
    {
        int phil = *(int *)philID;
        pickUp(phil);
    }

    return NULL;
}


int main(void)
{
    //Assigning philosher numbers
    for (int i = 0; i < k; ++i)
    {
        thread_id[i] = i;
    }

    for(int i = 0; i < k; i++)
    {
        sema_init(&forks[i], 1);
    }

    for(int i = 0; i < 2; i++)
    {
        sema_init(&bowls[i], 1);
    }


    pthread_t threads[k];

    for(int i = 0; i < k; i++)
    {
        //  printf("Created Philospher %d thread\n", i);
        pthread_create(&threads[i], NULL, thread_func, &thread_id[i]);
    }

    for(int i = 0; i < k; i++)
    {
        pthread_join(threads[i], NULL);
    }


    return 0;
}
