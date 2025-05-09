#include "render.hpp"

void Render::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::Resized: {
            sf::FloatRect visibleArea(0, 0, event.size.width,
                                      event.size.height);
            window->setView(sf::View(visibleArea));

            renderTex.create(event.size.width, event.size.height);
            shader.setUniform("resolution", sf::Vector2f(renderTex.getSize()));

            if (menu) {
                menu->resize(event.size.width, event.size.height);
            }
            if (fallingSand) {
                fallingSand->resize(event.size.width, event.size.height);
            }
            if (sandTetrix) {
                sandTetrix->resize(event.size.width, event.size.height);
            }
            break;
        }
        case sf::Event::KeyPressed: {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                window->close();
                break;
            case sf::Keyboard::Enter:
                if (opc == 0) {
                    int selection = menu->getSelection();
                    switch (selection) {
                    case 0:
                        opc = 1;
                        break;
                    case 1:
                        opc = 2;
                        break;
                    case 2:
                        window->close();
                        break;
                    default:
                        break;
                    }
                }
                break;
            case sf::Keyboard::L:
                useShader = !useShader;
                break;
            case sf::Keyboard::R: {
                resetGameState();
                break;
            }
            case sf::Keyboard::M:
                resetGameState();
                opc = 0;
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }

        switch (opc) {
        case 0:
            menu->handleEvents(event);
            break;
        case 2:
            sandTetrix->handleEvents(event);
            break;
        default:
            break;
        }
    }
}

void Render::handleMouse() {
    mousePosition = sf::Mouse::getPosition(*window);
    if (opc == 1) {
        fallingSand->mouseDragged(mousePosition);
    }
}

void Render::resetGameState() {
    if (opc == 1 && fallingSand) {
        fallingSand->setupGrid();
    }
    if (opc == 2 && sandTetrix) {
        sandTetrix->setupGame();
    }
}
