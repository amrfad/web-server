#ifndef PROCESS_POOL_H
#define PROCESS_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "server.h" // Untuk handle_client()

#define PROCESS_POOL_SIZE 16

// Struktur data untuk Process Pool
typedef struct {
    pid_t workers[PROCESS_POOL_SIZE];
} ProcessPool;

extern ProcessPool *pool;
extern pid_t parent_pid;

/**
 * @brief Membuat kumpulan proses worker untuk menangani koneksi.
 *
 * @param processCount Jumlah proses worker yang akan dibuat.
 * @param serverSocket Socket server yang akan digunakan worker.
 * @return Pointer ke struktur ProcessPool yang baru dibuat.
 */
ProcessPool* createProcessPool(int processCount, int serverSocket);

/**
 * @brief Membersihkan dan menghentikan semua proses worker.
 *
 * @param pool Pointer ke struktur ProcessPool yang akan dihancurkan.
 */
void destroyProcessPool(ProcessPool *pool);

#endif

