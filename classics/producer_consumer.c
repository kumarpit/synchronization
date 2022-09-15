#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex, items, spaces;

int buffer_size = 10;
int buffer[10];
int current_index = 0;

void *producer(void *a) {
    int event;
    for (int i=0; i < 20; i++) {
        event = i;
        
        sem_wait(&spaces);
        
        sem_wait(&mutex);
            buffer[current_index] = event;
            // printf("produced: %d at index: %d\n", buffer[current_index], current_index);
            current_index++;
        sem_post(&mutex);
        
        sem_post(&items);
    }
}

void *consumer(void *a) {
    for (int i=0; i < 20; i++) {
        sem_wait(&items);

        sem_wait(&mutex);
            current_index--;
            printf("consumed: %d at index: %d \n", buffer[current_index], current_index);
        sem_post(&mutex);

        sem_post(&spaces);
    }
}

int main() {
    pthread_t t1, t2;

    sem_init(&spaces, 0, buffer_size);
    sem_init(&mutex, 0, 1);
    sem_init(&items, 0, 0);

    pthread_create(&t1, 0, producer, 0);
    pthread_create(&t2, 0, consumer, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);
}

