#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

// 1. BUILD THE MONITOR STRUCT
typedef struct {
    int buffer[BUFFER_SIZE];
    int count;
    pthread_mutex_t mutex;       // The main monitor lock
    pthread_cond_t not_empty;    // Lounge for waiting consumers
    pthread_cond_t not_full;     // Lounge for waiting producers
} monitor_t;

// 2. THE PRODUCER PROCEDURE (Insert)
void monitor_insert(monitor_t* monitor, int value) {
    pthread_mutex_lock(&monitor->mutex); // Lock Monitor
    
    // If buffer is full, go to sleep in 'not_full' lounge
    while (monitor->count >= BUFFER_SIZE) {
        pthread_cond_wait(&monitor->not_full, &monitor->mutex);
    }
    
    monitor->buffer[monitor->count++] = value; // Add item
    
    pthread_cond_signal(&monitor->not_empty); // Wake up a consumer
    pthread_mutex_unlock(&monitor->mutex);    // Unlock Monitor
}

// 3. THE CONSUMER PROCEDURE (Remove)
int monitor_remove(monitor_t* monitor) {
    int value;
    pthread_mutex_lock(&monitor->mutex); // Lock Monitor
    
    // If buffer is empty, go to sleep in 'not_empty' lounge
    while (monitor->count == 0) {
        pthread_cond_wait(&monitor->not_empty, &monitor->mutex);
    }
    
    value = monitor->buffer[--monitor->count]; // Remove item
    
    pthread_cond_signal(&monitor->not_full);  // Wake up a producer
    pthread_mutex_unlock(&monitor->mutex);    // Unlock Monitor
    
    return value;
}