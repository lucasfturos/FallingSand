#include "falling_sand.hpp"

FallingSand::FallingSand(int screenWidth, int screenHeight,
                         std::shared_ptr<sf::RenderWindow> window)
    : cols(screenWidth / CELL_SIZE), rows(screenHeight / CELL_SIZE),
      window(window) {
    setupGrid();
}

std::vector<std::vector<int>> FallingSand::make2Darray() {
    return std::vector<std::vector<int>>(cols, std::vector<int>(rows, 0));
}

void FallingSand::setupGrid() {
    grid = make2Darray();
    for (auto &row : grid) {
        std::fill(row.begin(), row.end(), 0);
    }
}

sf::Color FallingSand::HSV2RGB(float h, float s, float v) {
    int i = static_cast<int>(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0:
        return sf::Color(v * 255, t * 255, p * 255);
    case 1:
        return sf::Color(q * 255, v * 255, p * 255);
    case 2:
        return sf::Color(p * 255, v * 255, t * 255);
    case 3:
        return sf::Color(p * 255, q * 255, v * 255);
    case 4:
        return sf::Color(t * 255, p * 255, v * 255);
    case 5:
        return sf::Color(v * 255, p * 255, q * 255);
    default:
        return sf::Color(0, 0, 0);
    }
}

sf::Color FallingSand::getColorByValue(int value) {
    float hue = static_cast<float>(value) / 255.0f * 360.0f;
    float saturation = 0.8f;
    float brightness = 0.8f;
    return HSV2RGB(hue / 360.0f, saturation, brightness);
}

void FallingSand::mouseDragged(sf::Vector2i mousePosition) {
    static int colorSand = 0;
    int mouseX = std::floor(mousePosition.x / CELL_SIZE);
    int mouseY = std::floor(mousePosition.y / CELL_SIZE);

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

void FallingSand::sandMovement() {
    auto nextGrid = make2Darray();
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (grid[i][j] > 0) {
                int state = grid[i][j];
                int below = (j + 1 < rows) ? grid[i][j + 1] : -1;

                int dir = 1;
                if (rand() % 2 == 0) {
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
    sf::CircleShape sand(CELL_SIZE);
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] > 0) {
                sand.setFillColor(getColorByValue(grid[i][j]));
                sand.setPosition(static_cast<float>(i * CELL_SIZE),
                                 static_cast<float>(j * CELL_SIZE));
                window->draw(sand);
            }
        }
    }
}
