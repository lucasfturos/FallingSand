#include "sand_tetrix.hpp"

SandTetrix::SandTetrix(std::shared_ptr<sf::RenderWindow> window)
    : window(window), z(std::vector<sf::Vector2i>(squares, sf::Vector2i(0, 0))),
      k(std::vector<sf::Vector2i>(squares, sf::Vector2i(0, 0))),
      isRunning(false), linesCleared(0), nextPieceIndex(0),
      currentPieceIndex(0),
      nextPieceColor(colors[std::rand() % colors.size()]) {

    if (!font.loadFromFile(filepathFont)) {
        throw std::runtime_error("Error loading font.");
    }
    setupGame();
}

void SandTetrix::setupGame() {
    board = make2Darray(rows, cols);
    for (auto &row : board) {
        std::fill(row.begin(), row.end(), 0);
    }

    dirX = 0;
    score = 0;
    rotate = false;
    gameover = false;
    timerCount = 0.f;
    dash = 0.3f;
    elapsedTime = 0.f;
    clock.restart();

    spawnPieces();
}

void SandTetrix::handleKeyboardEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            // Gira
            rotate = true;
            break;
        case sf::Keyboard::S: {
            // Dash
            dash = 0.05f;
            break;
        }
        case sf::Keyboard::A: {
            // Move para esquerda
            --dirX;
            break;
        }
        case sf::Keyboard::D: {
            // Move para direita
            ++dirX;
            break;
        }
        case sf::Keyboard::Space:
            // Pause
            isRunning = !isRunning;
            break;
        default:
            break;
        }
    }
}

void SandTetrix::draw() {
    drawBoard();
    drawPieces();
    drawPreview();
    drawText();
    if (gameover) {
        drawGameOver();
        isRunning = false;
    }
}

void SandTetrix::run() {
    float t = clock.getElapsedTime().asSeconds();
    clock.restart();
    timerCount += t;

    if (isRunning && !gameover) {
        elapsedTime += t;
        changePosition();
        setRotate();
        move2Down();
        setScore();
        resetValues();
    }
}
