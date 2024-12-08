#include "fou.h"


fou::fou(bool isWhite, int index)
    :  Piece(BISHOP, "pieces/fou.obj",  // Initial position of the bishop with y for elevation (height relative to the chessboard)
        isWhite ? (index == 0 ? glm::vec3(-1.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f)
            : glm::vec3(1.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f,  SQUARE_SIZE / 2.0f))
        : (index == 0 ? glm::vec3(-1.750 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)
            : glm::vec3(1.25 * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.70f, 7. * SQUARE_SIZE + SQUARE_SIZE / 2.0f)),
        "")
{

    //Set the Board Indicies of the Queen
    BoardIndex.x = (index == 0 ? 2 : 5);
    BoardIndex.y = ((isWhite ? 0 : 7));//set color

    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)FOU) + std::to_string(index);
}

glm::vec2 fou::GetRandomMove()
{

    Moves.type = BISHOP;

    
    glm::vec2 Position;
    while (true)
    {

        // Randomly pick the direction for x and y
        int signX = (rand() % 2 == 0) ? 1 : -1; // Randomly pick positive or negative for x
        int signY = (rand() % 2 == 0) ? 1 : -1; // Randomly pick positive or negative for y

        {

            // Assign the diagonal move
            Position.x = signX * (rand() % 7); 
            Position.y = Position.x;        
            break;
        }
    }


    return Position;
}




void fou::Draw() const
{
	draw();
}
