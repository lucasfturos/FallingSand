#include "menu.hpp"

void Menu::handleEvents(sf::Event &event) {
    const int totalOptions = 3;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            selectedOption = (selectedOption + 1) % totalOptions;
            break;
        case sf::Keyboard::Enter:
            break;
        default:
            break;
        }
    }
}
