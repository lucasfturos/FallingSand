#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

class FallingSand {
  protected:
    const int cellSize = 10;

  private:
    int cols, rows;
    std::vector<std::vector<int>> grid;

    void sandMovement();

  public:
    FallingSand(int, int);

    void setupGrid();
    void resize(int, int);
    void mouseDragged(sf::Vector2i);
    void draw(sf::RenderTarget &);
};
