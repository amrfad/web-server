#include "server.h"

int main() {
    // Tangani keyboard interrupt
    signal(SIGINT, handle_signal);

    // Inisialisasi server
    server_fd = initialize_server();

    while (1) {
	accept_client(server_fd);
    }

    return 0;
}
