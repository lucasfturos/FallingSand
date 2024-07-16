#pragma once

#include "../Common/common.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>

class SandTetrix {
  protected:
    const int cols = 20;
    const int rows = 20;
    const int shapes = 7;
    const int squares = 4;
    const int cellSize = 36;

    const std::string filepathFont =
        "assets/font/press-start-2p/PressStart2P-Regular.ttf";

    const std::vector<sf::Color> colors = {
        sf::Color::Green, sf::Color::Blue,    sf::Color::Red, sf::Color::Yellow,
        sf::Color::White, sf::Color::Magenta, sf::Color::Cyan};

    const std::vector<std::vector<int>> forms = {
        {1, 3, 5, 7}, // I
        {2, 4, 5, 7}, // Z
        {3, 5, 4, 6}, // S
        {3, 5, 4, 7}, // T
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4, 5}, // O
    };

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<sf::Vector2i> z;
    std::vector<sf::Vector2i> k;
    bool isRunning;
    int linesCleared;
    int nextPieceIndex;
    int currentPieceIndex;
    sf::Color currentPieceColor;

    sf::Font font;
    sf::Clock clock;
    sf::Color nextPieceColor;

    int dirX;
    int score;
    bool rotate;
    bool gameover;
    float dash;
    float timerCount;
    float elapsedTime;
    std::vector<std::vector<int>> board;

    void changePosition();
    bool checkCollision();
    void move2Down();
    void resetValues();
    void setRotate();
    void setScore();
    void spawnPieces();

    std::string formatTime(float seconds);
    void drawTextParams(sf::Vector2f, sf::Color, const std::string &, int);

    void drawBoard();
    void drawGameOver();
    void drawPieces();
    void drawPreview();
    void drawText();

  public:
    SandTetrix(std::shared_ptr<sf::RenderWindow>);
    void setupGame();
    void handleKeyboardEvent(const sf::Event &);
    void draw();
    void run();
};