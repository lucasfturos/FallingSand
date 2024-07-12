#include "render.hpp"

void Render::drawPointer() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::CircleShape circle(CELL_SIZE);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(static_cast<sf::Vector2f>(mousePosition));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        window->draw(circle);
    }
}

void Render::drawGrid() {
    sf::CircleShape sand(CELL_SIZE);
    for (auto i = 0U; i < grid.size(); ++i) {
        for (auto j = 0u; j < grid[i].size(); ++j) {
            if (grid[i][j] > 0) {
                sand.setFillColor(getColorByValue(grid[i][j]));
                sand.setPosition(static_cast<float>(i * CELL_SIZE),
                                 static_cast<float>(j * CELL_SIZE));
                window->draw(sand);
            }
        }
    }
}
