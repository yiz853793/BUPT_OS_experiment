#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// 共享数据
int shared_data = 0;
pthread_mutex_t lock;

// 子线程1执行的任务
void *thread_func1(void *arg) {
    sleep(rand() % 2);
    pthread_mutex_lock(&lock);
    shared_data += 10;
    printf("Thread 1: Shared data = %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

// 子线程2执行的任务
void *thread_func2(void *arg) {
    sleep(rand() % 2);
    pthread_mutex_lock(&lock);
    shared_data += 20;
    printf("Thread 2: Shared data = %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

// 子线程3执行的任务
void *thread_func3(void *arg) {
    sleep(rand() % 2);
    pthread_mutex_lock(&lock);
    shared_data += 30;
    printf("Thread 3: Shared data = %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[3];
    srand(time(NULL));

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }
    
    pthread_create(&threads[0], NULL, thread_func1, NULL);
    pthread_create(&threads[1], NULL, thread_func2, NULL);
    pthread_create(&threads[2], NULL, thread_func3, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Parent thread: Final shared data = %d\n", shared_data);

    pthread_mutex_destroy(&lock);
    return 0;
}
