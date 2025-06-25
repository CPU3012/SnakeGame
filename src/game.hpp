#pragma once

#include <raylib.h>
#include <vector>

#define NUMBER_OF_TILES 32

class Tile;
struct bodyPart;

class Snake{
 
    public:

        double speed; //The rate of change of distance in tiles per second

        int m_length;
        int m_direction;

        Color m_headColour;

        Vector2 m_headPosition;
        
        std::vector<bodyPart> m_body;
        
        
};

class Game{
    
    public:
    
        Game();
        ~Game();

        void init(int WINDOW_WIDTH, int WINDOW_HEIGHT);
        void play();
        void update(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]);
        void draw(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]);
        void getInput(Snake& snake);
        void headPosOverflow(Snake& snake); //probably needs a better name#
        Vector2 getMaxSquareSize();

        bool collisionDetected();

    private:

        Snake snake;

        int m_screenWidth = GetScreenWidth();
        int m_screenHeight = GetScreenHeight();
        Vector2 m_playArea; //Should probably not use a vector for this(due to type conversion nonsense, floating point inaccuracy, etc), but it is convenient for now

    };




    /*
        Delete oldest part and create a new one in the previous head
    */
 struct bodyPart
{
    bodyPart() {
        colour = SKYBLUE;
    };

   Vector2 position;

   Color colour;

};


class Tile{

    public:
        
        Vector2 position;

        enum tileHat{
            apple,
            bomb
        };

};