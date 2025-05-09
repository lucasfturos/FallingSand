#include "menu.hpp"
#include "Common/RoundedRectangle.hpp"

Menu::Menu(int width, int height) : selectedOption(0) {
    if (!font.loadFromFile(filepathFont)) {
        throw std::runtime_error("Failed to load font.");
    }

    title.setFont(font);
    option1.setFont(font);
    option2.setFont(font);
    option3.setFont(font);

    layoutOption(width, height);
}

void Menu::resize(int width, int height) { layoutOption(width, height); }

void Menu::layoutOption(int w, int h) {
    float scale = w / 1080.0f;
    int tSize = static_cast<int>(50 * scale);
    int oSize = static_cast<int>(30 * scale);

    float oHeight = oSize * 1.2f;
    float space = oHeight * 1.5f;

    setupText(title, "Sand Experience", tSize, {w / 2.0f, h / 5.0f - 20});

    float vOffset = 50.f;
    setupText(option1, "Falling Sand", oSize,
              {w / 2.0f, h / 2.0f - space + vOffset});
    setupText(option2, "SandTetrix", oSize, {w / 2.0f, h / 2.0f + vOffset});
    setupText(option3, "Quit", oSize, {w / 2.0f, h / 2.0f + space + vOffset});
}

void Menu::setupText(sf::Text &text, const std::string &str, int size,
                     sf::Vector2f pos) {
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getLocalBounds().width / 2.0f,
                   text.getLocalBounds().height / 2.0f);
    text.setPosition(pos);
}

void Menu::borderOption(sf::RenderWindow &window) {
    float width = window.getSize().x * 0.5f;
    float height = window.getSize().y * 0.35f;

    RoundedRectangle border;
    border.setSize({width, height});
    border.setRadius(5.f);
    border.setOrigin(border.getSize() / 2.f);
    border.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 50);
    border.setFillColor(sf::Color(0, 0, 0, 150));
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(3.f);

    window.draw(border);
}

void Menu::highlightOption(sf::RenderWindow &window, sf::Text &option,
                           int optionIndex) {
    if (optionIndex == selectedOption) {
        sf::FloatRect bounds = option.getGlobalBounds();

        float width = window.getSize().x * 0.45f;
        float height = bounds.height + 20.f;

        RoundedRectangle background;

        background.setSize({width, height});
        background.setRadius(5.f);
        background.setOrigin(background.getSize() / 2.f);
        background.setPosition(window.getSize().x / 2.f,
                               option.getPosition().y);
        background.setFillColor(sf::Color(50, 50, 50, 200));
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(2.f);

        option.setScale(1.1f, 1.1f);
        option.setFillColor(sf::Color::White);

        window.draw(background);
    } else {
        option.setScale(1.f, 1.f);
        option.setFillColor(sf::Color::White);
    }

    window.draw(option);
}

void Menu::draw(sf::RenderWindow &window) {
    window.clear();
    window.draw(title);

    borderOption(window);

    highlightOption(window, option1, 0);
    highlightOption(window, option2, 1);
    highlightOption(window, option3, 2);

    window.display();
}
