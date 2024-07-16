#include "../Common/common.hpp"
#include "sand_tetrix.hpp"

void SandTetrix::drawBoard() {
    sf::Color lineColor(255, 255, 255, 50);
    sf::VertexArray lines(sf::Lines);
    for (int i = 0; i <= rows; ++i) {
        lines.append(sf::Vertex(sf::Vector2f(0, i * cellSize), lineColor));
        lines.append(
            sf::Vertex(sf::Vector2f(cols * cellSize, i * cellSize), lineColor));
    }
    for (int j = 0; j <= cols; ++j) {
        lines.append(sf::Vertex(sf::Vector2f(j * cellSize, 0), lineColor));
        lines.append(
            sf::Vertex(sf::Vector2f(j * cellSize, rows * cellSize), lineColor));
    }
    window->draw(lines);
}

void SandTetrix::drawSandBlock(sf::Vector2f position, sf::Color color) {
    int grainsPerCell = cellSize / sandGrainSize;
    sf::CircleShape sandBlock(sandGrainSize / 2.0f - 1);
    sandBlock.setFillColor(color);

    for (int i = 0; i < grainsPerCell; ++i) {
        for (int j = 0; j < grainsPerCell; ++j) {
            sandBlock.setPosition(position.x + i * sandGrainSize,
                                  position.y + j * sandGrainSize);
            window->draw(sandBlock);
        }
    }
}

void SandTetrix::drawSandGrain(sf::Vector2f position, sf::Color color) {
    int grainsPerCell = cellSize / sandGrainSize;
    sf::CircleShape sandGrain(sandGrainSize);
    sandGrain.setFillColor(color);

    for (int i = 0; i < grainsPerCell; ++i) {
        for (int j = 0; j < grainsPerCell; ++j) {
            sandGrain.setPosition(position.x * cellSize + i * sandGrainSize,
                                  position.y * cellSize + j * sandGrainSize);
            window->draw(sandGrain);
        }
    }
}

void SandTetrix::drawPieces() {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (board[x][y] < 0) {
                drawSandBlock(sf::Vector2f(x * cellSize, y * cellSize),
                              colors[board[x][y] - 1]);
            } else {
                drawSandGrain(sf::Vector2f(x, y), colors[board[x][y] - 1]);
            }
        }
    }

    for (const auto &pos : z) {
        drawSandBlock(sf::Vector2f(pos.x * cellSize, pos.y * cellSize),
                      currentPieceColor);
    }
}

void SandTetrix::drawPreview() {
    sf::Vector2f previewPosition(cols * cellSize + window->getSize().x / 8.0f,
                                 30.0f);

    sf::RectangleShape previewRect(sf::Vector2f(8 * cellSize, 5 * cellSize));
    previewRect.setPosition(((cols * cellSize) + window->getSize().x) * 0.42f,
                            previewPosition.y + cellSize - 20.0f);
    previewRect.setFillColor(sf::Color::Transparent);
    previewRect.setOutlineThickness(2);
    previewRect.setOutlineColor(sf::Color::White);
    window->draw(previewRect);

    int number = nextPieceIndex;
    for (auto i = 0; i < squares; ++i) {
        int modForm = forms[number][i] % 2;
        int pieceX = modForm * cellSize;
        int pieceY = (forms[number][i] / 2) * cellSize;
        int rotateX = pieceY;
        int rotateY = (modForm == 0) ? (1 - pieceX) : (2 - pieceX);

        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
        cell.setPosition(previewPosition.x + rotateX - 50,
                         previewPosition.y + rotateY + 100);
        cell.setFillColor(nextPieceColor);
        window->draw(cell);
    }
}

void SandTetrix::drawTextAtPosition(sf::Vector2f pos, sf::Color color,
                                    const std::string &str, int size) {
    sf::Text text;
    text.setFont(font);
    text.setPosition(pos.x, pos.y);
    text.setFillColor(color);
    text.setString(str);
    text.setCharacterSize(size);
    window->draw(text);
}

void SandTetrix::drawCenteredText(sf::Vector2f pos, sf::Color color,
                                  const std::string &str, int size) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);
    window->draw(text);
}

void SandTetrix::drawGameStart() {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    overlay.setFillColor(sf::Color::Black);
    window->draw(overlay);

    sf::Vector2f textTitlePos(window->getSize().x / 2.0f,
                              window->getSize().y / 2.0f - 50);
    drawCenteredText(textTitlePos, sf::Color::White, "SandTetrix", 48);

    sf::Vector2f textStartPos(window->getSize().x / 2.0f,
                              window->getSize().y / 2.0f + 20);
    drawCenteredText(textStartPos, sf::Color::White, "Press Space to Start",
                     24);
}

void SandTetrix::drawGameStats() {
    sf::Vector2f textTimePos(((cols * cellSize) + window->getSize().x) * 0.42f,
                             300.0f);
    std::string timeStr = formatTime(elapsedTime);
    drawTextAtPosition(textTimePos, sf::Color::White, timeStr, 24);

    sf::Vector2f textScorePos(textTimePos.x, 350.0f);
    std::string scoreStr = "Score: " + std::to_string(score);
    drawTextAtPosition(textScorePos, sf::Color::White, scoreStr, 24);

    sf::Vector2f textLinesClearedPos(textTimePos.x, 400.0f);
    std::string linesClearedStr = "Lines: " + std::to_string(linesCleared);
    drawTextAtPosition(textLinesClearedPos, sf::Color::White, linesClearedStr,
                       24);
}

void SandTetrix::drawGameOver() {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window->draw(overlay);

    sf::Vector2f textGameOverPos(window->getSize().x / 2.0f,
                                 window->getSize().y / 2.0f - 35.0f);
    drawCenteredText(textGameOverPos, sf::Color::White, "Game Over", 56);
    sf::Vector2f textRestartPos(window->getSize().x / 2.0f,
                                window->getSize().y / 2.0f + 30.0f);
    drawCenteredText(textRestartPos, sf::Color::White, "Press R to Restart",
                     24);
}