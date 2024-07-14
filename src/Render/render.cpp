#include "render.hpp"

Render::Render()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(WIDTH, HEIGHT), "Falling Sand",
          sf::Style::Titlebar | sf::Style::Close)),
      desktop(std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())),
      fallingSand(std::make_shared<FallingSand>(WIDTH, HEIGHT, window)),
      mousePosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2)) {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.0 - window->getSize().x / 2.0,
                     desktop->height / 2.0 - window->getSize().y / 2.0));
}

void Render::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed: {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window->close();
                break;
            case sf::Keyboard::R:
                fallingSand->setupGrid();
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Render::handleMouse() {
    mousePosition = sf::Mouse::getPosition(*window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        fallingSand->mouseDragged(mousePosition);
    }
}

void Render::drawPointer() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(static_cast<sf::Vector2f>(mousePosition));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        window->draw(circle);
    }
}

void Render::draw() {
    window->clear();
    fallingSand->draw();
    drawPointer();
    window->display();
}

void Render::run() {
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        handleEvents();
        handleMouse();
        fallingSand->sandMovement();
        draw();
    }
}
