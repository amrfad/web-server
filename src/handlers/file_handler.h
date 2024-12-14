#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

/**
 * Membaca isi file dari path yang diberikan.
 * 
 * @param filepath       Path ke file yang akan dibaca.
 * @param content        Pointer ke buffer untuk menyimpan konten file.
 * @param content_length Pointer untuk menyimpan ukuran konten file.
 * @return               true jika file berhasil dibaca, false jika terjadi kesalahan.
 */
bool read_file(const char *file_path, unsigned char **content, size_t *content_length);

/**
 * Menentukan Content-Type dari file berdasarkan ekstensi.
 * 
 * @param file_path Path ke file yang ingin diperiksa.
 * @return          String Content-Type yang sesuai (contoh: "text/html", "image/png").
 *                  Jika ekstensi tidak dikenali, akan mengembalikan "application/octet-stream".
 */
const char *get_content_type(const char *file_path);

#endif
