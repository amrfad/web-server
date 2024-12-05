#include "thread_pool.h"
#include "server.h"

// Variabel untuk Thread Pool
ThreadPool *pool;

// Fungsi untuk membuat antiran tugas/permintaan client
TaskQueue* createTaskQueue(int capacity) {
    TaskQueue *queue = malloc(sizeof(TaskQueue));
    queue->tasks = malloc(sizeof(int) * capacity);
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->shutdown = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}

// 
void destroyTaskQueue(TaskQueue *queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cond); // Pastikan aman dihancurkan
    free(queue->tasks);
    free(queue);
}


//
void enqueue(TaskQueue *queue, int task) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->size == queue->capacity) {
	pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->tasks[queue->rear] = task;
    queue->size++;
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

//
void* workerThread(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    while (1) {
        pthread_mutex_lock(&pool->queue->mutex);

        // Tunggu jika queue kosong, tapi periksa shutdown flag
        while (pool->queue->size == 0 && !pool->queue->shutdown) {
            pthread_cond_wait(&pool->queue->cond, &pool->queue->mutex);
        }

        if (pool->queue->shutdown) {
            pthread_mutex_unlock(&pool->queue->mutex);
            break; // Keluar dari loop jika shutdown
        }

        // Dequeue tugas
        int clientSocket = pool->queue->tasks[pool->queue->front];
        pool->queue->front = (pool->queue->front + 1) % pool->queue->capacity;
        pool->queue->size--;

        pthread_mutex_unlock(&pool->queue->mutex);

        // Handle request dari client 
        handle_client(clientSocket);
    }
    return NULL;
}


// 
ThreadPool* createThreadPool(int threadCount, int queueCapacity) {
    ThreadPool *pool = malloc(sizeof(ThreadPool));
    pool->queue = createTaskQueue(queueCapacity);

    pthread_t thread;
    for (int i = 0; i < threadCount; i++) {
	pthread_create(&thread, NULL, workerThread, pool);
	pthread_detach(thread);
    }
    return pool;
}

// 
void destroyThreadPool(ThreadPool *pool) {
    pthread_mutex_lock(&pool->queue->mutex);
    pool->queue->shutdown = 1;
    pthread_cond_broadcast(&pool->queue->cond); // Beri tahu semua thread worker
    pthread_mutex_unlock(&pool->queue->mutex);

    destroyTaskQueue(pool->queue);
    free(pool);
}

