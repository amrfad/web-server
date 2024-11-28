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

// Fungsi untuk memvalidasi request (contho validasi sederhana)
bool validate_request(const HttpRequest *request) {
    // Vallidasi hanya mendukung HTTP/1.1
    return strcmp(request->protocol, "HTTP/1.1") == 0;
    /* Validasi lainnya akan ditambahkan . . . */
}

// Fungsi utama untuk menangani GET request
void handle_get_request(const char *path, char *response, size_t response_size) {
    /* Masih prototype . . . */
    if (strcmp(path, "/") == 0) {
	create_response(response, response_size, 200, "text/html", "<h1>Welcome to the homepage!</h1>");
    } else if (strcmp(path, "/about") == 0) {
	create_response(response, response_size, 200, "text/html", "<h1>About Us\nThis is our Web Server!</h1>");
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
