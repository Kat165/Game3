#include "../headers/Bullet.h"

Bullet::Bullet(Texture *texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed) {

    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeedB = movement_speed;
}

Bullet::~Bullet() = default;

void Bullet::update() {
    this->shape.move(this->movementSpeedB * this->direction);
}

void Bullet::render(RenderTarget *target) {
    target->draw(this->shape);

}

FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}


