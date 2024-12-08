#include "tour.h"


Tour::Tour(bool isWhite, int index)
    :Piece(ROOK, "pieces/tour.obj",  // Initial position of the knight with y for elevation (height relative to the chessboard)
        isWhite ? (index == 0 ? glm::vec3(-3.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f)
            : glm::vec3(3.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f))
        : (index == 0 ? glm::vec3(-3.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)
            : glm::vec3(3.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)),
        "")
{

    //Set the Board Indicies of the Rook
    BoardIndex.x = (index == 0 ? 0 : 7);
    BoardIndex.y = ((isWhite ? 0 : 7));//set color


    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));//color

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)TOUR) + std::to_string(index); //Key
}


glm::vec2 Tour::GetRandomMove()
{

    Moves.type = ROOK;
    glm::vec2 Position;

    
    while (true)
    {
        int id = rand() % 2;

        int signX = (rand() % 2 == 0) ? 1 : -1; 
        int signY = (rand() % 2 == 0) ? 1 : -1; 

 
        if (id == 0) {  // Horizontal Move
            Position.x = signX * (rand() % 7); 
            Position.y = 0;
            break;
        }
        else if (id == 1) {  // Vertical Move
            Position.y = signY * (rand() % 7); 
            Position.x = 0;
            break;
        }


    }


    return Position;
}


void Tour::Draw() const {
    draw();
}
