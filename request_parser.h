#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

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

// Struktur untuk menyimpan keseluruhan HTTP request
typedef struct {
    char method[16];
    char path[256];
    QueryParam *params;
    size_t param_count;
    char protocol[16];
    Header *headers;
    size_t header_count;
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

#endif
