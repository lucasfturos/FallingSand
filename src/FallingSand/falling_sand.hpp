#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

class FallingSand {
  protected:
    const int CELL_SIZE = 10;

  private:
    int cols, rows;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::vector<int>> grid;

    sf::Color getColorByValue(int);
    sf::Color HSV2RGB(float, float, float);
    std::vector<std::vector<int>> make2Darray();

  public:
    FallingSand(int screenWidth, int screenHeight,
                std::shared_ptr<sf::RenderWindow> window);
    void setupGrid();
    void sandMovement();
    void mouseDragged(sf::Vector2i);
    void draw();
};
