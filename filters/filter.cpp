#include "filter.h"

void Filter::Apply(Image* image) const {
}

void FilterWithMatrix::Apply(Image* image) const {
    *image *= GetFilterMatrix();
}

const RGBMatrix& FilterWithMatrix::GetFilterMatrix() const {
    return matrix_;
}

FilterWithMatrix::FilterWithMatrix() {
}