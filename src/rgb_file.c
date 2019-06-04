//
// Created by Cameron Roe on 2019-05-29.
//

#include "../include/rgb_file.h"

#include <stdlib.h>
#include <stdio.h>

rgb_file* initialize_rgb_file(uint32_t width, uint32_t height, uint8_t bpp) {
    printf("initializing RGB file\n");
    rgb_file* new_file = (rgb_file*) malloc(sizeof(rgb_file));
    new_file->header.width = width;
    new_file->header.height = height;
    new_file->header.bpp = bpp;
    new_file->rgb_buffer_size = (width * height * bpp);
    new_file->rgb_buffer = (uint8_t*) malloc(sizeof(uint8_t) * new_file->rgb_buffer_size);
    return new_file;
}

void clean_rgb_file(rgb_file* file) {
    free(file->rgb_buffer);
    free(file);
}

int save_rgb_file(rgb_file* file, char* filename) {
    printf("Saving RGB file to disk\n");
    FILE* rgb_fd = fopen(filename, "wb");
    fwrite(&file->header.width, sizeof(uint32_t), 1, rgb_fd);
    fwrite(&file->header.height, sizeof(uint32_t), 1, rgb_fd);
    fwrite(&file->header.bpp, sizeof(uint8_t), 1, rgb_fd);
    uint8_t padding[] = {0, 0, 0};
    fwrite(&padding, sizeof(uint8_t), 3, rgb_fd);
    fwrite(file->rgb_buffer, sizeof(uint8_t), (file->header.width * file->header.height * file->header.bpp), rgb_fd);
    fclose(rgb_fd);
    return 0;
}