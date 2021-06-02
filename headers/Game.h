#ifndef GAME3_GAME_H
#define GAME3_GAME_H

#include <sstream>
#include <map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game {
    RenderWindow* window;
    Player* player;

    float spawnTimer;
    float spawnTimerMax;
    unsigned points;

    map <string, Texture*> textures;
    vector <Bullet*> bullets;
    vector<Enemy*> enemies;

    Font font;
    Text pointText;
    Text endGameText;

    Texture worldBackgroundTex;
    Sprite worldBackground;

    RectangleShape playerHpBar;
    RectangleShape playerHpBarBack;

    void initWindow();
    void initTextures();
    void initGui();
    void initWorld();
    void initVariables();
    void initPlayer();
    void initEnemies();
public:
    Game();
    virtual ~Game();

    void run();
    void updateBullet();
    void updatePollEvents();
    void updateInput();
    void updateEnemies();
    void updateCombat();
    void updateGui();
    void updateWorld();
    void updateCollision();
    void update();
    void renderGui();
    void renderWorld();
    void render();

};


#endif //GAME3_GAME_H
