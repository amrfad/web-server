#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "http_request.h"
#include "http_response.h"

#define BUFFER_SIZE 1024
#define MAX_RESPONSE_SIZE 2 * 1024 * 1024

extern int server_fd;
extern int keep_running;

/**
 * @brief Menangani sinyal yang diterima oleh server, khususnya SIGINT.
 *
 * @param sig Nomor sinyal yang diterima.
 */
void handle_signal(int sig);

/**
 * @brief Menginisialisasi socket server.
 *
 * @return File descriptor socket yang telah dikonfigurasi.
 */
int initialize_server();

/**
 * @brief Memproses koneksi dari client yang terhubung.
 *
 * @param client_fd File descriptor socket client.
 */
void handle_client(int client_fd);

#endif
