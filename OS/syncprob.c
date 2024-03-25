#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

sem_t rw_mutex, mutex;  // Semaphores for controlling access
int read_count = 0;     // Tracks the number of active readers
char buffer[BUFFER_SIZE];  // Shared buffer

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    
    while (1) {
        // Acquire mutex to protect read_count
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            // First reader, acquire rw_mutex to prevent writers
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        
        // Read from buffer
        printf("Reader %d is reading: %s\n", reader_id, buffer);
        
        // Release mutex
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            // Last reader, release rw_mutex to allow writers
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
        
        // Sleep for a random amount of time
        usleep(rand() % 1000000);
    }
    
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    
    while (1) {
        // Acquire rw_mutex to prevent other writers and readers
        sem_wait(&rw_mutex);
        
        // Write to buffer
        sprintf(buffer, "Writer %d wrote something", writer_id);
        printf("Writer %d wrote: %s\n", writer_id, buffer);
        
        // Release rw_mutex
        sem_post(&rw_mutex);
        
        // Sleep for a random amount of time
        usleep(rand() % 1000000);
    }
    
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    
    // Create reader threads
    pthread_t reader_threads[5];
    int reader_ids[5];
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    pthread_t writer_threads[3];
    int writer_ids[3];
    for (int i = 0; i < 3; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    
    // Wait for reader threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    
    // Wait for writer threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    
    return 0;
}