#include "sand_tetrix.hpp"
#include "Common/common.hpp"

SandTetrix::SandTetrix(int screenWidth, int screenHeight)
    : z(std::vector<sf::Vector2i>(squares, sf::Vector2i(0, 0))),
      k(std::vector<sf::Vector2i>(squares, sf::Vector2i(0, 0))),
      isRunning(false), cols((screenWidth * 0.65f) / cellSize),
      rows(screenHeight / cellSize), linesCleared(0), nextPieceIndex(0),
      currentPieceIndex(0),
      nextPieceColor(colors[std::rand() % colors.size()]) {

    if (!font.loadFromFile(filepathFont)) {
        throw std::runtime_error("Error loading font.");
    }

    setupGame();
}

void SandTetrix::setupGame() {
    board = make2Darray<int>(rows, cols);
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

void SandTetrix::resize(int width, int height) {
    int newCols = (width * 0.65f) / cellSize;
    int newRows = height / cellSize;

    auto newBoard = make2Darray<int>(newRows, newCols);
    for (int y = 0; y < std::min(rows, newRows); ++y) {
        for (int x = 0; x < std::min(cols, newCols); ++x) {
            newBoard[x][y] = board[x][y];
        }
    }

    cols = newCols;
    rows = newRows;
    board = std::move(newBoard);
}

void SandTetrix::draw(sf::RenderTarget &target) {
    drawBoard(target);
    drawPieces(target);
    drawPreview(target);
    drawGameStats(target);
    if (gameover) {
        drawGameOver(target);
        isRunning = false;
    }
    if (!isRunning && !gameover) {
        drawGameStart(target);
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
        sandMovement();
        resetValues();
    }
}
