#include "../headers/Enemy.h"

Enemy::Enemy(float pos_x, float pos_y) {
    this->initVariables();
    this->initShape();
    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy() {

}

void Enemy::initVariables() {
    this->pointCount = rand()%8 + 3;
    this->type = 0;
    this->speed = static_cast<float>(this->pointCount/3);
    this->hpMax = static_cast<int>(this->pointCount);
    this->hp = this->hpMax;
    this->damage = static_cast<int>(this->pointCount);
    this->points = static_cast<int>(this->pointCount);
}

void Enemy::initShape() {
    this->shape.setRadius(static_cast<float>(this->pointCount)*3);
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(Color(rand()%255+1,rand()%255+1,rand()%255+1,255));
}

void Enemy::update() {
    this->shape.move(0.f, this->speed);
}

void Enemy::render(RenderTarget *target) {
    target->draw(this->shape);

}

FloatRect Enemy::getBounds() const {
    return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const {
    return this->points;
}

const int &Enemy::getDamage() const {
    return this->damage;
}

