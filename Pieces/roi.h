#ifndef ROI_H
#define ROI_H

#include "piece.h"

class Roi : public Piece {
public:
    Roi(bool isWhite);
    void Draw() const override;
    glm::vec2 GetRandomMove() override;

};

#endif // ROI_H
