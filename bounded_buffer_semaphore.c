#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define RAND_DIVISOR 100000000
#define BUFFER_SIZE 5
#define TRUE 1

typedef int buffer_item;

pthread_mutex_t mutex;

sem_t full, empty;

buffer_item buffer[BUFFER_SIZE];

int counter;

pthread_t tid;
pthread_attr_t attr;

void *producer(void *param);
void *consumer(void *param);

void initializeData() {

    pthread_mutex_init(&mutex, NULL);

    sem_init(&full, 0, 0);

    sem_init(&empty, 0, BUFFER_SIZE);

    pthread_attr_init(&attr);

    counter = 0;
}

int insert_item(buffer_item item) {
    if(counter < BUFFER_SIZE) {
        buffer[counter] = item;
        counter++;
        return 0;
    }
    else {
        return -1;
    }
}

int remove_item(buffer_item *item) {
    if(counter > 0) {
        *item = buffer[(counter-1)];
        counter--;
        return 0;
    }
    else {
        return -1;
    }
}

void *producer(void *param) {
    buffer_item item;

    while(TRUE) {
        int rNum = rand() / RAND_DIVISOR;
        sleep(1);

        item = rand();

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if(insert_item(item)) {
            fprintf(stderr, " Producer report error condition\n");
        }
        else {
            printf("producer produced %d\n", item);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *param) {
    buffer_item item;

    while(TRUE) {
        int rNum = rand() / RAND_DIVISOR;
        sleep(1);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if(remove_item(&item)) {
            fprintf(stderr, "Consumer report error condition\n");
        }
        else {
            printf("consumer consumed %d\n", item);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(int argc, char *argv[]) {

    int i;
    int mainSleepTime;
    int numProd;
    int numCons;

    printf("Enter main sleep time: ");
    scanf("%d", &mainSleepTime);

    printf("Enter the number of producer threads: ");
    scanf("%d", &numProd);

    printf("Enter the number of consumer threads: ");
    scanf("%d", &numCons);

    initializeData();

    for (i = 0; i < numProd; i++) {
        pthread_create(&tid, &attr, producer, NULL);
    }

    for (i = 0; i < numCons; i++) {
        pthread_create(&tid, &attr, consumer, NULL);
    }

    sleep(mainSleepTime);

    printf("Exit the program\n");
    exit(0);
}
