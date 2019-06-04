//
// Created by Cameron Roe on 2019-06-01.
//

#include "../include/jpeg_file.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

jpeg_file* initialize_jpeg_file() {
    printf("initializing jpeg_file object\n");
    jpeg_file* file = (jpeg_file*) malloc(sizeof(jpeg_file));
    return file;
}

jpeg_header parse_jpeg_header(jpeg_file* file) {
    printf("about to parse JPEG header\n");
    int width, height, ss_type, cs_type;
    int header_success;
    header_success = tjDecompressHeader3(file->decompressor,
            file->jpeg_buffer,
            file->jpeg_buffer_size,
            &width,
            &height,
            &ss_type,
            &cs_type);
    if(header_success < 0) {
        jpeg_header empty_header;
        fprintf(stderr, "could not decompress header of JPEG file: %s\n", tjGetErrorStr2(file->decompressor));
        return empty_header;
    }
    printf("got data:\n");
    printf("\twidth: %i\n", width);
    printf("\theight: %i\n", height);
    printf("\tsubsampling_type: %i\n", ss_type);
    printf("\tcolorspace_type: %i\n", cs_type);
    jpeg_header file_header;
    file_header.width = width;
    file_header.height = height;
    file_header.colorspace_type = cs_type;
    file_header.subsampling_type = ss_type;

    return file_header;
}

jpeg_file* load_jpeg_file(char* filename) {
    printf("starting to load JPEG file: %s\n", filename);
    jpeg_file* file = initialize_jpeg_file();

    printf("opening file: %s\n", filename);
    FILE* jpeg_fd = fopen(filename, "r");
    if(jpeg_fd) {
        printf("getting size of JPEG file\n");
        fseek(jpeg_fd, 0, SEEK_END);
        size_t file_size = ftell(jpeg_fd);
        fseek(jpeg_fd, 0, SEEK_SET);
        printf("got size: %lu\n", file_size);

        file->jpeg_buffer_size = file_size;
        file->jpeg_buffer = (uint8_t *) malloc(sizeof(uint8_t) * file_size);
        printf("reading file into buffer\n");
        fread(file->jpeg_buffer, sizeof(uint8_t), file_size, jpeg_fd);

        printf("initializing decompressor\n");
        file->decompressor = tjInitDecompress();

        if(file->decompressor) {
            jpeg_header header_data = parse_jpeg_header(file);
            file->header = header_data;

            return file;
        } else {
            fprintf(stderr, "unable to initialize JPEG decompressor: %s\n", tjGetErrorStr2(NULL));
        }
    } else {
        fprintf(stderr, "unable to open %s: %s\n", filename, strerror(errno));
        return NULL;
    }
}

rgb_file* decode_jpeg_to_rgb(jpeg_file* jpeg) {
    rgb_file* rgb = initialize_rgb_file(jpeg->header.width, jpeg->header.height, 3);
    tjDecompress2(
            jpeg->decompressor,
            (unsigned char*) jpeg->jpeg_buffer,
            (unsigned long) jpeg->jpeg_buffer_size,
            (unsigned char*) rgb->rgb_buffer,
            jpeg->header.width,
            jpeg->header.width * 3,
            jpeg->header.height,
            TJCS_RGB,
            0
    );
    return rgb;
}

void clean_jpeg_file(jpeg_file* file) {
    free(file->jpeg_buffer);
    free(file);
}