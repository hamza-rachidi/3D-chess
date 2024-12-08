#ifndef PIECE_H
#define PIECE_H

#include "../object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WHITE_TEAM "blanc"
#define BLACK_TEAM "noir"

#define PION "pion"
#define ROI "roi"
#define CAVALIER "Cavalier"
#define TOUR "tour"
#define DAME "dame"
#define FOU "fou"


#include "../mesh.h"
const float SQUARE_SIZE = 0.2f; //size of each cell on the Board
enum  PIECETYPE
{
    PAWN,
    KING,
    QUEEN,
    BISHOP,
    ROOK,
    KNIGHT
};

struct PieceMovement
{
    PIECETYPE type;
    glm::vec2 PossibleMovementOptions[15] = { };
};


inline bool isWithinRange(float min, float max, float val)
{
    //checks if a float value is Withing a range
    if (val >= min && val <= max)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Piece : public Mesh{
public:
    Piece() { };
    Piece(PIECETYPE Type, std::string ModelPath, glm::vec3 relativePosition, const std::string& texturePath);
    virtual ~Piece() = default;

    // This method will be implemented in the derived classes (chess pieces)
    virtual void Draw() const
    {
    };
    glm::mat4 getModelMatrix();

    std::string GetKey()
    {
        return Key;
    }

    glm::vec2 PositioToVec2()
    {
        return glm::vec2(position.x, position.z);
    }

    void initializeVec2Position(glm::vec2 pos)
    {
        position.x = pos.x;
        position.z = pos.y;
    }

    virtual  glm::vec2 GetRandomMove()
    {
        return glm::vec2(0);
    };


    glm::vec3 color;
    glm::vec3 position;
    mutable glm::vec3 rotationAngles = glm::vec3(0.0f);

    static std::string path;
    PIECETYPE type; //Type of Chess Pices

    PieceMovement  Moves;
    glm::vec2 BoardIndex; //index of the Chess Piece on the Board
protected:
    std::string Key;
private:
    Texture* m_texture;
    glm::vec3 relativePosition;  // Position relative par rapport à l'échiquier pour que la pièce se déplace avec l'echiquier 
};

#endif   // PIECE_H
