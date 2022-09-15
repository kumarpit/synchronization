#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

/**
we want to guarantee that a1 happens before b2 and b1 happens before a2
*/

sem_t a1, b1;

void *thread_a(void *a) {
    printf("a1 \n");
    sem_post(&a1);
    sem_wait(&b1);
    printf("a2 \n");
}

void *thread_b(void *b) {
    printf("b1 \n");
    sem_post(&b1);
    sem_wait(&a1);
    printf("b2 \n");
}

int main() {
    pthread_t a, b;

    sem_init(&a1, 0, 0);
    sem_init(&b1, 0, 0);

    pthread_create(&a, 0, thread_a, 0);
    pthread_create(&b, 0, thread_b, 0);

    pthread_join(a, 0);
    pthread_join(b, 0);
}