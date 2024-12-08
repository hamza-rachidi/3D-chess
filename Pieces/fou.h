#ifndef FOU_H
#define FOU_H
#include "piece.h"

class fou : public Piece
{
public:
    fou(bool isWhite, int index);
    glm::vec2 GetRandomMove() override;
    void Draw() const override;
};

#endif // FOU_H
