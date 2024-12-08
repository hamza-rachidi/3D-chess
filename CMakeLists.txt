cmake_minimum_required(VERSION 3.5)

project(Chessgame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Chessgame main.cpp camera.cpp camera.h navigationcontrols.h navigationcontrols.cpp renderer.h renderer.cpp vertexarray.h vertexarray.cpp
    vertexbuffer.h vertexbuffer.cpp shader.h shader.cpp uvbuffer.h uvbuffer.cpp fpscontrols.h fpscontrols.cpp controls.cpp controls.h
    texture.h texture.cpp object.h object.cpp stb_image/stb_image.h stb_image/stb_image.cpp echiquier.cpp echiquier.h
    Pieces/piece.h Pieces/piece.cpp Pieces/pion.h Pieces/pion.cpp Pieces/cavalier.h Pieces/cavalier.cpp Pieces/tour.h Pieces/tour.cpp
    Pieces/fou.h Pieces/fou.cpp Pieces/dame.h Pieces/dame.cpp Pieces/roi.h Pieces/roi.cpp mesh.h mesh.cpp )

target_link_libraries(Chessgame glfw GLEW libGLEW.so libGLU.so libGL.so )
