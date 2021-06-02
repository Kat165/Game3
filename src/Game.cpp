#include "../headers/Game.h"

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initGui();
    this->initWorld();
    this->initPlayer();
    this->initEnemies();
    this->initVariables();
}

Game::~Game() {
    delete this->window;
    delete this->player;

    for (auto &i : this->textures) {
        delete i.second;
    }

    for (auto *i : this->bullets) {
        delete i;
    }

    for (auto *i : this->enemies) {
        delete i;
    }
}

void Game::run() {
    while (this->window->isOpen())
    {
        this->updatePollEvents();
        if (this->player->getHp()>0)
            this->update();
        this->render();
    }
}

void Game::initWindow() {
    this->window = new RenderWindow(VideoMode(800, 600),
                                    "Game 3", Style::Close | Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::update() {
    this->updateInput();
    this->player->update();
    this->updateCollision();
    this->updateBullet();
    this->updateEnemies();
    this->updateCombat();
    this->updateGui();
    this->updateWorld();
}

void Game::render() {
    this->window->clear();

    this->renderWorld();

    this->player->render(*this->window);

    for(auto *bullet : this->bullets)
    {
        bullet->render(this->window);
    }

    for(auto *enemy : this->enemies)
    {
        enemy->render(this->window);
    }

    this->renderGui();

    if (this->player->getHp()<=0)
        this->window->draw(this->endGameText);

    this->window->display();
}

void Game::initPlayer() {
    this->player = new Player();
}

void Game::updatePollEvents() {
    Event e{};
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == Event::Closed)
            this->window->close();
        if (e.Event::key.code == Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput() {
    if (Keyboard::isKeyPressed(Keyboard::A))
        this->player->move(-1.f,0.f);
    if (Keyboard::isKeyPressed(Keyboard::D))
        this->player->move(1.f,0.f);
    if (Keyboard::isKeyPressed(Keyboard::W))
        this->player->move(0.f,-1.f);
    if (Keyboard::isKeyPressed(Keyboard::S))
        this->player->move(0.f,1.f);

    if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"],
                           this->player->getPos().x + this->player->getBounds().width/2.f, this->player->getPos().y,
                           0.f, -1.f, 5.f));
    }
}

void Game::initTextures() {
    this->textures["BULLET"] = new Texture();
    if(!this->textures["BULLET"]->loadFromFile("../Textures/bullet.png"))
        cout<<"GAME::INITTEXTURES failed to load bullet texture\n";
}

void Game::updateBullet() {
    unsigned counter = 0;
    for(auto *bullet : this->bullets)
    {
        bullet->update();

        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
        }
        ++counter;
    }

}

void Game::updateEnemies() {
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand()% this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.f;
    }

    unsigned counter = 0;
    for(auto *enemy : this->enemies)
    {
        enemy->update();

        if (enemy->getBounds().top > this->window->getSize().y)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        } else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        ++counter;
    }
}

void Game::initEnemies() {
    this->spawnTimerMax = 50.f;
    this->spawnTimer = spawnTimerMax;

}

void Game::initGui() {

    if (!this->font.loadFromFile(R"(C:\Users\kasia\Documents\Fonts\Dosis-Light.ttf)"))
        cout<<"GAME::INITGUI - failed to load font from file" <<endl;
    this->pointText.setPosition(650.f, 25.f);
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(30);
    this->pointText.setFillColor(Color::White);
    this->pointText.setString("test");

    this->endGameText.setFont(this->font);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setFillColor(Color::Red);
    this->endGameText.setString("Game over");
    this->endGameText.setPosition(this->window->getSize().x/2.f - this->endGameText.getGlobalBounds().width/2.f,
                                  this->window->getSize().y/2.f - this->endGameText.getGlobalBounds().height/2.f);

    this->playerHpBar.setSize(Vector2f(300.f,25.f));
    this->playerHpBar.setFillColor(Color::Red);
    this->playerHpBar.setPosition(Vector2f(20.f,25.f));
    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(Color(25.f,25.f,25.f,200.f));
}

void Game::updateGui() {
    stringstream ss;
    ss<<"Points: "<<this->points;
    this->pointText.setString(ss.str());

    auto hpPrecent = static_cast<float>(this->player->getHp())/ this->player->getHpMax();
    this->playerHpBar.setSize(Vector2f(300.f * hpPrecent, this->playerHpBar.getSize().y));
}

void Game::renderGui() {
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::updateCombat() {
    for(int i=0; i<this->enemies.size(); ++i)
    {
        bool enemy_deleted = false;
        for (int j = 0; j < this->bullets.size() && !enemy_deleted; ++j) {
            if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()))
            {
                this->points += this->enemies[i]->getPoints();

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[j];
                this->bullets.erase(this->bullets.begin() + j);

                enemy_deleted = true;
            }
        }
    }
}

void Game::initWorld() {
    if(!this->worldBackgroundTex.loadFromFile("../Textures/space.png"))
        cout<<"GAME::INITWORLD - failed to init background texture"<<endl;

    this->worldBackground.setTexture(this->worldBackgroundTex);
    this->worldBackground.setScale(0.5f,0.5f);
}

void Game::renderWorld() {
    this->window->draw(this->worldBackground);
}

void Game::updateWorld() {

}

void Game::updateCollision() {
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }

}

void Game::initVariables() {
    this->points = 0;
}
