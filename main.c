#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "http_request.h"
#include "http_response.h"

#define BUFFER_SIZE 1024

int server_fd;

void handle_signal(int sig) {
    if (sig == SIGINT) {
	printf("\nReceived SIGINT (CTRL+C). Shutting down server...\n");
	if (server_fd > 0) {
	    // Close server socket
	    close(server_fd);
	}
	exit(EXIT_SUCCESS);
    }
}

int main() {
    // Setup signal handler
    signal(SIGINT, handle_signal);

    // Membuat socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
	perror("Socket creation failed!");
	exit(EXIT_FAILURE);
    }

    // Setup server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
	perror("Bind failed!");
	exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 10) < 0) {
	perror("Listen failed!");
	exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    while(1) {
	// Accept connection
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	
	if (client_fd < 0) {
	    perror("Accept failed!");
	    continue;
	}
	
	printf("New client connected\n");

	// Read data from client
	char buffer[BUFFER_SIZE] = {0};
	ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received > 0) {
	    // Test HTTP parser and handler
	    HttpRequest request;
	    if (parse_http_request(buffer, &request)) {
		char response[1024];
		handle_request(&request, response, sizeof(response));
		// printf("%s\n", response);
		free_http_request(&request);

		// Send response to client
		send(client_fd, response, strlen(response), 0);
	    }
	}
	
	// Close client socket
	close(client_fd);
    }
}
