#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Menu {
  protected:
    const std::string filepathFont =
        "assets/font/press-start-2p/PressStart2P-Regular.ttf";

  private:
    sf::Font font;
    sf::Text title;
    sf::Text option1;
    sf::Text option2;
    sf::Text option3;

    int selectedOption;

    void layoutOption(int, int);
    void borderOption(sf::RenderWindow &);
    void highlightOption(sf::RenderWindow &, sf::Text &, int);
    void setupText(sf::Text &, const std::string &, int, sf::Vector2f);

  public:
    Menu(int, int);

    void resize(int, int);
    void handleEvents(sf::Event &);
    void draw(sf::RenderWindow &);

    int getSelection() const { return selectedOption; }
};
