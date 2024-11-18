#include <stdio.h>
#include <pthread.h>
#define N 1000000
#define NUM_THREADS 4

double a = 2.0;
double x[N], y[N];
pthread_mutex_t lock;

void *daxpy_thread(void *arg) {
    int id = *(int *)arg;
    int start = (N / NUM_THREADS) * id;
    int end = start + (N / NUM_THREADS);

    for (int i = start; i < end; i++) {
        y[i] = a * x[i] + y[i];
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize vectors
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.5;
        y[i] = i * 0.25;
    }

    // Launch threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, daxpy_thread, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Daxpy kernel completed.\n");
    return 0;
}
