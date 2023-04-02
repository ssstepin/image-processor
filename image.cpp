#include "image.h"
#include <iostream>

RGB::RGB(double r, double g, double b) : red(r), green(g), blue(b) {
}

RGB operator*(const RGB& lhs, int rhs) {
    return {static_cast<double>(rhs) * lhs.red, static_cast<double>(rhs) * lhs.green,
            static_cast<double>(rhs) * lhs.blue};
}

RGB operator*(const RGB& lhs, double rhs) {
    return {rhs * lhs.red, rhs * lhs.green, rhs * lhs.blue};
}

RGB operator+(const RGB& lhs, const RGB& rhs) {
    return {lhs.red + rhs.red, lhs.blue + rhs.blue, lhs.green + rhs.green};
}

RGB& RGB::operator+=(const RGB& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
}

void RGB::Normalize() {
    red = std::min(1.0, std::max(0.0, red));
    blue = std::min(1.0, std::max(0.0, blue));
    green = std::min(1.0, std::max(0.0, green));
}

const Image& Image::operator*=(const RGBMatrix& other) {
    ImageMatrix new_inner_image = ImageMatrix(height_, std::vector<RGB>(width_, BLACK));
    for (ssize_t i = 0; i < height_; ++i) {
        for (ssize_t j = 0; j < width_; ++j) {
            for (const auto& [x, y] : other.directions) {
                ssize_t new_i = i + x;
                ssize_t new_j = j + y;
                if (new_i == -1) {
                    new_i = 0;
                }
                if (new_j == -1) {
                    new_j = 0;
                }
                if (new_i == height_) {
                    new_i = static_cast<ssize_t>(height_) - 1;
                }
                if (new_j == width_) {
                    new_j = static_cast<ssize_t>(width_) - 1;
                }
                new_inner_image[i][j] +=
                    inner_image_[new_i][new_j] * other.matrix[other.center_x + x][other.center_y + y];
            }
            new_inner_image[i][j].Normalize();
        }
    }
    inner_image_ = new_inner_image;
    return *this;
}

Image::Image(size_t width, size_t height) : width_(static_cast<ssize_t>(width)), height_(static_cast<ssize_t>(height)) {
    inner_image_ = ImageMatrix(height_, std::vector<RGB>(width_, WHITE));
}

Image::Image(const ImageMatrix& image_matrix) : inner_image_(image_matrix) {
    height_ = static_cast<ssize_t>(image_matrix.size());
    if (height_ != 0) {
        width_ = static_cast<ssize_t>(image_matrix[0].size());
    }
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

const RGB& Image::GetPixel(size_t i, size_t j) const {
    return inner_image_[i][j];
}

void Image::SetPixel(size_t i, size_t j, const RGB& new_pixel) {
    inner_image_[i][j] = new_pixel;
}

void Image::SetHeight(size_t new_height) {
    height_ = static_cast<ssize_t>(new_height);
}

void Image::SetWidth(size_t new_width) {
    width_ = static_cast<ssize_t>(new_width);
}