#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
//#include <netinet/in.h>
//#include <sys/socket.h>

#define MAX_QUEUE 10
#define THREAD_POOL_SIZE 8

// Struktur data untuk menyimpan antrian permintaan HTTP
typedef struct {
    int *tasks;
    int capacity;
    int size;
    int front;
    int rear;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} TaskQueue;

// Struktur data untuk thread pool
typedef struct {
    TaskQueue *queue;
} ThreadPool;


TaskQueue* createTaskQueue(int capacity);


void destroyTaskQueue(TaskQueue *queue);


void enqueue(TaskQueue *queue, int task);


int dequeue(TaskQueue *queue);


void* workerThread(void *arg);


ThreadPool* createThreadPool(int threadCount, int queueCapacity);


void destroyThreadPool(ThreadPool *pool);


#endif
