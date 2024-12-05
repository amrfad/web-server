#include "server.h"
#include "thread_pool.h"

// Variabel global untuk socket server
int server_fd;

int keep_running = 1;

// Prosedur untuk menangani keyboard interrupt
void handle_signal(int sig) {
    if (sig == SIGINT) {
	printf("\nReceived SIGINT (CTRL+C). Shutting down server...\n");
        keep_running = 0;
        if (server_fd > 0) {
            close(server_fd);  // Tutup server socket
	    destroyThreadPool(pool);
	    exit(EXIT_SUCCESS);
        }
    }
}

// Inisialisasi server
int initialize_server() {
    // Membuat socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
	perror("Socket creation failed!");
	exit(EXIT_FAILURE);
    }

    // Opsi socket
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
	perror("Socket options failed!");
	exit(EXIT_FAILURE);
    }

    // Setup server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
	perror("Bind failed!");
	exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(fd, 10) < 0) {
	perror("Listen failed!");
	exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");
    return fd;
}

// Proses permintaan client
void handle_client(int client_fd) {
    // Read data from client
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
	// Parsing request dan mengirimkan response
	HttpRequest request;
	if (parse_http_request(buffer, &request)) {
	    char response[8192];
	    handle_request(&request, response, sizeof(response));
	    free_http_request(&request);
	    
	    #ifdef DEBUG
		printf("%s\n", response);
	    #endif
	    
	    // Send response to client
	    usleep(1000);
	    send(client_fd, response, strlen(response), 0);
	}
    }
	
    // Close client socket
    close(client_fd);
}

// Terima koneksi client
void accept_client(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd;

    while (keep_running) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (!keep_running) break;  // Keluar jika server diminta berhenti

        if (client_fd < 0) {
            if (errno == EINTR) continue;  // Sinyal diterima, lanjutkan loop
            perror("Accept failed!");
            return;
        }
        
        printf("New client connected\n");
        enqueue(pool->queue, client_fd);
    }
}
