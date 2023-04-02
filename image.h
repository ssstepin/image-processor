#pragma once

#include <vector>

struct RGB {
    double red;
    double green;
    double blue;
    void Normalize();
    RGB(double r, double g, double b);
    RGB& operator+=(const RGB& other);
};

const RGB BLACK = RGB(0.0, 0.0, 0.0);
const RGB WHITE = RGB(1.0, 1.0, 1.0);
using ImageMatrix = std::vector<std::vector<RGB>>;

struct RGBMatrix {
    // 3x3 matrix for filters
    std::vector<std::vector<int>> matrix;
    const std::vector<std::pair<ssize_t, ssize_t>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0},
                                                                 {0, 1},   {1, -1}, {1, 0},  {1, 1}};
    ssize_t center_x = 1;
    ssize_t center_y = 1;
};

RGB operator*(const RGB& lhs, int rhs);
RGB operator*(const RGB& lhs, double rhs);
RGB operator+(const RGB& lhs, const RGB& rhs);

class Image {
public:
    explicit Image(const ImageMatrix& image_matrix);
    Image(){};
    Image(size_t width, size_t height);
    const Image& operator*=(const RGBMatrix& other);
    size_t GetWidth() const;
    size_t GetHeight() const;
    const RGB& GetPixel(size_t i, size_t j) const;
    void SetPixel(size_t i, size_t j, const RGB& new_pixel);
    void SetWidth(size_t new_width);
    void SetHeight(size_t new_height);

private:
    ImageMatrix inner_image_;
    ssize_t width_;
    ssize_t height_;
};
