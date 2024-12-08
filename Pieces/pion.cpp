#include "pion.h"
int PawnsMoveID = 2;

Pion::Pion(bool isWhite, int index)
    :Piece(PAWN, "pieces/pion.obj",  //  Initial position of the pawn with y for elevation (height relative to the chessboard)
        isWhite ?  glm::vec3((index - 4.75f) * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.71f, 1 * SQUARE_SIZE + SQUARE_SIZE / 2.0f)
        : glm::vec3((index - 4.750f) * SQUARE_SIZE + SQUARE_SIZE / 2.0f, -0.71f, 6. * SQUARE_SIZE + SQUARE_SIZE / 2.0f),
        "")
{
    //Set the Board Indicies of the Pawns
    BoardIndex.x = index - 1;
    BoardIndex.y = ((isWhite ? 1 : 6));//set color

    if (index <= 1)
    {
        BoardIndex.x = index;

        //calculate horizontal position based on which pawn index 
        this->position.x = (index - 3.75f) * SQUARE_SIZE + SQUARE_SIZE / 2.0f;
    }

    color = ((isWhite ? glm::vec3(1.0f) : glm::vec3(0.0f)));//set color

    Key = ((isWhite ? WHITE_TEAM : BLACK_TEAM) + (std::string)PION) + std::to_string(index); //set key 

    Moves.type = PAWN;
    //if pawn is White they Can only make positive movement
    if(isWhite){
    Moves.PossibleMovementOptions[0].x = 0;
    Moves.PossibleMovementOptions[0].y = 1;
    Moves.PossibleMovementOptions[1].x = 0;
    Moves.PossibleMovementOptions[1].y = 1;

    //index 2 can only be used once at the start of the Game
    Moves.PossibleMovementOptions[2].x = 0;
    Moves.PossibleMovementOptions[2].y = 2;

    }
    else
    {
        //black can make only Negative Movement
        Moves.PossibleMovementOptions[0].x = 0;
        Moves.PossibleMovementOptions[0].y = -1;
        Moves.PossibleMovementOptions[1].x = 0;
        Moves.PossibleMovementOptions[1].y = -1;

        //index 2 can only be used once at the start of the Game
        Moves.PossibleMovementOptions[2].x = 0;
        Moves.PossibleMovementOptions[2].y = -2;
    }
}


glm::vec2 Pion::GetRandomMove()
{
    //Get a Ranom Move From the List of movements
    int MoveID = rand() % PawnsMoveID;
    return Moves.PossibleMovementOptions[MoveID];
}

void Pion::Draw() const {
    draw();
}
