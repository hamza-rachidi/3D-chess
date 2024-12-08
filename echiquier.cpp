#include "echiquier.h"
#include "renderer.h"
#include "pieces/cavalier.h"


Echiquier::Echiquier(float squareSize, int gridSize)
    : Object(generateVertices(squareSize, gridSize), generateUVs(gridSize), generateColors(gridSize), GenerateXZpositions(squareSize, gridSize), "") {
    }


float Offset = 0.03;

// Checks if a given position on the chessboard is free or occupied.
PositionCheckReturnType Echiquier::CheckPosition(glm::vec2 PositionOnBoard)
{
    
    PositionCheckReturnType ReturnValue;
    
    for (auto& pair : KeyedChessPieces)
    {
        auto& Key = pair.first;
        auto& Value = pair.second;
        if (isWithinRange(Value->position.x - Offset, Value->position.x + Offset, PositionOnBoard.x) &&
            isWithinRange(Value->position.z - Offset, Value->position.z + Offset, PositionOnBoard.y))
        {
            //return false since its not free space
            ReturnValue.IsFree = false;
            //return the Occupants Key
            ReturnValue.Key = Key;
            return ReturnValue;
        }

    }

        {
            //other wise Return true and no Key
                ReturnValue.IsFree = true;
                ReturnValue.Key = "";
                return ReturnValue;
        }
}

/* Move a piece identified by a key to a new position defined by an offset while checking it stays within the board boundaries
and also to captures opponent pieces */
bool  Echiquier::MovePiece(std::string key,  glm::vec2 XZOffsets, Shader* SimpleShader)
{
    glm::vec2 IndexOffsets = XZOffsets; //integer offsets for Changing the Board index

    //retrives the Piece pointer from the map
    Piece* piece = KeyedChessPieces[key];
    //Express XZoffsets in The Unit Size of the Board which is 0.2 in this case
    XZOffsets = SQUARE_SIZE * XZOffsets;

    //checks if the final Location will still be on the Board
    bool isWithinXboard =  isWithinRange(-3.750f * SQUARE_SIZE, 3.250f * SQUARE_SIZE, (piece->PositioToVec2() + XZOffsets).x);
    bool isWithinZboard =  isWithinRange(0.0f * SQUARE_SIZE, 7.0f * SQUARE_SIZE, (piece->PositioToVec2() + XZOffsets).y);
   
    if (isWithinXboard && isWithinZboard)
    {

        //checks if the Poistion is Free 
        auto result = CheckPosition(piece->PositioToVec2() + XZOffsets);

        if (!result.IsFree)
        {
            //if its Not and there is an Opposite Team there Kill it And delete from the map
            if (result.Key.find(BLACK_TEAM) != piece->GetKey().find(BLACK_TEAM))
            {
                PieceAndTimer Temp;
                Temp.piece = *piece;
                Temp.time.Time = 0.8;
                Temp.time.reset();
                //dont update the Main Pice imeediately
                Temp.piece.initializeVec2Position(piece->PositioToVec2() + XZOffsets);
                Temp.piece.BoardIndex += IndexOffsets;//update the Board index To Match Current Location on the Board
                KeyedChessPieces.erase(result.Key); //kill chess Piece

                TempKeyedChessPieces[piece->GetKey()] = Temp;

                //set the Green Color For a short time 
                SimpleShader->setUniform3fv("XZ", glm::vec3(Temp.piece.BoardIndex.x, 0, Temp.piece.BoardIndex.y)); //use location to land at

            }


        }
        //if not initialize the New Position fopr the Piece
        else
        {
            PieceAndTimer Temp;
            Temp.piece = *piece;
            Temp.time.Time = 0.5;
            Temp.time.reset();
            //dont update the Main Pice imeediately

            Temp.piece.initializeVec2Position(piece->PositioToVec2() + XZOffsets);
            Temp.piece.BoardIndex += IndexOffsets; //update the Board index To Match Current Location on the Board
            TempKeyedChessPieces[piece->GetKey()] = Temp;

            //set the Green Color For a short time 
            SimpleShader->setUniform3fv("XZ", glm::vec3(Temp.piece.BoardIndex.x, 0, Temp.piece.BoardIndex.y)); //use location to land at
        }

        return true;
    }
    else
    {
        //when this is call the Piece make A new random move
        return false;
    }
 

}

void Echiquier::UpdatePieces()
{
    for (auto& [key, value] : TempKeyedChessPieces)
    {
        //if the Timer For The Green Box runs out Upate the Pieces Location
        if (value.time.elapsed() >= value.time.Time)
        {
            //Update the Position after the Wait for Green Box
            KeyedChessPieces[key]->position = value.piece.position;
            KeyedChessPieces[key]->BoardIndex = value.piece.BoardIndex;
            TempKeyedChessPieces.erase(key);

            if (TempKeyedChessPieces.size() == 0)
            {
                break;
            }
        }
    }
}

