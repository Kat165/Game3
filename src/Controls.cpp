#include "../headers/Controls.h"

Controls::Controls() {
    this->initWindow();
    this->initTexture();
    this->initCText();
}

Controls::~Controls() {
    delete this->window;
}

void Controls::run() {
    while (this->window->isOpen())
    {
        this->updatePollEvents();
        this->update();
        this->render();
    }
}

void Controls::initWindow() {
    this->window = new RenderWindow(VideoMode(800, 600),
                                    "Game 3", Style::Close | Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Controls::initCText() {
    if (!this->font.loadFromFile(R"(C:\Users\kasia\Documents\Fonts\Dosis-Light.ttf)"))
        cout<<"CONTROLS::INITCTEXT - failed to load font from file" <<endl;
    this->controlsText.setPosition(650.f, 25.f);
    this->controlsText.setFont(this->font);
    this->controlsText.setCharacterSize(60);
    this->controlsText.setFillColor(Color::White);
    this->controlsText.setString("test");
}

void Controls::initTexture() {
    if(!this->controlsBackgroundTex.loadFromFile("../Textures/space.png"))
        cout<<"CONTROLS::INITTEXTURE - failed to init background texture"<<endl;

    this->controlsBackground.setTexture(this->controlsBackgroundTex);
    this->controlsBackground.setScale(0.5f,0.5f);

}

void Controls::updatePollEvents() {
    Event e{};
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == Event::Closed)
            this->window->close();
        if (e.Event::key.code == Keyboard::Enter)
            this->window->close();
    }
}

void Controls::udpateCText() {
    stringstream ss;
    ss<<"Use W A S D to move.\nDestroy the asteroids\nand try not to crush your ship.\nPress enter to continue";
    this->controlsText.setString(ss.str());
    this->controlsText.setFillColor(Color::White);
    this->controlsText.setOutlineColor(Color::Black);
    this->controlsText.setOutlineThickness(2.f);
    this->controlsText.setPosition(100.f, 135.f);
}

void Controls::update() {
    this->udpateCText();
}

void Controls::renderCTexT() {
    this->window->draw(this->controlsText);
}

void Controls::renderBgTex() {
    this->window->draw(this->controlsBackground);
}

void Controls::render() {
    this->window->clear();
    this->renderBgTex();
    this->renderCTexT();
    this->window->display();
}






