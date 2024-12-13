#include "process_pool.h"

ProcessPool *pool;
pid_t parent_pid;

// Shutdown flag untuk worker
static volatile int shutdown_flag = 0;

// Handler untuk sinyal SIGTERM (digunakan oleh worker)
void handle_worker_shutdown(int sig) {
    shutdown_flag = 1;
}

// Fungsi utama untuk worker
void workerProcess(int serverSocket) {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    // Pasang handler untuk shutdown
    signal(SIGTERM, handle_worker_shutdown);

    while (!shutdown_flag) {
        // Terima koneksi klien
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            if (shutdown_flag) break; // Keluar jika ada sinyal shutdown
            perror("accept");
            continue;
        }
        printf("New client connected\n");

        // Tangani permintaan klien
        handle_client(clientSocket);

        // Tutup koneksi klien
        close(clientSocket);
    }

    exit(EXIT_SUCCESS);
}

// Membuat process pool
ProcessPool* createProcessPool(int processCount, int serverSocket) {
    ProcessPool *pool = malloc(sizeof(ProcessPool));

    for (int i = 0; i < processCount; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process menjalankan worker
            workerProcess(serverSocket);
        } else {
            // Parent menyimpan PID worker
            pool->workers[i] = pid;
        }
    }

    return pool;
}

// Menghancurkan process pool
void destroyProcessPool(ProcessPool *pool) {
    // Kirim sinyal SIGTERM ke semua worker
    for (int i = 0; i < PROCESS_POOL_SIZE; i++) {
        kill(pool->workers[i], SIGTERM);
        waitpid(pool->workers[i], NULL, 0); // Tunggu setiap worker selesai
    }

    free(pool);
}

