#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

class Render {
  protected:
    const int WIDTH = 1080;
    const int HEIGHT = 720;
    const int CELL_SIZE = 10;
    const int cols = WIDTH / CELL_SIZE;
    const int rows = HEIGHT / CELL_SIZE;

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;
    sf::Vector2i mousePosition;

    std::vector<std::vector<int>> grid;

  private:
    std::vector<std::vector<int>> make2Darray();
    sf::Color getColorByValue(int);

    void setupGrid();
    void sandMovement();
    void mouseDragged();

    void handleEvents();
    void handleMouse();

    void drawPointer();
    void drawGrid();
    void draw();

  public:
    Render();
    void run();
};
