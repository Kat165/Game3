#ifndef GAME3_CONTROLS_H
#define GAME3_CONTROLS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

class Controls {
    RenderWindow* window;
    Font font;
    Text controlsText;
    Texture controlsBackgroundTex;
    Sprite controlsBackground;
    void initWindow();
    void initCText();
    void initTexture();
public:
    Controls();
    ~Controls();
    void run();
    void updatePollEvents();
    void udpateCText();
    void update();
    void renderCTexT();
    void renderBgTex();
    void render();

};


#endif //GAME3_CONTROLS_H
