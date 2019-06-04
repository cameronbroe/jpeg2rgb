//
// Created by Cameron Roe on 2019-05-29.
//

#ifndef JPEG2RGB_RGB_FILE_H
#define JPEG2RGB_RGB_FILE_H

#include <stdint.h>

typedef struct _rgb_header {
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
} rgb_header;

typedef struct _rgb_file {
    rgb_header header;
    uint32_t rgb_buffer_size;
    uint8_t* rgb_buffer;
} rgb_file;

rgb_file* initialize_rgb_file(uint32_t width, uint32_t height, uint8_t bpp);
void clean_rgb_file(rgb_file* file);
int save_rgb_file(rgb_file* file, char* filename);

#endif //JPEG2RGB_RGB_FILE_H
