#include "game.hpp"

#include <raylib.h>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <ctime>

Game::Game() {
    init(800, 800); // Initial Window Dimentions
}
Game::~Game(){
    CloseWindow(); 
}

void Game::init(int WINDOW_WIDTH, int WINDOW_HEIGHT){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake Game");
    SetExitKey(KEY_NULL);

    snake.m_headColour = BLUE;
    snake.m_length = 0;
    snake.speed = 3.0; // Set the speed of the snake
    snake.m_direction = 90; // Initial direction (0 = up, 90 = right, 180 = down, 270 = left)
    snake.m_headPosition.x = 0; snake.m_headPosition.y = 0;

    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::play() {

    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();
    Tile tiles[NUMBER_OF_TILES][NUMBER_OF_TILES];
    
    calculateSquareDimensions(m_squareSize, m_offsetX, m_offsetY);
    recalcTiles(tiles);

    // --- Spawn apples at random positions ---
    apples.clear();
    int numApples = 3; // Set how many apples you want
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < numApples; ++i) {
        Vector2 pos;
        pos.x = rand() % NUMBER_OF_TILES;
        pos.y = rand() % NUMBER_OF_TILES;
        apples.emplace_back(pos, CollisionObject::Apple, RED);
    }

    // Main game loop
    while (!WindowShouldClose()) {
        
        m_screenWidth = GetScreenWidth();
        m_screenHeight = GetScreenHeight();

        collisionChecks(snake, tiles);
        getInput(snake);
        update(snake, tiles);
        draw(snake, tiles);

    }

    
}

void Game::update(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]) {

    double frameTime = GetFrameTime();
    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();

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

    if (IsWindowResized()) {
        calculateSquareDimensions(m_squareSize, m_offsetX, m_offsetY);
        recalcTiles(tiles);
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

                (m_squareSize / NUMBER_OF_TILES),
                (m_squareSize / NUMBER_OF_TILES),

                tileColour

            );

        }
    }

    // Draw apples
    for (const auto& apple : apples) {
    // Clamp apple position to board limits, idk if this is necessary but I did it anyway
    int x = std::clamp(int(apple.position.x), 0, NUMBER_OF_TILES - 1);
    int y = std::clamp(int(apple.position.y), 0, NUMBER_OF_TILES - 1);

    DrawRectangle(
        int(tiles[x][y].position.x),
        int(tiles[x][y].position.y),
        (m_squareSize / NUMBER_OF_TILES),
        (m_squareSize / NUMBER_OF_TILES),
        apple.colour
    );
}

    //Draw player
    DrawRectangle(

        int(tiles[int(playerPostion.x)][int(playerPostion.y)].position.x), 
        int(tiles[int(playerPostion.x)][int(playerPostion.y)].position.y),

        (m_squareSize / NUMBER_OF_TILES),
        (m_squareSize / NUMBER_OF_TILES),

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

void Game::recalcTiles(Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]) {

    for(int i = 0; i < NUMBER_OF_TILES; i++) {
        for(int i2 = 0; i2 < NUMBER_OF_TILES; i2++) {

        tiles[i][i2].position.x = double(m_squareSize / NUMBER_OF_TILES * i) + m_offsetX;
        tiles[i][i2].position.y = double(m_squareSize / NUMBER_OF_TILES * i2) + m_offsetY;

        }
    }
}

// Calculate and store the dimensions of a perfect square that fits inside the window
void Game::calculateSquareDimensions(int& squareSize, int& offsetX, int& offsetY) {

    // Determine the size of the square (smallest dimension)
    squareSize = std::min(m_screenWidth, m_screenHeight);

    // Calculate offsets to center the square in the window
    offsetX = (m_screenWidth - squareSize) / 2;
    offsetY = (m_screenHeight - squareSize) / 2;
}

bool Game::collisionChecks(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]) {

    // Check for collisions with bombs or body parts
    for (const auto& bomb : bombs) {
        if (bomb.isColliding(snake.m_headPosition)) {
            // Handle bomb collision, e.g., end game or reduce snake length
            return true; // Collision detected
        }
    }
    for (const auto& bodyPart : bodyParts) {
        if (bodyPart.isColliding(snake.m_headPosition)) {
            // Handle collision with snake's own body
            return true; // Collision detected
        }
    }

    // Check for collisions with apples
    for (int i = 0; i < apples.size(); ++i) {
        CollisionObject& apple = apples[i];
        
        // Check if the snake's head collides with the apple
        if (apple.isColliding(snake.m_headPosition)) {
            // Handle apple eaten, e.g., increase snake length, remove apple, etc.
            apples.erase(apples.begin() + i); // Remove the apple
            snake.m_length++; // Increase snake length
            // Optionally, spawn a new apple at a random position
            // add another body part to the vector of body parts

            return true; // Collision detected
        }
    }

    
    // Placeholder for collision detection logic
    // This function should return true if a collision is detected
    return false;
}
