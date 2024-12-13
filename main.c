#include "server.h"
#include "process_pool.h"

int main() {
    parent_pid = getpid(); // Simpan PID parent
    signal(SIGINT, handle_signal); // Tangani SIGINT

    server_fd = initialize_server(); // Inisialisasi server

    pool = createProcessPool(PROCESS_POOL_SIZE, server_fd); // Inisialisasi process pool

    // Proses utama hanya menunggu hingga ada sinyal untuk shutdown
    while (keep_running) {
        pause(); // Tunggu sinyal
    }

    destroyProcessPool(pool); // Cleanup jika ada kesalahan
    return 0;
}

