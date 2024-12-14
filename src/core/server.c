#include "server.h"
#include "process_pool.h"

// Variabel global untuk socket server
int server_fd;
int keep_running = 1;

// Prosedur untuk menangani SIGINT
void handle_signal(int sig) {
    if (sig == SIGINT) {

	if (getpid() == parent_pid) {
	    printf("\nReceived SIGINT (CTRL+C). Shutting down server...\n");
	}
	
        keep_running = 0;
        if (server_fd > 0) {
            close(server_fd);       // Tutup server socket
            destroyProcessPool(pool); // Hentikan semua worker
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
	    #ifdef DEBUG
	    print_http_request(&request);
	    #endif

	    unsigned char response[MAX_RESPONSE_SIZE];
	    handle_request(&request, response, sizeof(response));
	    #ifdef DEBUG
	    printf("%s\n", response);
	    #endif
	    free_http_request(&request);
	    
	    // Send response to client
	    send(client_fd, response, sizeof(response), 0);
	}
    }
	
    // Close client socket
    close(client_fd);
}
