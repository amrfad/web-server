#ifndef GZIP_COMPRESSION_H
#define GZIP_COMPRESSION_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

/**
 * @brief Mengompresi data menggunakan algoritma gzip.
 *
 * @param input Pointer ke data asli yang akan dikompresi.
 * @param input_length Panjang data asli.
 * @param output Pointer ke buffer hasil kompresi (akan dialokasikan di dalam fungsi).
 * @param output_length Pointer untuk menyimpan panjang data hasil kompresi.
 * @return bool True jika kompresi berhasil, false jika gagal.
 */
bool compress_gzip(const unsigned char *input, size_t input_length, unsigned char **output, size_t *output_length);

#endif

