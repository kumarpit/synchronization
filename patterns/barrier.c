#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 10

/**
When the first n − 1 threads arrive they should block until the nth thread
arrives, at which point all the threads may proceed
*/

sem_t mutex, barrier;
int count = 0;

void *thread(void *a) {
    sem_wait(&mutex);
        count++;
        if (count == NUM_THREADS) {
            sem_post(&barrier);
        }
    sem_post(&mutex);

    printf("waiting...\n");

    sem_wait(&barrier);
        printf("done.\n");
    sem_post(&barrier);
}

int main() {
    pthread_t threads[NUM_THREADS];

    sem_init(&mutex, 0, 1);
    sem_init(&barrier, 0, 0);

    for (int i=0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], 0, thread, 0);
    }

    for (int i=0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], 0);
    }
}