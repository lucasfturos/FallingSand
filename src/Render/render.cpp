#include "render.hpp"

Render::Render()
    : window(std::make_shared<sf::RenderWindow>(
          sf::VideoMode(WIDTH, HEIGHT), "Sand Experience",
          sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize)),
      desktop(std::make_shared<sf::VideoMode>(sf::VideoMode::getDesktopMode())),
      useShader(false) {
    window->setPosition(
        sf::Vector2i(desktop->width / 2.0 - window->getSize().x / 2.0,
                     desktop->height / 2.0 - window->getSize().y / 2.0));

    sf::Vector2i screenPos(window->getSize().x, window->getSize().y);

    menu = std::make_shared<Menu>(screenPos.x, screenPos.y);
    fallingSand = std::make_shared<FallingSand>(screenPos.x, screenPos.y);
    sandTetrix = std::make_shared<SandTetrix>(screenPos.x, screenPos.y);

    mousePosition = sf::Vector2i(screenPos.x / 2, screenPos.y / 2);

    setupShader();
}

void Render::setupShader() {
    if (!shader.loadFromFile("assets/shader/crt_effect.frag",
                             sf::Shader::Fragment)) {
        throw std::runtime_error("Failed to load shader.");
    }
    renderTex.create(WIDTH, HEIGHT);

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("resolution", sf::Vector2f(renderTex.getSize()));
}

void Render::drawPointer() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(static_cast<sf::Vector2f>(mousePosition));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        renderTex.draw(circle);
    }
}

void Render::draw() {
    window->clear();
    if (opc == 0) {
        menu->draw(*window);
    } else {
        renderTex.clear();
        if (opc == 1) {
            fallingSand->draw(renderTex);
            drawPointer();
        } else if (opc == 2) {
            sandTetrix->draw(renderTex);
            sandTetrix->run();
        }
        renderTex.display();

        sf::Sprite sprite(renderTex.getTexture());
        if (useShader) {
            window->draw(sprite, &shader);
        } else {
            window->draw(sprite);
        }
    }
    window->display();
}

void Render::run() {
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        handleEvents();
        handleMouse();
        shader.setUniform("time", clock.getElapsedTime().asSeconds());
        draw();
    }
}