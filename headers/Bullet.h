#ifndef GAME3_BULLET_H
#define GAME3_BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
    Sprite shape;
    Vector2f direction;
    float movementSpeedB;
public:
    Bullet()=default;
    Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();

    FloatRect getBounds() const;

    void update();
    void render(RenderTarget* target);
};


#endif //GAME3_BULLET_H
