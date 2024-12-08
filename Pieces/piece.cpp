#include "piece.h"

std::string Piece::path = "";

Piece::Piece(PIECETYPE Type, std::string ModelPath, glm::vec3 relativePosition, const std::string& texturePath)
    :Mesh(), position(relativePosition), type(Type)
{


    m_texture = new Texture(texturePath);

    this->loadOBJ(path + ModelPath);
    // The absolute position of the piece will be determined by that of the chessboard + relativePosition
}


glm::mat4 Piece::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1, 0, 0));
    m = glm::rotate(m, rotationAngles.y, glm::vec3(0, 1, 0));
    m = glm::rotate(m, rotationAngles.z, glm::vec3(0, 0, 1));
    return m;
}

