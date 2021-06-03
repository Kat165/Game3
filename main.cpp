#include<ctime>
#include "headers/Game.h"
#include "headers/Controls.h"


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Controls controls;
    controls.run();

    Game game;
    game.run();
    return 0;
}
