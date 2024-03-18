//many readers can read
//no readers when writer is writing
//one writer at a time

//wait-d-decrement-wait
//signal-v-increment-post
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t rw_mutex, mutex;  // Semaphores for controlling access
int read_count = 0;     // Tracks the number of active readers

// Writer thread function
void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex);  // Acquire permission to write

        // Critical Section - Perform writing here
        printf("Writer is writing...\n");
        sleep(rand() % 3 + 1); // Simulate writing time

        sem_post(&rw_mutex);          // Release write permission
        sleep(rand() % 3 + 1); // Simulate thinking/other tasks
    }
    printf("\n");
}#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void* requester(void* arg) {
    for (int i = 0; i < 20; ++i) {
        int data = rand() % 100; // Generate random data for demonstration

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            // Buffer is full, wait for the sender to consume some data
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[count++] = data;
        printf("Requester produced: %d\n", data);

        // Signal the sender that the buffer is not empty
        pthread_cond_signal(&full);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* sender(void* arg) {
    for (int i = 0; i < 20; ++i) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            // Buffer is empty, wait for the requester to produce some data
            pthread_cond_wait(&full, &mutex);
        }

        int data = buffer[--count];
        printf("Sender consumed: %d\n", data);

        // Signal the requester that the buffer is not full
        pthread_cond_signal(&empty);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t requester_thread, sender_thread;

    // Create requester and sender threads
    pthread_create(&requester_thread, NULL, requester, NULL);
    pthread_create(&sender_thread, NULL, sender, NULL);

    // Wait for threads to finish
    pthread_join(requester_thread, NULL);
    pthread_join(sender_thread, NULL);

    return 0;
}        // Critical Section - Perform reading here
        printf("Reader is reading...\n");
        sleep(rand() % 3 + 1); // Simulate reading time

        sem_wait(&mutex);         // Protect the read_count variable
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);  // Release write permission if last reader
        }
        sem_post(&mutex);         // Release read_count protection
        sleep(rand() % 3 + 1); // Simulate thinking/other tasks
    }
    printf("\n");
}

int main() {
    sem_init(&rw_mutex, 0, 1); // Initialize semaphores, rw_mutex for writers
    sem_init(&mutex, 0, 1);    // mutex to protect read_count

    int num_readers, num_writers; 
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    pthread_t reader_threads[num_readers], writer_threads[num_writers];

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    // Wait for all threads to finish 
    for (int i = 0; i < num_readers; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}
