#include "falling_sand.hpp"
#include "../Common/common.hpp"

FallingSand::FallingSand(int screenWidth, int screenHeight,
                         std::shared_ptr<sf::RenderWindow> window)
    : cols(screenWidth / cellSize), rows(screenHeight / cellSize),
      window(window) {
    setupGrid();
}

void FallingSand::setupGrid() {
    grid = make2Darray(rows, cols);
    for (auto &row : grid) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void FallingSand::mouseDragged(sf::Vector2i mousePosition) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        static int colorSand = 0;
        int mouseX = std::floor(mousePosition.x / cellSize);
        int mouseY = std::floor(mousePosition.y / cellSize);

        int matrixSize = 5;
        int extent = std::floor(matrixSize / 2);
        for (int i = -extent; i <= extent; ++i) {
            for (int j = -extent; j <= extent; ++j) {
                int x = mouseX + i;
                int y = mouseY + j;
                if (x >= 0 && x < cols && y >= 0 && y < rows) {
                    grid[x][y] = colorSand;
                }
            }
        }
        colorSand = (colorSand + 1) % 360;
    }
}

void FallingSand::sandMovement() {
    auto nextGrid = make2Darray(rows, cols);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (grid[i][j] > 0) {
                int state = grid[i][j];
                int below = (j + 1 < rows) ? grid[i][j + 1] : -1;

                int dir = 1;
                if (std::rand() % 2 == 0) {
                    dir *= -1;
                }

                int belowA = (i + dir >= 0 && i + dir < cols && j + 1 < rows)
                                 ? grid[i + dir][j + 1]
                                 : -1;
                int belowB = (i - dir >= 0 && i - dir < cols && j + 1 < rows)
                                 ? grid[i - dir][j + 1]
                                 : -1;

                if (below == 0) {
                    nextGrid[i][j + 1] = state;
                } else if (belowA == 0) {
                    nextGrid[i + dir][j + 1] = state;
                } else if (belowB == 0) {
                    nextGrid[i - dir][j + 1] = state;
                } else {
                    nextGrid[i][j] = state;
                }
            }
        }
    }

    grid = nextGrid;
}

void FallingSand::draw() {
    sandMovement();

    sf::CircleShape sand(cellSize);
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] > 0) {
                sand.setFillColor(getColorByValue(grid[i][j]));
                sand.setPosition(static_cast<float>(i * cellSize),
                                 static_cast<float>(j * cellSize));
                window->draw(sand);
            }
        }
    }
}
