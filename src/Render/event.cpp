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
            case sf::Keyboard::Num1:
                opc = 1;
                break;
            case sf::Keyboard::Num2:
                opc = 2;
                break;
            case sf::Keyboard::L:
                useShader = !useShader;
                break;
            case sf::Keyboard::R: {
                if (opc == 1) {
                    fallingSand->setupGrid();
                }
                if (opc == 2) {
                    sandTetrix->setupGame();
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        default:
            break;
        }

        if (opc == 2) {
            sandTetrix->handleEvents(event);
        }
    }
}

void Render::handleMouse() {
    mousePosition = sf::Mouse::getPosition(*window);
    if (opc == 1) {
        fallingSand->mouseDragged(mousePosition);
    }
}