#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>     
#include <sys/wait.h>  
#include <pthread.h>
#include <sys/stat.h>

void * count(void *);
int globalNumber = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t threads[5];
    for (i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, count, NULL);
        pthread_join(threads[i], NULL);
    }
    return 0;
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex);
    return (0);
}