glm::vec3 Echiquier::GetBoardIndexFromPiecePosition(glm::vec3 Position)
{
    return glm::vec3();
}


std::vector<glm::vec3> Echiquier::GenerateXZpositions(float squareSize, int gridSize)
{
    std::vector<glm::vec3> XZPositions;


    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
          
            float zHeight = 0.2f; // Cube height
            //set Position to Use for changing Colors Of cubes to Move to 
            for (int i = 0; i < 36; ++i)  XZPositions.push_back(glm::vec3(col, 0, row));


        }
    }


    return XZPositions;
}

std::vector<glm::vec3> Echiquier::generateVertices(float squareSize, int gridSize) {
    std::vector<glm::vec3> vertices;



    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            float x = col * squareSize;
            float y = row * squareSize;

            float zHeight = 0.2f; // Cube height
            //set Position to Use for changing Colors Of cubes to Move to 

            // Bottom face (z = 0)
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x + squareSize, y, 0.0f));       // b
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, 0.0f)); // d
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, 0.0f)); // d
            vertices.push_back(glm::vec3(x, y + squareSize, 0.0f));       // c

            // Top face (z = z_Height)
            vertices.push_back(glm::vec3(x, y, zHeight));                 // e
            vertices.push_back(glm::vec3(x + squareSize, y, zHeight));    // f
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x, y, zHeight));                 // e
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x, y + squareSize, zHeight));    // g

            // Front face
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x + squareSize, y, 0.0f));       // b
            vertices.push_back(glm::vec3(x + squareSize, y, zHeight));    // f
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x + squareSize, y, zHeight));    // f
            vertices.push_back(glm::vec3(x, y, zHeight));                 // e

            // Back face
            vertices.push_back(glm::vec3(x, y + squareSize, 0.0f));       // c
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, 0.0f)); // d
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x, y + squareSize, 0.0f));       // c
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x, y + squareSize, zHeight));    // g

            // Left face
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x, y + squareSize, 0.0f));       // c
            vertices.push_back(glm::vec3(x, y + squareSize, zHeight));    // g
            vertices.push_back(glm::vec3(x, y, 0.0f));                    // a
            vertices.push_back(glm::vec3(x, y + squareSize, zHeight));    // g
            vertices.push_back(glm::vec3(x, y, zHeight));                 // e

            // Right face
            vertices.push_back(glm::vec3(x + squareSize, y, 0.0f));       // b
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, 0.0f)); // d
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x + squareSize, y, 0.0f));       // b
            vertices.push_back(glm::vec3(x + squareSize, y + squareSize, zHeight)); // h
            vertices.push_back(glm::vec3(x + squareSize, y, zHeight));    // f
        }
    }


    return vertices;
}

std::vector<glm::vec2> Echiquier::generateUVs(int gridSize) {
    std::vector<glm::vec2> uvs(gridSize * gridSize * 6, glm::vec2(0.0f, 0.0f)); // Placeholder
    return uvs;
}

std::vector<glm::vec3> Echiquier::generateColors(int gridSize) {
    std::vector<glm::vec3> colors;
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            glm::vec3 color = ((row + col) % 2 == 0) ? glm::vec3(0.8f, .6f, .4f) : glm::vec3(0.5f, 0.25f, 0.0f);
            for (int i = 0; i < 36; ++i) colors.push_back(color);
        }
    }
    return colors;
}

glm::mat4 Echiquier::getModelMatrix() {
    return Object::getModelMatrix();
}

void Echiquier::AddPiece(Piece* piece) 
{
    //Adds a Piece to the Map of Pieces
    auto Key = piece->GetKey();
    KeyedChessPieces[Key] = piece;
}

void Echiquier::Draw(Shader* SimpleShader) const {

    /*Object::Bind();
    Renderer::DrawObject(this); // Rendu de l'échiquier lui-même*/
    Bind();
    glDrawArrays(GL_TRIANGLES, 0, m_vb->getSize());

    SimpleShader->setUniform1i("isChessPiece", 1);
    
    //Retrieve Keys, and Values From The Map of ChessPieces in a loop iteration
    for (const auto& [Key, Piece] : KeyedChessPieces) {
        SimpleShader->Bind();
        //Setup the piece model matrix
        SimpleShader->setUniformMat4f("model", glm::scale(Piece->getModelMatrix(), glm::vec3(0.015)));
        //set the piece Color
        SimpleShader->setUniform3fv("PieceColor", Piece->color);
        Piece->Draw();  // Dessiner la pièce
    }

    //this is used in Shader To Differenctiate when to Use uniforms color for chess pieces and Object color for Board 
    SimpleShader->setUniform1i("isChessPiece", 0);

}
