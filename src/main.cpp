#include "game.hpp"

int main() {
    Game game;
    game.play();
}

/*
Todo:
    - When the snake moves, create a new bodypart where the head initially was and deleted the oldest bodypart
    - Only recalculate tile positons on window resize
    - UI
    - Gameplay probably
*/