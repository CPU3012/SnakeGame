#include "game.hpp"
#include <raylib.h>
#include <vector>
#include <algorithm>

Game::Game() {
    init(800, 800); // Initial Window Dimentions
}
Game::~Game(){
    CloseWindow(); 
}

void Game::init(int WINDOW_WIDTH, int WINDOW_HEIGHT){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPU's Snake Game");
    SetExitKey(KEY_NULL);

    snake.m_headColour = BLUE;
    snake.m_length = 0;
    snake.speed = 2.0;
    snake.m_direction = 90;
    snake.m_headPosition.x = 0; snake.m_headPosition.y = 0;

}

void Game::play() {

    Tile tiles[NUMBER_OF_TILES][NUMBER_OF_TILES];

    // Main game loop
    while (!WindowShouldClose()) {
        
        m_screenWidth = GetScreenWidth();
        m_screenHeight = GetScreenHeight();

        //if(collisionDetected()) return;
        getInput(snake);
        update(snake, tiles);
        draw(snake, tiles);

    }

    
}

void Game::update(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]) {

    double frameTime = GetFrameTime();
    
    Vector2 oldSnakePosition;
    switch (snake.m_direction)
    {
    case 0:

        snake.m_headPosition.x = int(snake.m_headPosition.x);    

        snake.m_headPosition.y -= snake.speed * double(frameTime);
        headPosOverflow(snake);

        break;
    case 90:

        snake.m_headPosition.y = int(snake.m_headPosition.y);    

        snake.m_headPosition.x += snake.speed * double(frameTime);
        headPosOverflow(snake);

        break;
    case 180:

        snake.m_headPosition.x = int(snake.m_headPosition.x);

        snake.m_headPosition.y += snake.speed * double(frameTime);
        headPosOverflow(snake);

        break;
    case 270:

        snake.m_headPosition.y = int(snake.m_headPosition.y);

        snake.m_headPosition.x -= snake.speed * double(frameTime);
        headPosOverflow(snake);

        break;
    }
    /*
    The head position is always rounded down before rendering, this means 
    the player will only visually move a full tile at a time.
    */

    for(int i = 0; i < NUMBER_OF_TILES; i++){
        for(int i2 = 0; i2 < NUMBER_OF_TILES; i2++){

            tiles[i][i2].position.x = double(m_screenWidth / NUMBER_OF_TILES) * i;
            tiles[i][i2].position.y = double(m_screenHeight / NUMBER_OF_TILES) * i2;

        }
    }

}

void Game::draw(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]) {

    BeginDrawing();
    ClearBackground(BLACK);


    Vector2 playerPostion;
    playerPostion.x = std::clamp(int(snake.m_headPosition.x), 0, (NUMBER_OF_TILES - 1));
    playerPostion.y = std::clamp(int(snake.m_headPosition.y), 0, (NUMBER_OF_TILES - 1));

    //Draw tile pattern
    Color tileColour;
    for(int i = 0; i < NUMBER_OF_TILES; i++){
        for(int i2 = 0; i2 < NUMBER_OF_TILES; i2++){

            if (((i + 1) + (i2 + 1)) % 2 == 0)
            {
                tileColour = BEIGE;
            } else {
                tileColour = BROWN;
            }
            
            DrawRectangle(

                int(tiles[i][i2].position.x),
                int(tiles[i][i2].position.y),

                m_screenWidth / NUMBER_OF_TILES,
                m_screenHeight / NUMBER_OF_TILES,

                tileColour

            );

        }
    }

    //Draw player
    DrawRectangle(

        int(tiles[int(playerPostion.x)][int(playerPostion.y)].position.x), 
        int(tiles[int(playerPostion.x)][int(playerPostion.y)].position.y),

        (m_screenWidth / NUMBER_OF_TILES),
        (m_screenHeight / NUMBER_OF_TILES),

        snake.m_headColour

    );

    EndDrawing();
}

void Game::getInput(Snake& snake) {
    
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

    if(snake.m_headPosition.x > (NUMBER_OF_TILES - 1)) {
        snake.m_headPosition.x -= NUMBER_OF_TILES;
    }
    if(snake.m_headPosition.y > (NUMBER_OF_TILES - 1)) {
        snake.m_headPosition.y -= NUMBER_OF_TILES;
    }

    if(snake.m_headPosition.x < 0) {
        snake.m_headPosition.x += NUMBER_OF_TILES;
    }
    if(snake.m_headPosition.y < 0) {
        snake.m_headPosition.y += NUMBER_OF_TILES;
    }

}