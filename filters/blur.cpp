#include "blur.h"

Blur::Blur(double sigma) : blur_sigma_(sigma) {
}

void Blur::Apply(Image *image) const {
    ssize_t radius = static_cast<ssize_t>(blur_sigma_ * 3);
    double norm_sum = 0;
    const double coeff = 1 / (2.0 * M_PI * blur_sigma_ * blur_sigma_);
    for (ssize_t x = -radius; x <= radius; ++x) {
        for (ssize_t y = -radius; y <= radius; ++y) {
            norm_sum += coeff * std::exp(-static_cast<double>(x * x + y * y) / (2 * blur_sigma_ * blur_sigma_));
        }
    }

    ImageMatrix new_image_x = ImageMatrix(image->GetHeight(), std::vector<RGB>(image->GetWidth(), BLACK));

    ssize_t height = static_cast<ssize_t>(image->GetHeight());
    ssize_t width = static_cast<ssize_t>(image->GetWidth());
    for (ssize_t i = 0; i < height; ++i) {
        for (ssize_t j = 0; j < width; ++j) {
            for (ssize_t x = -radius; x <= radius; ++x) {
                ssize_t new_i = std::min(height - 1, std::max(static_cast<ssize_t>(0), i + x));
                new_image_x[i][j] +=
                    image->GetPixel(new_i, j) * std::exp(-static_cast<double>(x * x) / (2 * blur_sigma_ * blur_sigma_));
            }
        }
    }

    ImageMatrix new_image_y = new_image_x;
    for (ssize_t i = 0; i < height; ++i) {
        for (ssize_t j = 0; j < width; ++j) {
            for (ssize_t y = -radius; y <= radius; ++y) {
                if (y == 0) {
                    continue;
                }
                ssize_t new_j = std::min(width - 1, std::max(static_cast<ssize_t>(0), j + y));
                new_image_y[i][j] +=
                    new_image_x[i][new_j] * std::exp(-static_cast<double>(y * y) / (2 * blur_sigma_ * blur_sigma_));
            }
        }
    }

    for (ssize_t i = 0; i < height; ++i) {
        for (ssize_t j = 0; j < width; ++j) {
            new_image_y[i][j] = new_image_y[i][j] * (coeff / norm_sum);
            new_image_y[i][j].Normalize();
            image->SetPixel(i, j, new_image_y[i][j]);
        }
    }
}
