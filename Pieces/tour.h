#ifndef TOUR_H
#define TOUR_H

#include "piece.h"
#include "../renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Tour : public Piece {
public:
    Tour(bool isWhite, int index);
    glm::vec2 GetRandomMove() override;
    void Draw() const override;
};


#endif // TOUR_H
