/**
 *
 * COE 628 - Operating Systems
 * Lab 6
 *
 **/

// if not already compiled run: (wont build in netbeans)
// gcc -pthread -o main main.c
// else if the main executable is already in folder you can just run it

#include <stdlib.h>     /* For NULL, exit, EXIT_FAILURE */
#include <stdio.h>      /* For printf */
#include <sys/types.h>  /* For pid_t */
#include <unistd.h>     /* For get_pid */
#include <sys/wait.h>   /* For wait */
#include <pthread.h>    /* For pthreads functions and types */

#define PRODUCER_NO 5   // Number of producers, can change here
#define NUM_PRODUCED 20 // Number of items to be produced, can change here

void *generator_function(void*);
void *print_function(void*);
long sum; // Sum of generated values
long finished_producers; // Number of the producer that finished producing

// C: Mutex declaration and initialization
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// F: Condition variable declaration and initialization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main(void) {
    srand(time(NULL)); // Initialize random seed
    sum = 0;
    int i;
    finished_producers = 0;
    
    // A: Creates five generator threads
    pthread_t threads[PRODUCER_NO];
    for (int i = 0; i < PRODUCER_NO; i++) {
        pthread_create(&threads[i], NULL, generator_function, NULL);
    }

    // D: Creates print thread
    pthread_t print_thread;
    pthread_create(&print_thread, NULL, print_function, NULL);
    
    // B: Makes sure that all generator threads have finished before proceeding
    for (int i = 0; i < PRODUCER_NO; i++) {
        pthread_join(threads[i], NULL);
    }

    // E: Makes sure that print thread has finished before proceeding
    pthread_join(print_thread, NULL);
       
    return 0;
}

void *generator_function(void* junk) {
    pthread_mutex_lock(&lock); // Lock
    
    long counter = 0;
    long sum_this_generator = 0;
   
    while (counter < NUM_PRODUCED) {
        long tmpNumber = sum;
        long rnd_number = 1; // rand() % 10; Can make = 1, output should be 100 (20 loops*5 threads)
        printf("Current sum of the generated number up to now is %ld going to add %ld to it.\n", tmpNumber, rnd_number);
        sum = tmpNumber + rnd_number;
        counter++;
        sum_this_generator += rnd_number;
        usleep(1000);
    }
    
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    printf("The sum of produced items for this number generator at the end is: %ld \n", sum_this_generator);
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    
    finished_producers++;
    pthread_mutex_unlock(&lock); // Unlock
    
    // H: If all generators have finished, fire signal for condition variable
    pthread_mutex_lock(&lock);
    if (finished_producers == PRODUCER_NO) {
        printf("All generator threads finished, signaling the condition.\n");
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

void *print_function(void* junk) {
    // G: Wait until all generators have finished
    pthread_mutex_lock(&lock);
    while (finished_producers < PRODUCER_NO) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("The value of counter at the end is: %ld \n", sum);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    return NULL;
}
