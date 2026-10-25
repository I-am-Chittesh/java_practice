#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

enum {THINKING, HUNGRY, EATING} state[N];
pthread_mutex_t mutex;
pthread_cond_t cond[N];

void test(int i) {
    if (state[i] == HUNGRY && state[(i + 4) % N] != EATING && state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d is eating\n", i);
        pthread_cond_signal(&cond[i]);
    }
}

void pickup(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    while (state[i] != EATING) {
        pthread_cond_wait(&cond[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void putdown(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d has finished eating\n", i);
    test((i + 4) % N);
    test((i + 1) % N);
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;
    while (1) {
        sleep(1);
        pickup(i);
        sleep(1);
        putdown(i);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
        ids[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}