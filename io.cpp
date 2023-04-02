#include "io.h"

BMPReaderException::BMPReaderException(const std::string &message) {
    message_ = "BMPReader exception. Message: " + message;
}
const char *BMPReaderException::what() const noexcept {
    return message_.c_str();
}

BMPObject::BMPObject(std::ifstream &file) {
    file.read(reinterpret_cast<char *>(&header_.signature), sizeof(header_.signature));
    file.read(reinterpret_cast<char *>(&header_.file_size), sizeof(header_.file_size));
    file.read(reinterpret_cast<char *>(&header_.reserved_bytes), sizeof(header_.reserved_bytes));
    file.read(reinterpret_cast<char *>(&header_.offset), sizeof(header_.offset));
    file.read(reinterpret_cast<char *>(&header_.header_size), sizeof(header_.header_size));
    file.read(reinterpret_cast<char *>(&header_.dimensions), sizeof(header_.dimensions));
    file.read(reinterpret_cast<char *>(&header_.color_planes), sizeof(header_.color_planes));
    file.read(reinterpret_cast<char *>(&header_.bits_per_pixel), sizeof(header_.bits_per_pixel));
    file.read(reinterpret_cast<char *>(&header_.compression), sizeof(header_.compression));
    file.read(reinterpret_cast<char *>(&header_.image_size), sizeof(header_.image_size));
    file.read(reinterpret_cast<char *>(&header_.resolution), sizeof(header_.resolution));
    file.read(reinterpret_cast<char *>(&header_.palette_colors), sizeof(header_.palette_colors));
    file.read(reinterpret_cast<char *>(&header_.important_colors), sizeof(header_.important_colors));

    const int expected_bpp = 24;
    if (header_.bits_per_pixel != expected_bpp) {
        throw BMPReaderException("something wrong with input file.");
    }
    ImageMatrix new_image;
    const size_t row_const = 32.0;
    const double color_coeff = 255.0;
    size_t row_size = static_cast<size_t>(
        std::ceil(static_cast<double>(header_.bits_per_pixel * header_.dimensions[0]) / row_const) * 4);
    for (size_t i = 0; i < header_.dimensions[1]; ++i) {
        uint8_t row[row_size];
        std::vector<RGB> image_row;
        file.read(reinterpret_cast<char *>(&row), static_cast<std::streamsize>(sizeof(row)));
        for (size_t j = 0; j < header_.dimensions[0]; ++j) {
            uint8_t r = static_cast<uint8_t>(row[j * 3 + 2]);
            uint8_t g = static_cast<uint8_t>(row[j * 3 + 1]);
            uint8_t b = static_cast<uint8_t>(row[j * 3]);
            image_row.emplace_back(static_cast<double>(r) / color_coeff, static_cast<double>(g) / color_coeff,
                                   static_cast<double>(b) / color_coeff);
        }
        new_image.push_back(image_row);
    }
    std::reverse(new_image.begin(), new_image.end());
    bmp_image_ = Image(new_image);
    file.close();
}

void BMPObject::Write(std::ofstream &file) {
    header_.dimensions[0] = bmp_image_.GetWidth();
    header_.dimensions[1] = bmp_image_.GetHeight();
    file.write(reinterpret_cast<char *>(&header_.signature), sizeof(header_.signature));
    file.write(reinterpret_cast<char *>(&header_.file_size), sizeof(header_.file_size));
    file.write(reinterpret_cast<char *>(&header_.reserved_bytes), sizeof(header_.reserved_bytes));
    file.write(reinterpret_cast<char *>(&header_.offset), sizeof(header_.offset));
    file.write(reinterpret_cast<char *>(&header_.header_size), sizeof(header_.header_size));
    file.write(reinterpret_cast<char *>(&header_.dimensions), sizeof(header_.dimensions));
    file.write(reinterpret_cast<char *>(&header_.color_planes), sizeof(header_.color_planes));
    file.write(reinterpret_cast<char *>(&header_.bits_per_pixel), sizeof(header_.bits_per_pixel));
    file.write(reinterpret_cast<char *>(&header_.compression), sizeof(header_.compression));
    file.write(reinterpret_cast<char *>(&header_.image_size), sizeof(header_.image_size));
    file.write(reinterpret_cast<char *>(&header_.resolution), sizeof(header_.resolution));
    file.write(reinterpret_cast<char *>(&header_.palette_colors), sizeof(header_.palette_colors));
    file.write(reinterpret_cast<char *>(&header_.important_colors), sizeof(header_.important_colors));

    const size_t row_const = 32.0;
    const double color_coeff = 255.0;
    const size_t new_row_size = static_cast<size_t>(
        std::ceil(static_cast<double>(header_.bits_per_pixel * bmp_image_.GetWidth()) / row_const) * 4);
    for (size_t i = 0; i < bmp_image_.GetHeight(); ++i) {
        uint8_t row[new_row_size];
        for (size_t j = 0; j < bmp_image_.GetWidth(); ++j) {
            row[3 * j] =
                static_cast<uint8_t>(bmp_image_.GetPixel(bmp_image_.GetHeight() - 1 - i, j).blue * color_coeff);
            row[3 * j + 1] =
                static_cast<uint8_t>(bmp_image_.GetPixel(bmp_image_.GetHeight() - 1 - i, j).green * color_coeff);
            row[3 * j + 2] =
                static_cast<uint8_t>(bmp_image_.GetPixel(bmp_image_.GetHeight() - 1 - i, j).red * color_coeff);
        }
        file.write(reinterpret_cast<char *>(row), static_cast<std::streamsize>(sizeof(row)));
    }
    file.close();
}

Image *BMPObject::GetImagePtr() {
    return &bmp_image_;
}