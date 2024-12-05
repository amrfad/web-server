#include "server.h"
#include "thread_pool.h"

int main() {
    // Tangani keyboard interrupt
    signal(SIGINT, handle_signal);

    // Inisialisasi server
    server_fd = initialize_server();
    
    // Inisialisasi Thread Pool
    pool = createThreadPool(THREAD_POOL_SIZE, MAX_QUEUE);

    // Menerima client
    accept_client(server_fd);
    
    // 
    destroyThreadPool(pool);
    return 0;
}
