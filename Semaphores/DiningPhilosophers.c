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
It has field count, an associated mutex lock and a condition variable
*/

typedef struct
{
    volatile unsigned count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
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
    pthread_cond_init(&sema->cond, NULL);
}

/*wait operation
Need to make it an atomic operation so for that we acqurie the mutex lock
We need to decrement the count but alo check that the count is greater than 0
So we wait while the count is 0
After decrementing we release the lock
*/
void sema_wait(my_semaphore *sema)
{
    pthread_mutex_lock(&sema->mutex);
    while(sema->count == 0)
    {
        pthread_cond_wait(&sema->cond, &sema->mutex);
    }
    sema->count -= 1;
    pthread_mutex_unlock(&sema->mutex);
}

/*signal operation
Need to make it an atomic operation so for that we acqurie the mutex lock
We need to increment the count
I can always notify or notify when the count becomes 1 from 0, because only then there is
a likelihood of someone waiting. I chose to notify in the latter case
After that we release the mutex lock
*/
void sema_signal(my_semaphore *sema)
{
    pthread_mutex_lock(&sema->mutex);
    sema->count += 1;
    if(sema->count == 1)
    {
        pthread_cond_signal(&sema->cond);
    }
    pthread_mutex_unlock(&sema->mutex);
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

/*wait to get both forks A philosopher at an even position should pick the
right chopstick and then the left chopstick while a philosopher at an odd
position should pick the left chopstick and then the right chopstick. Thus avoiding deadlock */
void pickForks(int phil)
{
    if(phil % 2 == 0)
    {
        sema_wait(&forks[(phil+1)%5]);
        sema_wait(&forks[phil]);
    }
    else
    {
        sema_wait(&forks[phil]);
        sema_wait(&forks[(phil+1)%5]);
    }
}


/*wait to get both bowls*/
void pickBowls()
{
    sema_wait(&bowls[0]);
    sema_wait(&bowls[1]);
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

void *thread_func(void *philID)
{

    while(1)
    {
        int phil = *(int *)philID;
        pickForks(phil);
        pickBowls();
       // / sleep(1); //eating
        printf("Philosopher %d eats using forks %d and %d\n", phil, phil, (phil + 1) % k);
        keepForksDown(phil);
        keepBowlsDown();
    }

    return NULL;
}


int main(void)
{
    //Assigning philospher numbers
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
