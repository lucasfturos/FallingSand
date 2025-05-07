#include "sand_tetrix.hpp"

void SandTetrix::handleEvents(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            // Gira
            rotate = true;
            break;
        case sf::Keyboard::S: {
            // Dash
            dash = 0.05f;
            break;
        }
        case sf::Keyboard::A: {
            // Move para esquerda
            --dirX;
            break;
        }
        case sf::Keyboard::D: {
            // Move para direita
            ++dirX;
            break;
        }
        case sf::Keyboard::Space:
            // Pause
            isRunning = !isRunning;
            break;
        default:
            break;
        }
    }
}
