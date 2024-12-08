#include <GL/glew.h>
#include "roi.h"
#include <vector>
#include <glm/glm.hpp>
#include <cmath>

Roi::Roi(bool isWhite)
    :Piece(KING, "pieces/roi.obj", // Initial position of the king with y for elevation (height relative to the chessboard)
            isWhite ? glm::vec3(-0.25 * SQUARE_SIZE, -.700f, 0.5 * SQUARE_SIZE)
                    : glm::vec3(-0.25 * SQUARE_SIZE, -0.70f, 7.5 * SQUARE_SIZE) ,
            "")
{
    //Set the Board Indicies of the King
    BoardIndex.x = 4;
    BoardIndex.y = ((isWhite ? 0 : 7));//set color

    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)ROI);
}

void Roi::Draw() const {
    draw();

}

glm::vec2 Roi::GetRandomMove()
{

        Moves.type = KING;


        glm::vec2 Position;
         while (true)
    {
        int id = rand() % 8; // 8 possible directions can be generated: 4 cardinal directions and 4 diagonals

        int signX = (rand() % 2 == 0) ? 1 : -1; 
        int signY = (rand() % 2 == 0) ? 1 : -1; 

        if (id == 0) { // Horizontal movement
            Position.x = signX * 1;
            Position.y = 0;
            break;
        }
        else if (id == 1) { // Vertical movement
            Position.x = 0;
            Position.y = signY * 1;
            break;
        }
        else if (id == 2) { // Diagonal movement to the top right
            Position.x = signX * 1;
            Position.y = signY * 1;
            break;
        }
        else if (id == 3) { // Diagonal movement to the top left
            Position.x = -signX * 1;
            Position.y = signY * 1;
            break;
        }
        else if (id == 4) { // Diagonal movement to the bottom right
            Position.x = signX * 1;
            Position.y = -signY * 1;
            break;
        }
        else if (id == 5) { // Diagonal movement to the bottom left
            Position.x = -signX * 1;
            Position.y = -signY * 1;
            break;
        }
        else if (id == 6) { // Up
            Position.x = 0;
            Position.y = signY * 1;
            break;
        }
        else if (id == 7) { // Down
            Position.x = 0;
            Position.y = -signY * 1;
            break;
        }
    }

    return Position;
}
