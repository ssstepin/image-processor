#include "wide.h"

Wide::Wide(double coeff) : wide_coeff_(coeff) {
}

void Wide::Apply(Image *image) const {
    ImageMatrix new_image(0);
    for (size_t i = 0; wide_coeff_ * static_cast<double>(i) < static_cast<double>(image->GetHeight()); ++i) {
        std::vector<RGB> new_row;
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            new_row.push_back(image->GetPixel(static_cast<size_t>(wide_coeff_ * static_cast<double>(i)), j));
        }
        new_image.push_back(new_row);
    }
    *image = Image(new_image);
}