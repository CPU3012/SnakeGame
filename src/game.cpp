#include "game.hpp"
#include <raylib.h>

Game::Game() {
    init(1200,800); // Initial Window Dimentions
}

void Game::init(int WINDOW_WIDTH, int WINDOW_HEIGHT){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPU's Snake Game");

    // SetTargetFPS(60);

}

void Game::play() {
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Hello World", 190, 200, 20, SKYBLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}