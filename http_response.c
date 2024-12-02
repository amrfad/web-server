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

// Fungsi untuk membuat respons HTTP
void create_response(char *buffer, size_t buffer_size, int status_code, 
                     const char *content_type, const char *body) {

    const char *status_message = get_status_message(status_code);
    size_t body_length = strlen(body);

    snprintf(buffer, buffer_size,
	     "HTTP/1.1 %d %s\r\n"
	     "Content-Type: %s\r\n"
	     "Content-Length: %zu\r\n"
	     "\r\n"
	     "%s",
	     status_code, status_message,
	     content_type, body_length,
	     body);
}

// Fungsi untuk memvalidasi request (contoh validasi sederhana)
bool validate_request(const HttpRequest *request) {
    // Vallidasi hanya mendukung HTTP/1.1 dan HTTP/1.0
    return (strcmp(request->protocol, "HTTP/1.1") == 0) || (strcmp(request->protocol, "HTTP/1.0") == 0);
    /* Validasi lainnya akan ditambahkan . . . */
}

// Fungsi utama untuk menangani GET request
void handle_get_request(const char *path, char *response, size_t response_size) {
    char file_path[512];
    const char *root = "./www";
    snprintf(file_path, sizeof(file_path), "%s%s", root, path); // Root direktori ./www
    
    // Default ke index.html jika path adalah direktori
    struct stat path_stat;
    if (stat(file_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
	strncat(file_path, "/index.html", sizeof(file_path) - strlen(file_path) - 1);
    }
    
    // Basic directory protection (masih prototype . . .)
    char resolved_path[512];
    if (!validate_path(root, path, resolved_path, sizeof(resolved_path))) {
	create_response(response, response_size, 403, "text/html", "<h1>403 Forbidden</h1>");
    }

    // Baca file
    char *file_content = NULL;
    size_t file_size = 0;
    if (read_file(file_path, &file_content, &file_size)) {
	const char *content_type = get_content_type(file_path);
	create_response(response, response_size, 200, content_type, file_content);
	free(file_content);
    } else {
	create_response(response, response_size, 404, "text/html", "<h1>404 Not Found</h1>");
    }
}

// Fungsi utama untuk menangani request HTTP
void handle_request(HttpRequest *request, char *response, size_t response_size) {
    // Validasi request
    if (!validate_request(request)) {
	create_response(response, response_size, 400, "text/html", "<h1>400 Bad Request</h1>");
	return;
    }

    // Routing berdasarkan metode HTTP
    if (strcmp(request->method, "GET") == 0) {
	handle_get_request(request->path, response, response_size);
    } else if (strcmp(request->method, "POST") == 0) {
	create_response(response, response_size, 501, "text/html", "<h1>501 Method Not Implemented</h1>");
    } else {
	create_response(response, response_size, 405, "text/html","<h1>405 Method Not Allowed</h1>");
    }
}
