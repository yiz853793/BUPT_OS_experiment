#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 共享数据
int shared_data = 0;
pthread_mutex_t lock;

void *thread_func1(void *arg) {
    sleep(rand() % 2);
    pthread_mutex_lock(&lock);
    shared_data += 10;
    printf("Thread 1 updated shared data: %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

// 子线程2
void *thread_func2(void *arg) {
    sleep(rand() % 2);
    pthread_mutex_lock(&lock);
    shared_data += 20;
    printf("Thread 2 updated shared data: %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *parent_thread_func(void *arg) {
    sleep(1);
    pthread_mutex_lock(&lock);
    printf("Parent thread reading shared data: %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[3];
    srand(time(NULL));  

    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        exit(1);
    }

    pthread_create(&threads[0], NULL, thread_func1, NULL);
    pthread_create(&threads[1], NULL, thread_func2, NULL);

    pthread_create(&threads[2], NULL, parent_thread_func, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}
