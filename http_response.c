#include "http_response.h"

// Fungsi untuk mendapatkan pesan status berdasarkan status code
const char *get_status_message(int status_code) {
    switch (status_code) {
        case 200: return "OK";
        case 400: return "Bad Request";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 500: return "Internal Server Error";
        default: return "Unknown";
    }
}

// Fungsi untuk membuat respons HTTP sederhana
void create_response(unsigned char *buffer, size_t buffer_size, int status_code, 
                     const char *content_type, const unsigned char *body, size_t body_length) {
    const char *status_message = get_status_message(status_code);
    snprintf((char *)buffer, buffer_size,
             "HTTP/1.1 %d %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "\r\n",
             status_code, status_message, content_type, body_length);
    memcpy(buffer + strlen((char *)buffer), body, body_length);
}

// Fungsi untuk membuat respons HTTP dengan encoding
void create_response_with_encoding(unsigned char *buffer, size_t buffer_size, int status_code, 
                                   const char *content_type, const unsigned char *body, size_t body_length, 
                                   const char *content_encoding) {
    const char *status_message = get_status_message(status_code);

    snprintf((char *)buffer, buffer_size,
             "HTTP/1.1 %d %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "Content-Encoding: %s\r\n"
             "\r\n",
             status_code, status_message, content_type, body_length, content_encoding);
    memcpy(buffer + strlen((char *)buffer), body, body_length);
}

// Fungsi untuk memvalidasi request (contoh validasi sederhana)
bool validate_request(const HttpRequest *request) {
    return (strcmp(request->protocol, "HTTP/1.1") == 0 || strcmp(request->protocol, "HTTP/1.0") == 0);
}

// Fungsi utama untuk menangani GET request
void handle_get_request(const HttpRequest *request, unsigned char *response, size_t response_size) {
    char file_path[512];
    const char *root = "./www";
    snprintf(file_path, sizeof(file_path), "%s%s", root, request->path);

    struct stat path_stat;
    if (stat(file_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
        strncat(file_path, "/index.html", sizeof(file_path) - strlen(file_path) - 1);
    }

    bool supports_gzip = false;
    for (size_t i = 0; i < request->header_count; i++) {
        if (strcasecmp(request->headers[i].key, "Accept-Encoding") == 0 &&
            strstr(request->headers[i].value, "gzip") != NULL) {
            supports_gzip = true;
            break;
        }
    }

    unsigned char *file_content = NULL;
    size_t file_size = 0;

    if (read_file(file_path, &file_content, &file_size)) {
        const char *content_type = get_content_type(file_path);

        if (supports_gzip) {
            unsigned char *compressed_content = NULL;
            size_t compressed_size = 0;

            if (compress_gzip(file_content, file_size, &compressed_content, &compressed_size)) {
                create_response_with_encoding(response, response_size, 200, content_type, 
                                              compressed_content, compressed_size, "gzip");
                free(compressed_content);
            } else {
                create_response(response, response_size, 500, "text/html", (unsigned char *)"<h1>500 Internal Server Error</h1>", strlen("<h1>500 Internal Server Error</h1>"));
            }
        } else {
            create_response(response, response_size, 200, content_type, file_content, file_size);
        }

        free(file_content);
    } else {
        create_response(response, response_size, 404, "text/html", (unsigned char *)"<h1>404 Not Found</h1>", strlen("<h1>404 Not Found</h1>"));
    }
}

// Fungsi utama untuk menangani request HTTP
void handle_request(HttpRequest *request, unsigned char *response, size_t response_size) {
    if (!validate_request(request)) {
        create_response(response, response_size, 400, "text/html", (unsigned char *)"<h1>400 Bad Request</h1>", strlen("<h1>400 Bad Request</h1>"));
        return;
    }

    if (strcmp(request->method, "GET") == 0) {
        handle_get_request(request, response, response_size);
    } else if (strcmp(request->method, "POST") == 0) {
        create_response(response, response_size, 501, "text/html", (unsigned char *)"<h1>501 Method Not Implemented</h1>", strlen("<h1>501 Method Not Implemented</h1>"));
    } else {
        create_response(response, response_size, 405, "text/html", (unsigned char *)"<h1>405 Method Not Allowed</h1>", strlen("<h1>405 Method Not Allowed</h1>"));
    }
}
