#pragma once

#include "FallingSand/falling_sand.hpp"
#include "Menu/menu.hpp"
#include "SandTetrix/sand_tetrix.hpp"

class Render {
  protected:
    const int WIDTH = 1080;
    const int HEIGHT = 720;

  private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::VideoMode> desktop;

    std::shared_ptr<Menu> menu;
    std::shared_ptr<FallingSand> fallingSand;
    std::shared_ptr<SandTetrix> sandTetrix;

    sf::Vector2i mousePosition;

    bool useShader;

  private:
    int opc;
    
    sf::Clock clock;
    sf::Shader shader;
    sf::RenderTexture renderTex;

    void setupShader();

    void handleEvents();
    void handleMouse();
    void resetGameState();

    void drawPointer();
    void draw();

  public:
    Render();
    void run();
};
