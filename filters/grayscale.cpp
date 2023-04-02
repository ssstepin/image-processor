#include "grayscale.h"

Grayscale::Grayscale() {
}

void Grayscale::Apply(Image *image) const {
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            RGB gray_pixel = image->GetPixel(i, j);
            gray_pixel = {gray_pixel.red * gray_effect_[0] + gray_pixel.green * gray_effect_[1] +
                              gray_pixel.blue * gray_effect_[2],
                          gray_pixel.red * gray_effect_[0] + gray_pixel.green * gray_effect_[1] +
                              gray_pixel.blue * gray_effect_[2],
                          gray_pixel.red * gray_effect_[0] + gray_pixel.green * gray_effect_[1] +
                              gray_pixel.blue * gray_effect_[2]};
            image->SetPixel(i, j, gray_pixel);
        }
    }
}