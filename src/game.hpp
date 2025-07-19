#pragma once

#include <raylib.h>
#include <vector>

#define NUMBER_OF_TILES 32

class Tile;
struct bodyPart;
struct CollisionObject;

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
        void recalcTiles(Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]);
        void calculateSquareDimensions(int& squareSize, int& offsetX, int& offsetY);
        
        bool collisionChecks(Snake& snake, Tile (&tiles)[NUMBER_OF_TILES][NUMBER_OF_TILES]);

        Vector2 getMaxSquareSize();
        int getScore() const {
            return snake.m_length;
        }
    private:

        Snake snake;

        std::vector<CollisionObject> apples;
        std::vector<CollisionObject> bombs;
        std::vector<CollisionObject> bodyParts;

        int m_squareSize = 0;
        int m_offsetX = 0;   
        int m_offsetY = 0;

        int m_screenWidth = GetScreenWidth();
        int m_screenHeight = GetScreenHeight();

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

struct CollisionObject
{
    enum Type {
        Head, // currently unused
        Body,
        Apple,
        Bomb,
        Tile
    };

    Vector2 position;
    Type type;
    Color colour;

    CollisionObject(Vector2 pos, Type t, Color c)
        : position(pos), type(t), colour(c) {}

    // Simple collision check (tile-based)
    bool isColliding(const Vector2& otherPos) const {
        return (int)position.x == (int)otherPos.x && (int)position.y == (int)otherPos.y;
    }
};
class Tile{

    public:
        
        Vector2 position;

      

};