#include "negative.h"

Negative::Negative() {
}

void Negative::Apply(Image *image) const {
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            RGB negative_pixel = image->GetPixel(i, j);
            negative_pixel = {1.0 - negative_pixel.red, 1.0 - negative_pixel.green, 1.0 - negative_pixel.blue};
            image->SetPixel(i, j, negative_pixel);
        }
    }
}