#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include "object.h"
#include "pieces/piece.h"
#include "glm/glm.hpp"
#include <vector>
#include <unordered_map>
#include "shader.h"
#include <chrono>
#include <queue>


//Chrono Timer 
//Reset : Restarts the Timer From Zero
//Elapsed returns the Time in seconds since last reset ( to control the move speed )
class Timer {
public:
    Timer() : beg_(clock_::now()) {}

    void reset() { beg_ = clock_::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<second_> (clock_::now() - beg_).count();
    }

    float Time = - 1;
private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;

};


struct PositionCheckReturnType
{
    std::string Key;
    bool IsFree = false;
};


struct PieceAndTimer
{
    Piece piece;
    Timer time;
};

class Echiquier : public Object {
public:
    Echiquier(float squareSize, int gridSize);
    glm::mat4 getModelMatrix();
    void AddPiece(Piece* piece);   // Ajouter une pièce sur l'échiquier
    void Draw(Shader* SimpleShader) const;
    
    //pieces
    std::unordered_map<std::string, Piece*> KeyedChessPieces;
    std::unordered_map<std::string, PieceAndTimer> TempKeyedChessPieces;

    PositionCheckReturnType CheckPosition(glm::vec2 PositionOnBoard);


    bool MovePiece(std::string key, glm::vec2 XZOffsets, Shader * SimpleShader); 
    void UpdatePieces();
    glm::vec3 GetBoardIndexFromPiecePosition(glm::vec3 Position);

private:


    std::vector<glm::vec3> GenerateXZpositions(float squareSize, int gridSize);
    std::vector<glm::vec3> generateVertices(float squareSize, int gridSize);
    std::vector<glm::vec2> generateUVs(int gridSize);
    std::vector<glm::vec3> generateColors(int gridSize);


};

#endif // ECHIQUIER_H







