#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

inline std::vector<std::vector<int>> make2Darray(int rows, int cols) {
    return std::vector<std::vector<int>>(cols, std::vector<int>(rows, 0));
}

inline sf::Color HSV2RGB(float h, float s, float v) {
    int i = static_cast<int>(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0:
        return sf::Color(v * 255, t * 255, p * 255);
    case 1:
        return sf::Color(q * 255, v * 255, p * 255);
    case 2:
        return sf::Color(p * 255, v * 255, t * 255);
    case 3:
        return sf::Color(p * 255, q * 255, v * 255);
    case 4:
        return sf::Color(t * 255, p * 255, v * 255);
    case 5:
        return sf::Color(v * 255, p * 255, q * 255);
    default:
        return sf::Color(0, 0, 0);
    }
}

inline sf::Color getColorByValue(int value) {
    float hue = static_cast<float>(value) / 255.0f * 360.0f;
    float saturation = 0.8f;
    float brightness = 0.8f;
    return HSV2RGB(hue / 360.0f, saturation, brightness);
}
