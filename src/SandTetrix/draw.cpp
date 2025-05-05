#include "Common/common.hpp"
#include "sand_tetrix.hpp"

void SandTetrix::drawBoard(sf::RenderTarget &target) {
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
    target.draw(lines);
}

void SandTetrix::drawSandBlock(sf::RenderTarget &target, sf::Vector2f position,
                               sf::Color color) {
    sf::RectangleShape sandBlock(sf::Vector2f(cellSize - 1, cellSize - 1));
    sandBlock.setFillColor(color);
    sandBlock.setPosition(position.x, position.y);
    target.draw(sandBlock);
}

void SandTetrix::drawPieces(sf::RenderTarget &target) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (board[x][y] < 0) {
                drawSandBlock(target, sf::Vector2f(x * cellSize, y * cellSize),
                              colors[board[x][y] - 1]);
            } else {
                drawSandBlock(target, sf::Vector2f(x * cellSize, y * cellSize),
                              colors[board[x][y] - 1]);
            }
        }
    }

    for (const auto &pos : z) {
        drawSandBlock(target, sf::Vector2f(pos.x * cellSize, pos.y * cellSize),
                      currentPieceColor);
    }
}

void SandTetrix::drawPreview(sf::RenderTarget &target) {
    sf::Vector2f previewPosition(cols * cellSize + target.getSize().x / 8.0f,
                                 30.0f);

    sf::RectangleShape previewRect(sf::Vector2f(8 * cellSize, 5 * cellSize));
    previewRect.setPosition(((cols * cellSize) + target.getSize().x) * 0.42f,
                            previewPosition.y + cellSize - 20.0f);
    previewRect.setFillColor(sf::Color::Transparent);
    previewRect.setOutlineThickness(2);
    previewRect.setOutlineColor(sf::Color::White);
    target.draw(previewRect);

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
        target.draw(cell);
    }
}

void SandTetrix::drawTextAtPosition(sf::RenderTarget &target, sf::Vector2f pos,
                                    sf::Color color, const std::string &str,
                                    int size) {
    sf::Text text;
    text.setFont(font);
    text.setPosition(pos.x, pos.y);
    text.setFillColor(color);
    text.setString(str);
    text.setCharacterSize(size);
    target.draw(text);
}

void SandTetrix::drawCenteredText(sf::RenderTarget &target, sf::Vector2f pos,
                                  sf::Color color, const std::string &str,
                                  int size) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);
    target.draw(text);
}

void SandTetrix::drawGameStart(sf::RenderTarget &target) {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));
    overlay.setFillColor(sf::Color::Black);
    target.draw(overlay);

    sf::Vector2f textTitlePos(target.getSize().x / 2.0f,
                              target.getSize().y / 2.0f - 50);
    drawCenteredText(target, textTitlePos, sf::Color::White, "SandTetrix", 48);

    sf::Vector2f textStartPos(target.getSize().x / 2.0f,
                              target.getSize().y / 2.0f + 20);
    drawCenteredText(target, textStartPos, sf::Color::White,
                     "Press Space to Start", 24);
}

void SandTetrix::drawGameStats(sf::RenderTarget &target) {
    sf::Vector2f textTimePos(((cols * cellSize) + target.getSize().x) * 0.42f,
                             300.0f);
    std::string timeStr = formatTime(elapsedTime);
    drawTextAtPosition(target, textTimePos, sf::Color::White, timeStr, 24);

    sf::Vector2f textScorePos(textTimePos.x, 350.0f);
    std::string scoreStr = "Score: " + std::to_string(score);
    drawTextAtPosition(target, textScorePos, sf::Color::White, scoreStr, 24);

    sf::Vector2f textLinesClearedPos(textTimePos.x, 400.0f);
    std::string linesClearedStr = "Lines: " + std::to_string(linesCleared);
    drawTextAtPosition(target, textLinesClearedPos, sf::Color::White,
                       linesClearedStr, 24);
}

void SandTetrix::drawGameOver(sf::RenderTarget &target) {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    target.draw(overlay);

    sf::Vector2f textGameOverPos(target.getSize().x / 2.0f,
                                 target.getSize().y / 2.0f - 35.0f);
    drawCenteredText(target, textGameOverPos, sf::Color::White, "Game Over",
                     56);
    sf::Vector2f textRestartPos(target.getSize().x / 2.0f,
                                target.getSize().y / 2.0f + 30.0f);
    drawCenteredText(target, textRestartPos, sf::Color::White,
                     "Press R to Restart", 24);
}