#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "http_request.h"
#include "http_response.h"

#define BUFFER_SIZE 1024

extern int server_fd;


void handle_signal(int sig);


int initialize_server();


void handle_client(int client_fd);


void accept_client(int server_fd);

#endif
