#include "file_handler.h"

// Fungsi untuk membaca file dari path
bool read_file(const char *file_path, unsigned char **content, size_t *content_length) {
    int fd = open(file_path, O_RDONLY);
    if (fd < 0) return false;

    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0) {
        close(fd);
        return false;
    }

    *content_length = file_stat.st_size;
    *content = malloc(*content_length);
    if (!*content) {
        close(fd);
        return false;
    }

    if (read(fd, *content, *content_length) != (ssize_t)*content_length) {
        free(*content);
        close(fd);
        return false;
    }

    close(fd);
    return true;
}

// Fungsi untuk mendapatkan Content-Type berdasarkan ekstensi file
const char *get_content_type(const char *file_path) {
    const char *ext = strrchr(file_path, '.');
    if (!ext) return "application/octet-stream"; // Default tipe file
    
    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".css") == 0) return "text/css";
    if (strcmp(ext, ".js") == 0) return "application/javascript";
    if (strcmp(ext, ".png") == 0) return "image/png";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif") == 0) return "image/gif";
    if (strcmp(ext, ".txt") == 0) return "text/plain";

    return "application/octet-stream"; // Default untuk tipe tidak dikenal
}

// Fungsi untuk memvalidasi path agar tetap dalam root direktori
bool validate_path(const char *root, const char *path, char *resolved_path, size_t resolved_size) {
    char temp_path[512];
    snprintf(temp_path, sizeof(temp_path), "%s%s", root, path); // Gabungkan root dengan path

    // Konversi ke path absolut
    if (realpath(temp_path, resolved_path) == NULL) {
        return false; // Gagal menyelesaikan path
    }

    // Memastikan resolved_path berada di dalam root direktori
    if (strncmp(root, resolved_path, strlen(root)) != 0) {
        printf("\n\n\n$%s %s\n\n\n", root, resolved_path);
        return false; // Path di luar root direktori
    }

    return true;
}
