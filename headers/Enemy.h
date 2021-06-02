#ifndef GAME3_ENEMY_H
#define GAME3_ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy {
    CircleShape shape;
    int type;
    float speed;
    int hp;
    int hpMax;
    int damage;
    int points;
    unsigned pointCount;

    void initVariables();
    void initShape();
public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    FloatRect getBounds()const;
    const int& getPoints()const;
    const int& getDamage()const;
    void update();
    void render(RenderTarget* target);

};


#endif //GAME3_ENEMY_H
