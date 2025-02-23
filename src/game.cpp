#include "game.hpp"
#include <raylib.h>
#include <iostream>
#include <algorithm>


Game::Game() {
    init(1200,800); // Initial Window Dimentions
}
Game::~Game(){
    CloseWindow(); 
}

void Game::init(int WINDOW_WIDTH, int WINDOW_HEIGHT){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPU's Snake Game");

    snake.m_headColour = BLUE;
    snake.m_length = 0;
    snake.speed = 1.0f;
    snake.m_direction = 0;
    snake.m_headPosition.x = 4; snake.m_headPosition.y = 4;
}

void Game::play() {
    Tile tiles[8][8]; //The game will consist of 64 tiles

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        //if(collisionDetected()) return;
        getInput(snake);
        update(snake, tiles);
        draw(snake, tiles);

    }

    
}

void Game::update(Snake& snake, Tile (&tiles)[8][8]) {

    
    switch (snake.m_direction)
    {
    case 0:

        snake.m_headPosition.y -= snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 45:

        snake.m_headPosition.y += snake.speed * float(GetFrameTime());
        snake.m_headPosition.x += snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 90:

        snake.m_headPosition.x += snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 135:

        snake.m_headPosition.x += snake.speed * float(GetFrameTime());
        snake.m_headPosition.y -= snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 180:

        snake.m_headPosition.y += snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 225:
        snake.m_headPosition.y -= snake.speed * float(GetFrameTime());
        snake.m_headPosition.x -= snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 270:

        snake.m_headPosition.x -= snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    case 315:
        
        snake.m_headPosition.x += snake.speed * float(GetFrameTime());
        snake.m_headPosition.y += snake.speed * float(GetFrameTime());

        headPosOverflow(snake);

        break;
    }

    for(int i = 0; i < 8; i++){
        for(int i2 = 0; i2 < 8; i2++){
            tiles[i][i2].position.x = (GetScreenWidth() / 8) * i;
            tiles[i][i2].position.y = (GetScreenHeight() / 8) * i2;
        }
    }

    TraceLog(LOG_INFO, "Position: %d, %d", int(snake.m_headPosition.x), int(snake.m_headPosition.y));

}

void Game::draw(Snake& snake, Tile (&tiles)[8][8]) {
    BeginDrawing();
    ClearBackground(BLACK);

    int x = std::clamp(int(snake.m_headPosition.x), 0, 7);
    int y = std::clamp(int(snake.m_headPosition.y), 0, 7);

    DrawRectangle(
        float(tiles[x][y].position.x), 
        float(tiles[x][y].position.y),
        (GetScreenWidth() / 8),
        (GetScreenHeight() / 8),
        snake.m_headColour
    );

    EndDrawing();
}

void Game::getInput(Snake& snake) {
    if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)){
        snake.m_direction = 45;
        return;
    }
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)){
        snake.m_direction = 135;
        return;
    }
    if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)){
        snake.m_direction = 225;
        return;
    }
    if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W)){
        snake.m_direction = 315;
        return;
    }

    if(IsKeyDown(KEY_W)){
        snake.m_direction = 0;
        return;
    }
    if(IsKeyDown(KEY_D)){
        snake.m_direction = 90;
        return;
    }
    if(IsKeyDown(KEY_A)){
        snake.m_direction = 270;
        return;
    }
    if(IsKeyDown(KEY_S)){
        snake.m_direction = 180;
        return;
    }
    
    
}

void Game::headPosOverflow(Snake& snake) {
    if(snake.m_headPosition.x > 7) {
        snake.m_headPosition.x -= 8;
    }
    if(snake.m_headPosition.y > 7) {
        snake.m_headPosition.y -= 8;
    }

    if(snake.m_headPosition.x < 0) {
        snake.m_headPosition.x += 8;
    }
    if(snake.m_headPosition.y < 0) {
        snake.m_headPosition.y += 8;
    }
}