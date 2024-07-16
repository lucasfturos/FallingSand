#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

class SandTetrix {
  protected:
    const int shapes = 7;
    const int squares = 4;
    const int cellSize = 36;
    const int sandGrainSize = 5;

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
    int cols;
    int rows;
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
    void sandMovement();
    void setRotate();
    void setScore();
    void spawnPieces();

    void drawCenteredText(sf::Vector2f, sf::Color, const std::string &, int);
    void drawTextAtPosition(sf::Vector2f, sf::Color, const std::string &, int);

    void drawBoard();
    void drawFlashingPieces();
    void drawGameOver();
    void drawGameStart();
    void drawGameStats();
    void drawPieces();
    void drawPreview();
    void drawSandBlock(sf::Vector2f, sf::Color);
    void drawSandGrain(sf::Vector2f, sf::Color);

  public:
    SandTetrix(std::shared_ptr<sf::RenderWindow>);

    void setupGame();
    void handleEvents(const sf::Event &);
    void draw();
    void run();
};