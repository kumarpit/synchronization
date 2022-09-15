#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_SIZE 10
#define NUM_IT 20

sem_t mutex, items, spaces;

int buffer[BUFFER_SIZE];
int current_index = 0;

void *producer(void *a) {
    int event;
    for (int i=0; i < NUM_IT; i++) {
        event = i;
        
        sem_wait(&spaces);
        
        sem_wait(&mutex);
            buffer[current_index] = event;
            printf("produced: %d at index: %d\n", buffer[current_index], current_index);
            current_index++;
        sem_post(&mutex);
        
        sem_post(&items);
    }
}

void *consumer(void *a) {
    for (int i=0; i < NUM_IT; i++) {
        sleep(1);
        sem_wait(&items);

        sem_wait(&mutex);
            current_index--;
            // printf("consumed: %d at index: %d \n", buffer[current_index], current_index);
        sem_post(&mutex);

        sem_post(&spaces);
    }
}

int main() {
    pthread_t t1, t2;

    sem_init(&spaces, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);
    sem_init(&items, 0, 0);

    pthread_create(&t1, 0, producer, 0);
    pthread_create(&t2, 0, consumer, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);
}

