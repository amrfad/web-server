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
 *                       Buffer ini akan dialokasikan secara dinamis, 
 *                       dan perlu dibebaskan oleh pemanggil menggunakan `free`.
 * @param content_length Pointer untuk menyimpan ukuran konten file.
 * @return               true jika file berhasil dibaca, false jika terjadi kesalahan.
 */
bool read_file(const char *filepath, char **content, size_t *content_length);

/**
 * Menentukan Content-Type dari file berdasarkan ekstensi.
 * 
 * @param file_path Path ke file yang ingin diperiksa.
 * @return          String Content-Type yang sesuai (contoh: "text/html", "image/png").
 *                  Jika ekstensi tidak dikenali, akan mengembalikan "application/octet-stream".
 */
const char *get_content_type(const char *file_path);

/**
 * Memvalidasi dan menyelesaikan path file yang diminta.
 * 
 * @param root          Root direktori yang diizinkan.
 * @param path          Path relatif yang diminta oleh client.
 * @param resolved_path Buffer untuk menyimpan path absolut yang diselesaikan.
 * @param resolved_size Ukuran maksimum dari buffer `resolved_path`.
 * @return              true jika path valid dan berada dalam root direktori,
 *                      false jika path tidak valid atau keluar dari root direktori.
 */
bool validate_path(const char *root, const char *path, char *resolved_path, size_t resolved_size);

#endif
