#pragma once

#include "image.h"

#include <cmath>
#include <cstdint>
#include <fstream>

class BMPReaderException : public std::exception {
public:
    explicit BMPReaderException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

struct BMPHeader {
    unsigned char signature[2];
    uint32_t file_size;
    uint32_t reserved_bytes;
    uint32_t offset;

    uint32_t header_size;
    uint32_t dimensions[2];
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t resolution[2];
    uint32_t palette_colors;
    uint32_t important_colors;
};

class BMPObject {
public:
    explicit BMPObject(std::ifstream& file);
    void Write(std::ofstream& file);
    Image* GetImagePtr();

private:
    BMPHeader header_;
    Image bmp_image_;
};