#include "dame.h"

Dame::Dame(bool isWhite)
    :Piece(QUEEN, "pieces/dame.obj",  // Initial position of the queen with y for elevation (height relative to the chessboard)
            isWhite ? glm::vec3(0.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f) 
             : glm::vec3(0.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f), //  initial position
            "")
{

    //Set the Board Indicies of the Queen
    BoardIndex.x = 3;
    BoardIndex.y = ((isWhite ? 0 : 7));//set color

    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)DAME) ;

}


glm::vec2 Dame::GetRandomMove()
{

    Moves.type = QUEEN;



    glm::vec2 Position;
    while (true)
    {
        int id = rand() % 8; // 8 possible directions can be generated: 4 cardinal directions and 4 diagonals

        int signX = (rand() % 2 == 0) ? 1 : -1; // // Choose a random sign for x
        int signY = (rand() % 2 == 0) ? 1 : -1; // // Choose a random sign for y

        if (id == 0) { // Horizontal movement
            Position.x = signX * (rand() % 7 + 1); 
            Position.y = 0;
            break;
        }
        else if (id == 1) { // Vertical movement
            Position.x = 0;
            Position.y = signY * (rand() % 7 + 1); 
            break;
        }
        else if (id == 2) { // Diagonal movement to the top right
            Position.x = signX * (rand() % 7 + 1); 
            Position.y = signY * (rand() % 7 + 1); 
            break;
        }
        else if (id == 3) { // Diagonal movement to the top left
            Position.x = -signX * (rand() % 7 + 1);
            Position.y = signY * (rand() % 7 + 1);
            break;
        }
        else if (id == 4) { // Diagonal movement to the bottom right
            Position.x = signX * (rand() % 7 + 1);
            Position.y = -signY * (rand() % 7 + 1);
            break;
        }
        else if (id == 5) {// Diagonal movement to the bottom left
            Position.x = -signX * (rand() % 7 + 1);
            Position.y = -signY * (rand() % 7 + 1);
            break;
        }
    }

    return Position;
}

void Dame::Draw() const {
    draw();
}
