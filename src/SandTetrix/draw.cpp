#include "sand_tetrix.hpp"
#include <iomanip>
#include <sstream>

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

void SandTetrix::drawPieces() {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (board[x][y] != 0) {
                sf::RectangleShape cell(
                    sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(colors[board[x][y] - 1]);
                window->draw(cell);
            }
        }
    }
    for (const auto &pos : z) {
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
        cell.setPosition(pos.x * cellSize, pos.y * cellSize);
        if (board[pos.x][pos.y] > 0) {
            cell.setFillColor(colors[board[pos.x][pos.y] - 1]);
        }
        cell.setFillColor(currentPieceColor);
        window->draw(cell);
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

void SandTetrix::drawTextParams(sf::Vector2f pos, sf::Color color,
                                const std::string &str, int size) {
    sf::Text text;
    text.setFont(font);
    text.setPosition(pos.x, pos.y);
    text.setFillColor(color);
    text.setString(str);
    text.setCharacterSize(size);
    window->draw(text);
}

std::string SandTetrix::formatTime(float seconds) {
    int totalSeconds = static_cast<int>(seconds);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int secs = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << secs;
    return oss.str();
}

void SandTetrix::drawText() {
    sf::Vector2f textTimePos(((cols * cellSize) + window->getSize().x) * 0.42f,
                             300.0f);
    std::string timeStr = formatTime(elapsedTime);
    drawTextParams(textTimePos, sf::Color::White, timeStr, 24);

    sf::Vector2f textScorePos(textTimePos.x, 350.0f);
    std::string scoreStr = "Score: " + std::to_string(score);
    drawTextParams(textScorePos, sf::Color::White, scoreStr, 24);

    sf::Vector2f textLinesClearedPos(textTimePos.x, 400.0f);
    std::string linesClearedStr = "Lines: " + std::to_string(linesCleared);
    drawTextParams(textLinesClearedPos, sf::Color::White, linesClearedStr, 24);
}

void SandTetrix::drawGameOver() {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window->draw(overlay);

    sf::Text textGameOver;
    textGameOver.setFont(font);
    textGameOver.setFillColor(sf::Color::White);
    textGameOver.setString("Game Over");
    textGameOver.setCharacterSize(56);

    sf::FloatRect textRect = textGameOver.getLocalBounds();
    textGameOver.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
    textGameOver.setPosition(sf::Vector2f(window->getSize().x / 2.0f,
                                          window->getSize().y / 2.0f - 35.0f));
    window->draw(textGameOver);

    sf::Text textRestart;
    textRestart.setFont(font);
    textRestart.setFillColor(sf::Color::White);
    textRestart.setString("Press R to Restart");
    textRestart.setCharacterSize(24);

    sf::FloatRect restartRect = textRestart.getLocalBounds();
    textRestart.setOrigin(restartRect.left + restartRect.width / 2.0f,
                          restartRect.top + restartRect.height / 2.0f);
    textRestart.setPosition(sf::Vector2f(window->getSize().x / 2.0f,
                                         window->getSize().y / 2.0f + 30.0f));
    window->draw(textRestart);
}