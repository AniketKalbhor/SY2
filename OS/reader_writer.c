#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 5

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    
    // Reader entry section
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);
    
    // Reading section
    printf("Reader %d is reading...\n", reader_id);
    
    // Reader exit section
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);
    
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    
    // Writer entry section
    sem_wait(&wrt);
    
    // Writing section
    printf("Writer %d is writing...\n", writer_id);
    
    // Writer exit section
    sem_post(&wrt);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[MAX_READERS], writer_thread;
    int reader_ids[MAX_READERS], writer_id;
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    
    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer thread
    writer_id = 1;
    pthread_create(&writer_thread, NULL, writer, &writer_id);
    
    // Join reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer thread
    pthread_join(writer_thread, NULL);
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    
    return 0;
}