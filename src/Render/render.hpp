#pragma once

#include "../FallingSand/falling_sand.hpp"
#include "../SandTetrix/sand_tetrix.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Render {
  protected:
    const int WIDTH = 1080;
    const int HEIGHT = 720;

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;
    std::shared_ptr<FallingSand> fallingSand;
    std::shared_ptr<SandTetrix> sandTetrix;
    sf::Vector2i mousePosition;
    int opc;

  private:
    void handleEvents();
    void handleMouse();

    void drawPointer();
    void draw();

  public:
    Render();
    void run();
};
