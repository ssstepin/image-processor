#include "crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

void Crop::Apply(Image *image) const {
    size_t new_width = std::min(image->GetWidth(), width_);
    size_t new_height = std::min(image->GetHeight(), height_);
    image->SetWidth(new_width);
    image->SetHeight(new_height);
}
