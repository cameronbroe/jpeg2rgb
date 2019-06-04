#include <stdio.h>
#include <turbojpeg.h>

#include "../include/jpeg_file.h"
#include "../include/rgb_file.h"

#define VERSION "0.1"

void print_help() {
    printf("jpeg2rgb %s\n", VERSION);
    printf("USAGE\n");
    printf("\tjpeg2rgb [jpeg_source_file] [rgb_dest_file]\n");
}

int main(int argc, char** argv) {
    if(argc != 3) {
        print_help();
        return -9;
    }
    char* jpeg_file_path = argv[1];
    char* rgb_file_path = argv[2];
    jpeg_file* jpeg_file = load_jpeg_file(jpeg_file_path);
    rgb_file* rgb_file = decode_jpeg_to_rgb(jpeg_file);
    save_rgb_file(rgb_file, rgb_file_path);
    clean_jpeg_file(jpeg_file);
    clean_rgb_file(rgb_file);
    return 0;
}