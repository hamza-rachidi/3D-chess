#ifndef CAVALIER_H
#define CAVALIER_H

#include "piece.h"

class Cavalier : public Piece {
public:
    Cavalier(bool isWhite, int index);
    glm::vec2 GetRandomMove() override;
    void Draw() const override;
};

#endif // CAVALIER_H
