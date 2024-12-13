#include "gzip_compression.h"
#include <stdio.h>

// Fungsi untuk mengompresi data menggunakan gzip
bool compress_gzip(const unsigned char *input, size_t input_length, unsigned char **output, size_t *output_length) {
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    size_t max_output_size = compressBound(input_length);
    *output = malloc(max_output_size);
    if (!*output) return false;

    stream.next_in = (Bytef *)input;
    stream.avail_in = input_length;
    stream.next_out = (Bytef *)*output;
    stream.avail_out = (max_output_size <= 210) ? 210 : max_output_size * 1.1;

    if (deflateInit2(&stream, Z_BEST_COMPRESSION, Z_DEFLATED, 15 | 16, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        free(*output);
        return false;
    }

    int ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        fprintf(stderr, "Compression failed with error %d\n", ret);
        deflateEnd(&stream);
        free(*output);
        return false;
    }

    *output_length = stream.total_out;
    deflateEnd(&stream);
    return true;
}

