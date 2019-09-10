# jpeg2rgb

jpeg2rgb is a simple application to take a JPEG file and decode it into 
raw RGB pixels and write those pixels to a file. It is meant to be used 
as a tool to easily generate RGB data when developing applications that 
operate on raw RGB data.

Currently, it supports writing out to RGB files that use 3 bytes per pixel.
The RGB data that is output is prepended with a simple header to assist in 
reading the data back into a program.

### RGB File Data Layout
Each RGB file has a 12 byte header giving some basic metadata that is
immediately followed by the actual RGB pixels

| Offset | Type     | Description         |
|:------:|----------|---------------------|
| 0      | uint32_t | Width of the image  |
| 4      | uint32_t | Height of the image |
| 8      | uint8_t  | Bytes per pixel     |
| 9-11   | void     | padding             |
| 12+    | uint8_t[]| RGB data            |

The total size of the RGB buffer can be derived from the data in the
header with the formula (width * height * bpp). The pitch (number of
bytes per row) is (width * bpp). Iteration through the data would look
like

```c
uint32_t i, j;
for(i = 0; i < height; i++) {
    for(j = 0; j < (width * bpp); j+=3) {
        uint8_t red = buffer[i * j];
        uint8_t blue = buffer[i * j + 1];
        uint8_t green = buffer[i * j + 2];
        // do stuff with the pixel data
    }
}
```

## Building
This project is built using CMake. It does have a dependency on 
libjpeg-turbo. This can be installed using `brew install jpeg-turbo` on macOS.

To build, run the following commands:

```
mkdir build
cd build
cmake ..
make
```

## Usage
Currently, no options are supported. Usage is simply running the command like this:

```bash
jpeg2rgb example.jpg example.rgb
```

## License
This software is licensed under the MIT License which a copy has been provided in [LICENSE](LICENSE)
