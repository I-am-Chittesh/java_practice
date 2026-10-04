#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void eat(int phil) {
    printf("\nPhilosopher %d is eating", phil);
}

void* philosopher(void* num) {
    int phil = *(int*)num;
    
    // 1. Enter the room (Max 4 allowed)
    sem_wait(&room);
    printf("\nPhilosopher %d has entered room", phil);
    
    // 2. Lock left and right chopsticks
    sem_wait(&chopstick[phil]);           // Left
    sem_wait(&chopstick[(phil + 1) % 5]); // Right (Circular math)
    
    // 3. Eat
    eat(phil);
    sleep(2);
    printf("\nPhilosopher %d has finished eating", phil);
    
    // 4. Unlock chopsticks and leave room
    sem_post(&chopstick[(phil + 1) % 5]); // Unlock Right
    sem_post(&chopstick[phil]);           // Unlock Left
    sem_post(&room);                      // Leave room
    
    return NULL;
}

int main() {
    int a[5];
    pthread_t tid[5];
    
    sem_init(&room, 0, 4); // Room restricted to 4 philosophers
    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1); // Chopsticks initialized to 1 (available)
        a[i] = i;
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&tid[i], NULL, philosopher, (void*)&a[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}