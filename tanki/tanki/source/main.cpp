#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "renderer/renderer.h"

// 1. File\Renderer.cpp Func\MapToScreen - weird -1.
// 2. File\Renderer.cpp Func\Renderer::SetUpConsole - asserts used, maybe some could be interchanged with throws.


float vertices[] = {
    0.5, -0.5, // top right
   -0.5, -0.5, // top left
     0,   0.5  // bottom center
};

int main() {
    try {
        Renderer game;
        game.SetUpConsole(100, 100, 5, 5);
        game.Fill(0x2588, 0x000F);
        game.DrawVertices(0x2588, FG_BLUE, vertices, 6, 6, PK_TRIANGLES);
        game.UpdateScreen();
    }
    catch (ERROR e) {
        std::cerr << "Exeption caught" << e;
    }
    catch (...) {
        std::cerr << "Undifiend exeption caught";
    }
    std::cin.get();
    return 0;
}