#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include "http_request.h"
#include "file_handler.h"
#include "gzip_compression.h"

/**
 * @brief Mengembalikan pesan status berdasarkan kode status HTTP.
 *
 * @param status_code Kode status HTTP (contoh: 200, 404, 500).
 * @return Pesan status yang sesuai (contoh: "OK", "Not Found").
 */
const char *get_status_message(int status_code);

/**
 * @brief Membuat respons HTTP lengkap.
 *
 * @param buffer Buffer untuk menyimpan respons HTTP.
 * @param buffer_size Ukuran maksimal buffer.
 * @param status_code Kode status HTTP untuk respons (contoh: 200, 404).
 * @param content_type Jenis konten untuk header `Content-Type` (contoh: "text/html").
 * @param body Isi body respons (contoh: "<h1>Hello, World!</h1>").
 */
void create_response(unsigned char *buffer, size_t buffer_size, int status_code, 
                     const char *content_type, const unsigned char *body, size_t body_length);


void create_response_with_encoding(unsigned char *buffer, size_t buffer_size, int status_code, 
                                   const char *content_type, const unsigned char *body, size_t body_length, 
                                   const char *content_encoding);

/**
 * @brief Memvalidasi request HTTP untuk memastikan formatnya benar.
 *
 * @param request Pointer ke struct HttpRequest.
 * @return true jika valid, false jika tidak valid.
 */
bool validate_request(const HttpRequest *request);

/**
 * @brief Menangani request dengan metode GET berdasarkan path yang diminta.
 *
 * @param request Hasil parsing dari HTTP request
 * @param response Buffer untuk menyimpan respons HTTP.
 * @param response_size Ukuran maksimal buffer respons.
 */
void handle_get_request(const HttpRequest *request, unsigned char *response, size_t response_size);

/**
 * @brief Menangani request HTTP berdasarkan metode dan path.
 *
 * @param request Pointer ke struct HttpRequest yang berisi detail request.
 * @param response Buffer untuk menyimpan respons HTTP.
 * @param response_size Ukuran maksimal buffer respons.
 */
void handle_request(HttpRequest *request, unsigned char *response, size_t response_size);

#endif
