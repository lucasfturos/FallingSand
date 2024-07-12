#include "render.hpp"

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
                setupGrid();
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
        mouseDragged();
    }
}
