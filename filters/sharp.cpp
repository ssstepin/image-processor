#include "sharp.h"

Sharpening::Sharpening() {
}

const RGBMatrix& Sharpening::GetFilterMatrix() const {
    return sharp_matrix_;
}