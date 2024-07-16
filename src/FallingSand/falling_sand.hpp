#pragma once

#include "../Common/common.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

class FallingSand {
  protected:
    const int cellSize = 10;

  private:
    int cols, rows;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::vector<int>> grid;

    void sandMovement();

  public:
    FallingSand(int, int, std::shared_ptr<sf::RenderWindow>);
    void setupGrid();
    void mouseDragged(sf::Vector2i);
    void draw();
};
