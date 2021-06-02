#ifndef GAME3_PLAYER_H
#define GAME3_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class Player {
    Sprite sprite;
    Texture texture;

    float movementSpeed;
    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;

    void initVariables();
    void initTexture();
    void initSprite();
public:
    Player();
    virtual ~Player();

    const Vector2f& getPos()const;
    FloatRect getBounds() const;

    void setPositon(const Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int Hp);
    void loseHp(const int value);


    void move(const float dirX, const float dirY);
    const bool canAttack();
    void updateAttack();
    void update();
    void render(RenderTarget &target);

    const int& getHp() const;
    const int& getHpMax() const;
};


#endif //GAME3_PLAYER_H
