#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

/**
a writer cannot enter the critical section while any other
thread (reader or writer) is there, and while the writer is there, no other thread
may enter
categorical mutual exclusion
lightswitch solution
*/

#define NUM_IT_WRITER 10
#define NUM_IT_READER 5

sem_t mutex, room_empty;
int readers = 0;
int shared_ds = 0;

void *writer(void *a) {
    for (int i=0; i < NUM_IT_WRITER; i++) {
        sem_wait(&room_empty);
            printf("the writer is here \n");
            shared_ds = i;
        sem_post(&room_empty);
        sleep(1);
    }
}

void *reader(void *a) {
    for (int i=0; i < NUM_IT_READER; i++) {
        sem_wait(&mutex);
            readers++;
            // first reader, must wait for room to be empty
            if (readers == 1) {
                sem_wait(&room_empty);
            }
        sem_post(&mutex);

        printf("current value: %d \n", shared_ds);

        sem_wait(&mutex);
            readers--;
            // last reader out, allows writer to be in
            if (readers == 0) {
                sem_post(&room_empty);
            }
        sem_post(&mutex);
        sleep(1);
    }
}


int main() {
    pthread_t t1, t2, t3;

    sem_init(&mutex, 0, 1);
    sem_init(&room_empty, 0, 1);

    pthread_create(&t1, 0, writer, 0);
    pthread_create(&t2, 0, reader, 0);
    pthread_create(&t3, 0, reader, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
}