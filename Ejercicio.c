#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 10
#define CHUNK_SIZE 100

typedef struct {
    int pos;
    int val;
} est_t;

int arr[ARRAY_SIZE];
est_t est[NUM_THREADS];
pthread_t threads[NUM_THREADS];

void* rellenar(void* arg) {
    est_t* est = (est_t*) arg;
    for(int i = est->pos; i < est->pos + CHUNK_SIZE; i++) {
        arr[i] = est->val;
    }
    return NULL;
}

int main() {
    for(int i = 0; i < NUM_THREADS; i++) {
        est[i].pos = i * CHUNK_SIZE;
        est[i].val = i;
        pthread_create(&threads[i], NULL, rellenar, &est[i]);
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
        if((i + 1) % CHUNK_SIZE == 0) {
            printf("\n");
        }
    }

    return 0;
}