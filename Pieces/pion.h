#ifndef PION_H
#define PION_H


#include "piece.h"
#include "../renderer.h"
#include <glm/glm.hpp>
#include <vector>

class Pion : public Piece {
public:
    Pion(bool isWhite, int index);
  
    glm::vec2 GetRandomMove() override;
    void Draw() const override;
};

#endif // PION_H
