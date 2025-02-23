#pragma once
#include <raylib.h>
#include <vector>
class Tile;
struct bodyPart;
class Snake{
 
    public:

        float speed; //tiles per second
        int m_length;
        Color m_headColour;
        Vector2 m_headPosition;
        int m_direction;
        std::vector<bodyPart> m_body;
        
        
};

class Game{
    public:
    
        Game();
        ~Game();
        void init(int WINDOW_WIDTH, int WINDOW_HEIGHT);
        void play();
        void update(Snake& snake, Tile (&tiles)[8][8]);
        void draw(Snake& snake, Tile (&tiles)[8][8]);
        void getInput(Snake& snake);
        bool collisionDetected();

    private:

        void headPosOverflow(Snake& snake);

        Snake snake;

    };



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
        
        //Tile();

        Vector2 position;

        enum tileHat{
            apple,
            bomb
        };

};