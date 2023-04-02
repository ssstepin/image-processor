#include "edge.h"
#include "grayscale.h"

Edge::Edge(double threshold) : threshold_(threshold) {
}

void Edge::Apply(Image* image) const {
    Grayscale().Apply(image);
    *image *= edge_matrix_;
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            if (image->GetPixel(i, j).red > threshold_) {
                image->SetPixel(i, j, WHITE);
            } else {
                image->SetPixel(i, j, BLACK);
            }
        }
    }
}
const RGBMatrix& Edge::GetFilterMatrix() const {
    return edge_matrix_;
}