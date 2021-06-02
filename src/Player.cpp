#include "../headers/Player.h"

Player::Player() {
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player() {

}

void Player::update() {
    this->updateAttack();
}

void Player::render(RenderTarget &target) {
    target.draw(this->sprite);

}

void Player::initTexture() {
    if(!this->texture.loadFromFile("../Textures/ship.png"))
    {
        cout<<"ERROR::PLAYER::INITTEXTURE - loading texture failed\n";
    }

}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.1f,0.1f);
    this->sprite.setPosition(350.f,500.f);
}

void Player::move(const float dirX, const float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

}

const Vector2f &Player::getPos() const {
    return this->sprite.getPosition();
}

void Player::updateAttack() {
    if (this->attackCooldown<this->attackCooldownMax)
        attackCooldown += 0.5f;

}

const bool Player::canAttack() {
    if (this->attackCooldown>=this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::initVariables() {
    this->movementSpeed = 3.f;
    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;
    this->hpMax = 50;
    this->hp = this->hpMax;
}

FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

void Player::setPositon(const Vector2f pos) {
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

const int &Player::getHp() const {
    return this->hp;
}

const int &Player::getHpMax() const {
    return this->hpMax;
}

void Player::setHp(const int Hp) {
    this->hp = Hp;
}

void Player::loseHp(const int value) {
    this->hp -= value;
    if (this->hp<0)
        this->hp = 0;
}


