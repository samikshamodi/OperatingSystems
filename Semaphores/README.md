# Semaphores
Implemented my own counting semaphore using the pthread library. I also used the blocking and non-blocking functions available in the Pthreads library to implement the blocking and non-blocking variants of the primitives wait and signal.

I then used my implemented semaphore to solve the modified version of dining philosopher problem. 

*"Consider the scenario where you have a similar case of k philosophers and k forks. But in this case, the dinning table also has a pair of sauce bowls, both of which are needed simultaneously for a philosopher
to eat. Write a program that simulates the philosophers using threads, and the resources (forks and sauce bowls) using a shared variable. Your simulation should print the following message on the console whenever a philosopher gets to eat: "Philosopher < thread id > eats using forks < fork no x > and < fork no y >. The simulation keeps running in an infinte loop. Then, use my semaphore to avoid any possible deadlocks."*

For the shared resource that is the k forks and 2 sauce bowls, I have used a semaphore initialized with count 1. I implemented two programs - blocking (DiningPhilosophers_B.c) and non-blocking (DiningPhilosophers_NB.c) variants.

## Blocking Semaphore
The program is DiningPhilosophers_B.c

### Logic
- Inside an infinite loop in the philosopher thread function, the philosopher first tries to pick up the forks. To avoid deadlock in this scenario, the philosopher at an even position should first pick the right chopstick and then the left chopstick while the philosopher at an odd position should first pick the left chopstick and then the right chopstick. 

- After the philosopher has acquired both the forks, he tries to pick up both bowls. To avoid deadlock, the philosopher who has already acquired both the forks, must first acquire bowl 0 and only after acquiring bowl 0, he must acquire bowl 1.

- After the philosopher has acquired both the forks and both the bowls, he eats and puts down both the forks and bowls making them available to other philosopher threads.

### Semaphore Implementation
- The semaphore is a struct with 3 fields-count, pthread_mutex_t, and pthread_cond_t. 

- To implement wait pthread_mutex_lock() was used.We need to make the wait function an atomic operation so we acquire the mutex lock. We need to decrement the count but also check that the count is greater than 0. So we wait while the count is 0 using pthread_cond_wait(). After decrementing the count we release the lock.

- To implement signal pthread_mutex_lock was used. We need to make the signal function an atomic operation so for that we acquire the mutex lock. We then need to increment the count which I do. Then we can either always notify or notify when the count becomes 1 from 0, because only then there is a likelihood of someone waiting. I chose to notify in the latter case. After that we release the mutex lock.

## Non-blocking Sempahore
The program is DiningPhilosophers_NB.c

### Logic
- Inside an infinite loop in the philosopher thread function, the philosopher tries to pick up the resources that are the 2 forks he can access and the 2 bowls. To avoid deadlock in this scenario, the philosopher at an even position should first pick the right chopstick and then the left chopstick while the philosopher at an odd position should first pick the left chopstick and then the right chopstick. If philosopher gets the first chopstick, he tries to pick the second chopstick. If he gets the second chopstick he tries to pick the sauce bowls. If he does not get the second chopstick, he releases the first chopstick.

- Now if the philosopher gets both the first and the second chopstick, then he tries to get the two sauce bowls. If the philosopher gets the first bowl, he then tries to get the second bowl. If he gets the second bowl also then he eats and releases both the bowls and both the forks. But if the philosopher can't get the second bowl then he releases the first bowl, thus avoiding any deadlock.

### Semaphore Implementation
- The semaphore is a struct with 2 fields-count, pthread_mutex_t.

- To implement non-blocking wait pthread_mutex_trylock() was used. If a thread is not able to acquire the lock, wait returns 1. Else if it is able to acquire the lock, it checks the count. If count is less than 0, wait again returns 1. When 1 is returned it simply means that the philosopher can’t acquire that resource right now. If it can acquire the resource, the count is decremented and we release the lock.

- To implement signal pthread_mutex_lock was used. We need to make the signal function an atomic operation so for that we acquire the mutex lock. We then need to increment the count which I do. After that we release the mutex lock.

Please read the [WriteUp.pdf](WriteUp.pdf) for a more detailed description.
