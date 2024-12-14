#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Struktur untuk menyimpan query parameter (key-value pair)
typedef struct {
    char key[64];
    char value[256];
} QueryParam;

// Struktur untuk menyimpan header (key-value pair)
typedef struct {
    char key[64];
    char value[256];
} Header;

// Struktur untuk menyimpan key-value dari body POST
typedef struct {
    char key[64];
    char value[256];
} BodyParam;

// Struktur untuk menyimpan keseluruhan HTTP request
typedef struct {
    char method[16];
    char path[256];
    QueryParam *params;
    size_t param_count;
    char protocol[16];
    Header *headers;
    size_t header_count;
    BodyParam *body_params;
    size_t body_param_count;
} HttpRequest;

/**
 * Parse query parameters dari path.
 * 
 * @param path        Path dengan query string (contoh: "/index.html?lang=en").
 * @param params      Array untuk menyimpan query parameters.
 * @param param_count Pointer untuk jumlah query parameters.
 * @return            1 jika sukses, 0 jika tidak ada query parameters.
 */
int parse_query_params(const char *path, QueryParam *params, size_t *param_count);

/**
 * Parse headers dari request.
 * 
 * @param request      HTTP request lengkap.
 * @param headers      Array untuk menyimpan headers.
 * @param header_count Pointer untuk jumlah headers.
 * @return             1 jika sukses.
 */
int parse_headers(const char *request, Header *headers, size_t *header_count);

/**
 * Parse body POST ke key-value pairs.
 *
 * @param body       String body.
 * @param params     Array untuk menyimpan key-value pairs.
 * @param param_count Pointer untuk jumlah key-value pairs.
 * @return           1 jika sukses, 0 jika gagal.
 */
int parse_body_params(const char *body, BodyParam *params, size_t *param_count);

/**
 * Parse keseluruhan HTTP request.
 * 
 * @param raw_request  String HTTP request lengkap.
 * @param request      Pointer ke struct HttpRequest untuk hasil parsing.
 * @return             1 jika sukses.
 */
int parse_http_request(const char *raw_request, HttpRequest *request);

/**
 * Bebaskan memori yang dialokasikan untuk HttpRequest.
 * 
 * @param request Pointer ke HttpRequest.
 */
void free_http_request(HttpRequest *request);

// Hanya untuk debug
#ifdef DEBUG
/**
 * @brief Mencetak query parameter yang ada dalam HTTP request.
 *
 * @param params Array query parameter.
 * @param param_count Jumlah query parameter.
 */
void print_query_params(QueryParam *params, size_t param_count);

/**
 * @brief Mencetak header yang ada dalam HTTP request.
 *
 * @param headers Array header.
 * @param header_count Jumlah header.
 */
void print_headers(Header *headers, size_t header_count);

/**
 * @brief Mencetak body parameter yang ada dalam HTTP request.
 *
 * @param params Array body parameter.
 * @param param_count Jumlah body parameter.
 */
void print_body_params(BodyParam *params, size_t param_count);

/**
 * @brief Mencetak keseluruhan detail HTTP request.
 *
 * @param request Pointer ke struktur HttpRequest.
 */
void print_http_request(const HttpRequest *request);
#endif

#endif
