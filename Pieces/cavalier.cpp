#include <GL/glew.h>
#include "cavalier.h"
#include <vector>
#include <glm/glm.hpp>


Cavalier::Cavalier(bool isWhite, int index)
    :Piece(KNIGHT, "pieces/cavalier.obj",  // Initial position of the knight with y for elevation (height is relative to the chessboard)  
        isWhite ? (index == 0 ? glm::vec3(-2.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f)
            : glm::vec3(2.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, SQUARE_SIZE / 2.0f))
        : (index == 0 ? glm::vec3(-2.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)
            : glm::vec3(2.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)),
        "")
{

    //Set the Board Indicies of the Knights
    BoardIndex.x = (index == 0 ? 1 : 6 );
    BoardIndex.y = ((isWhite ? 0 : 7));//set color

    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)CAVALIER) + std::to_string(index);
}

glm::vec2 Cavalier::GetRandomMove()
{

        Moves.type = KNIGHT;


        glm::vec2 Position;
        while (true)
        {

            // Randomly choose a knight move pattern
            int moveType = rand() % 2; // 0 or 1
            int directionX = (rand() % 2 == 0) ? 1 : -1; // Randomly pick positive or negative for x
            int directionY = (rand() % 2 == 0) ? 1 : -1; // Randomly pick positive or negative for y

            if (moveType == 0) {
                // Move two squares in x and one square in y
                Position.x += directionX * 2;
                Position.y += directionY * 1;
                break;
            }
            else {
                // Move one square in x and two squares in y
                Position.x += directionX * 1;
                Position.y += directionY * 2;
                break;
            }

        }


        return Position;
    

}


void Cavalier::Draw() const {
    draw();
}
