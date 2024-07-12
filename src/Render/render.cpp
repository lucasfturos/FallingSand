#include "render.hpp"

Render::Render()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(WIDTH, HEIGHT), "Falling Sand",
          sf::Style::Titlebar | sf::Style::Close)),
      desktop(std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())),
      mousePosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2)) {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.0 - window->getSize().x / 2.0,
                     desktop->height / 2.0 - window->getSize().y / 2.0));

    setupGrid();
}

void Render::draw() {
    window->clear();

    drawGrid();
    drawPointer();

    window->display();
}

void Render::run() {
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        handleEvents();
        handleMouse();
        sandMovement();
        draw();
    }
}