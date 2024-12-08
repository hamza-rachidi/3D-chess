#ifndef DAME_H
#define DAME_H

#include "piece.h"
#include "../renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Dame : public Piece {
public:
    Dame(bool isWhite);
    glm::vec2 GetRandomMove() override;
    void Draw() const override;
};


#endif // DAME_H
