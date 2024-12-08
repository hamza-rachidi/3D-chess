#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "pieces/roi.h"
#include "pieces/cavalier.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "echiquier.h"
#include "pieces/fou.h"
#include "pieces/dame.h"
#include "pieces/pion.h"
#include "pieces/tour.h"

using namespace std;

int whiteCallCount = 0;
int BlackCallCount = 0;

void moveWhitePiece(Echiquier* Pointer, Shader *shader)
{
    whiteCallCount++;

    // Seed the random number generator
    std::srand(std::time(0));

    // Run the random selection in a loop
    while (true) {
        // Get the size of the map
        size_t mapSize = Pointer->KeyedChessPieces.size();

        // Generate a random index
        size_t randomIndex = std::rand() % mapSize;

        // Use an iterator to access the element at the random index
        auto it = Pointer->KeyedChessPieces.begin();
        std::advance(it, randomIndex);

        if (it->first.find(WHITE_TEAM))
        {
            if (Pointer->MovePiece(it->first, it->second->GetRandomMove(), shader))
            {
                break;
            }
            else
            {
                if (whiteCallCount >= 20)
                {
                    whiteCallCount = 0;
                    return;
                }

                moveWhitePiece(Pointer, shader);
            }


            break;
        }


    }

}

void moveBlackPiece(Echiquier * pointer, Shader* shader)
{
    BlackCallCount++;
    // Seed the random number generator
    std::srand(std::time(0));

    // Run the random selection in a loop
    while (true) {
        // Get the size of the map
        size_t mapSize = pointer->KeyedChessPieces.size();

        // Generate a random index
        size_t randomIndex = std::rand() % mapSize;

        // Use an iterator to access the element at the random index
        auto it = pointer->KeyedChessPieces.begin();
        std::advance(it, randomIndex);

        if (it->first.find(BLACK_TEAM))
        {
            if (pointer->MovePiece(it->first, it->second->GetRandomMove(), shader))
            {
                break;
            }
            else
            {

                if (BlackCallCount >= 20)
                {
                    BlackCallCount = 0;
                    return;
                }

                moveBlackPiece(pointer, shader);
                break;

            }
        }


    }

}

int main() {
#ifdef WINDOWS
    string path = "";
#else
    string path = "/mnt/e/M2TSI/OpenGL/MonProjet/OpenGL_API_V6/"; // to be replaced with your path 
#endif // WINDOWS


    Piece::path = path;

    // Initialisation de GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 600;
    int height = 600;
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary, nullptr, nullptr, &width, &height);
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_API", NULL, NULL);
    glfwSwapInterval(1);

    if (window == NULL) {
        cerr << "Erreur lors de la création de la fenêtre" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

/////////////////////////Initialisation de GLEW////////////////////////

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        cerr << "Erreur lors de l'initialisation de GLEW" << endl;
        return -1;
    }

/////////////////////////On crée un Renderer////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////

   
    Shader shader(path+"shaders/SimpleVertexShader.vertexshader", path+"shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

///////////////////////// The chess objects' initialisation /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float square_size = 0.2f;
    Echiquier echiquier(0.2f, 8); // Initialize the chessboard with appropriate square size and an 8x8 grid
    echiquier.AddPiece(new Roi(true));  // White King
    echiquier.AddPiece(new Roi(false)); // Black King

    echiquier.AddPiece(new Dame(true)); // White Queen
    echiquier.AddPiece(new Dame(false)); // Black Queen

    echiquier.AddPiece(new Cavalier(true, 0));  // Left White Knight
    echiquier.AddPiece(new Cavalier(true, 1));  // Right White Knight
    echiquier.AddPiece(new Cavalier(false, 0)); // Left Black Knight
    echiquier.AddPiece(new Cavalier(false, 1)); // Right Black Knight

    echiquier.AddPiece(new Tour(true, 0));  // Left White Rook
    echiquier.AddPiece(new Tour(true, 1));  // Right White Rook
    echiquier.AddPiece(new Tour(false, 0)); // Left Black Rook
    echiquier.AddPiece(new Tour(false, 1)); // Right Black Rook

    echiquier.AddPiece(new fou(true, 0));  // Left White Bishop
    echiquier.AddPiece(new fou(true, 1));  // Right White Bishop
    echiquier.AddPiece(new fou(false, 0)); // Left Black Bishop
    echiquier.AddPiece(new fou(false, 1)); // Right Black Bishop

    echiquier.AddPiece(new Pion(true, 0));  // White Pawn 1
    echiquier.AddPiece(new Pion(true, 1));  // White Pawn 2 
    echiquier.AddPiece(new Pion(true, 3));  // White Pawn 3
    echiquier.AddPiece(new Pion(true, 4));  // White Pawn 4
    echiquier.AddPiece(new Pion(true, 5));  // White Pawn 5
    echiquier.AddPiece(new Pion(true, 6));  // White Pawn 6
    echiquier.AddPiece(new Pion(true, 7));  // White Pawn 7
    echiquier.AddPiece(new Pion(true, 8));  // White Pawn 8

    echiquier.AddPiece(new Pion(false, 0));  // Black Pawn 1
    echiquier.AddPiece(new Pion(false, 1));  // Black Pawn 2
    echiquier.AddPiece(new Pion(false, 3));  // Black Pawn 3 
    echiquier.AddPiece(new Pion(false, 4));  // Black Pawn 4
    echiquier.AddPiece(new Pion(false, 5));  // Black Pawn 5
    echiquier.AddPiece(new Pion(false, 6));  // Black Pawn 6
    echiquier.AddPiece(new Pion(false, 7));  // Black Pawn 7
    echiquier.AddPiece(new Pion(false, 8));  // Black Pawn 8

    cam.setFoV(30.0f);


    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.86f, 0.86f, 0.82f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();


    Timer ChessTime;
    bool WhitesMove = true;

    // Adjusting the game view with the best camera's parameters 
    cam.position = glm::vec3(0.04, 0.05, -1.5410);
    cam.horizontalAngle = 6.28;
    cam.verticalAngle = -0.4;

    // Boucle de rendu
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        renderer.Clear();

        echiquier.rotationAngles.x=glm::radians(90.0f);  // chessboard position in the space

        echiquier.position.x=-0.75;      
        echiquier.position.y=-0.78;

        controls.update(deltaTime, &shader);

        cam.computeMatrices(width, height);
        
        glm::mat4 model = echiquier.getModelMatrix();
        glm::mat4 vp = cam.getProjectionMatrix() * cam.getViewMatrix();
      
        shader.setUniformMat4f("VP", vp);

        shader.setUniformMat4f("model", model);
        shader.Bind();
        renderer.Draw(va, echiquier, shader);
        echiquier.Draw(&shader);



        //move Pieces At Intervals of >1.5 seconds ( otherwise it might crash )
        if (ChessTime.elapsed() >= 1.5)
        {
            //reset Timer For Next Piece Movement
            ChessTime.reset();
            if (WhitesMove)
            {
                
                //Flip  A bool switch to decide which Color of Piece should move next
                WhitesMove = !WhitesMove;
                moveWhitePiece(&echiquier, &shader);
            }
            else if (!WhitesMove)
            {

              
                //Flip  A bool switch to Decide which Color of Piece should move next
                WhitesMove = !WhitesMove;
                moveBlackPiece(&echiquier, &shader);
            }

        }

        echiquier.UpdatePieces();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


