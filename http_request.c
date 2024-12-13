#include "http_request.h"

// Parse query parameters dari path.
int parse_query_params(const char *path, QueryParam *params, size_t *param_count) {
    const char *query_start = strchr(path, '?');
    if (!query_start) {
	// Jika tidak ada query parameters
	*param_count = 0;
	return 0;
    }

    query_start++;
    char query[1024];
    strncpy(query, query_start, sizeof(query));
    query[sizeof(query) - 1] = '\0'; // Null terminate string

    char *pair = strtok(query, "&");
    size_t count = 0;

    while (pair && count < *param_count) {
	char *equals = strchr(pair, '=');
	if (equals) {
	    *equals = '\0'; // Memisahkan key dan value
	    strncpy(params[count].key, pair, sizeof(params[count].key));
	    strncpy(params[count].value, equals + 1, sizeof(params[count].value));
	} else {
	    strncpy(params[count].key, pair, sizeof(params[count].key));
	    params[count].value[0] = '\0';
	}
	count++;
	pair = strtok(NULL, "&");
    }

    *param_count = count;
    return 1;
}

// Parse headers dari request.
int parse_headers(const char *request, Header *headers, size_t *header_count) {
    const char *line_start = strstr(request, "\r\n") + 2;
    size_t count = 0;

    while (line_start && count < *header_count) {
	const char *line_end = strstr(line_start, "\r\n");
	if (!line_end || line_start == line_end) { // Baris kosong (akhir header)
	    break;
	}

	char line[1024];
	size_t line_len = line_end - line_start;
	strncpy(line, line_start, line_len);
	line[line_len] = '\0';

	char *colon = strchr(line, ':');
	if (colon) {
	    *colon = '\0'; // Pisahkan key dan value
	    strncpy(headers[count].key, line, sizeof(headers[count]));
	    strncpy(headers[count].value, colon + 2, sizeof(headers[count])); // Melewati spasi setelah :
	}

	count++;
	line_start = line_end + 2; // Pindah ke baris berikutnya
    }

    *header_count = count;
    return 1;
}

// Parse keseluruhan HTTP request.
int parse_http_request(const char *raw_request, HttpRequest *request) {
    // Parse request line
    const char *request_line_end = strstr(raw_request, "\r\n");
    if (!request_line_end) {
	return 0; // Format tidak valid
    }

    char request_line[1024];
    size_t line_len = request_line_end - raw_request;
    strncpy(request_line, raw_request, line_len);
    request_line[line_len] = '\0';

    sscanf(request_line, "%s %s %s", request->method, request->path, request->protocol);

    // Parse query parameters
    QueryParam params[16];
    size_t param_count = 16;
    parse_query_params(request->path, params, &param_count);

    // Alokasi memori untuk params
    request->param_count = param_count;
    request->params = malloc(param_count * sizeof(QueryParam));
    for (size_t i = 0; i < param_count; i++) {
	request->params[i] = params[i];
    }

    // Parse headers
    Header headers[16];
    size_t header_count = 16;
    parse_headers(raw_request, headers, &header_count);

    // Alokasi memori untuk headers
    request->header_count = header_count;
    request->headers = malloc(header_count * sizeof(Header));
    for (size_t i = 0; i < header_count; i++) {
	request->headers[i] = headers[i];
    }

    return 1;
}

// Bebaskan memori yang dialokasikan untuk HttpRequest.
void free_http_request(HttpRequest *request) {
    free(request->params);
    free(request->headers);
}

#ifdef DEBUG
// Mencetak query parameter yang ada dalam HTTP request.
void print_query_params(QueryParam *params, size_t param_count) {
    printf("Query Parameters (%zu):\n", param_count);
    for (size_t i = 0; i < param_count; i++) {
        printf("  %s: %s\n", params[i].key, params[i].value);
    }
}

// Mencetak header yang ada dalam HTTP request.
void print_headers(Header *headers, size_t header_count) {
    printf("Headers (%zu):\n", header_count);
    for (size_t i = 0; i < header_count; i++) {
        printf("  %s: %s\n", headers[i].key, headers[i].value);
    }
}

// Mencetak keseluruhan detail HTTP request.
void print_http_request(const HttpRequest *request) {
    printf("HTTP Request Details:\n");
    printf("  Method: %s\n", request->method);
    printf("  Path: %s\n", request->path);
    printf("  Protocol: %s\n", request->protocol);
    
    print_query_params(request->params, request->param_count);
    print_headers(request->headers, request->header_count);
}
#endif
