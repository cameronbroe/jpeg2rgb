//
// Created by Cameron Roe on 2019-06-01.
//

#ifndef JPEG2RGB_JPEG_FILE_H
#define JPEG2RGB_JPEG_FILE_H

#include <stdint.h>
#include <turbojpeg.h>
#include "rgb_file.h"

typedef struct _jpeg_header {
    uint32_t width;
    uint32_t height;
    enum TJSAMP subsampling_type;
    enum TJCS colorspace_type;
} jpeg_header;

typedef struct _jpeg_file {
    jpeg_header header;
    uint32_t jpeg_buffer_size;
    uint8_t* jpeg_buffer;
    tjhandle decompressor;
} jpeg_file;

jpeg_file* load_jpeg_file(char* filename);
void clean_jpeg_file(jpeg_file* file);
rgb_file* decode_jpeg_to_rgb(jpeg_file* jpeg);

#endif //JPEG2RGB_JPEG_FILE_H
