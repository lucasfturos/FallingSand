#pragma once

#include "../FallingSand/falling_sand.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Render {
  protected:
    const int WIDTH = 1080;
    const int HEIGHT = 720;

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;
    sf::Vector2i mousePosition;

    std::shared_ptr<FallingSand> fallingSand;

  private:
    void handleEvents();
    void handleMouse();

    void drawPointer();
    void draw();

  public:
    Render();
    void run();
};
