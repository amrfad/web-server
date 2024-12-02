#include "thread_pool.h"

// Fungsi untuk membuat antiran tugas/permintaan clien
TaskQueue* createTaskQueue(int capacity) {
    TaskQueue *queue = malloc(sizeof(TaskQueue));
    queue->tasks = malloc(sizeof(int) * capacity);
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}

// 
void destroyTaskQueue(TaskQueue *queue) {
    free(queue->tasks);
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cond);
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
int dequeue(TaskQueue *queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->size == 0) {
	pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    int task = queue->tasks[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
    return task;
}

//
void* workerThread(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    while (1) {
	int clientSocket = dequeue(pool->queue);

	// Kode di sini
	////////////////////
	////////////////////
	
	close(clientSocket);
    }
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
    destroyTaskQueue(pool->queue);
    free(pool);
}
