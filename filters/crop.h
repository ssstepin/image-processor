#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    void Apply(Image* image) const override;

private:
    size_t width_;
    size_t height_;
};