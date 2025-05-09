#pragma once

// Credits: https://gist.github.com/Wesxdz/e8667fb20ce5864f758d39685d6547ce

#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangle : public sf::Shape {
  private:
    size_t cornerPointCount = 2;
    float anglePerPoint;
    float radius = 1.0f;
    sf::Vector2f size;

  public:
    virtual sf::Vector2f getPoint(size_t index) const override {
        if (cornerPointCount == 1 || radius == 0.0f) {
            sf::RectangleShape rect(size);
            return rect.getPoint(index);
        } else {
            size_t corner = index / cornerPointCount;
            float angle = 0;
            bool isLastPointOnCorner =
                (index % cornerPointCount == cornerPointCount - 1);
            if (isLastPointOnCorner) {
                angle = 90.0f;
            } else {
                angle = (index % cornerPointCount) * anglePerPoint;
            }
            sf::Vector2f point;
            switch (corner) {
            case 0:
                point = {radius, radius};
                angle -= 180;
                break;
            case 1:
                point = {size.x - radius, radius};
                angle -= 90;
                break;
            case 2:
                point = {size.x - radius, size.y - radius};
                break;
            default:
                point = {radius, size.y - radius};
                angle += 90;
            }
            point += {std::cos(angle * M_PIf / 180.0f) * radius,
                      std::sin(angle * M_PIf / 180.0f) * radius};
            return point;
        }
    }

    void setSize(sf::Vector2f size) {
        this->size = size;
        update();
    }

    void setRadius(float radius) {
        if (radius > 0.0f) {
            this->radius = radius;
            update();
        }
    }

    void setCornerPointCount(int points) {
        if (points < 1) {
            points = 1;
        }

        cornerPointCount = points;
        anglePerPoint = 90.0f / cornerPointCount;
        update();
    }

    virtual size_t getPointCount() const override {
        return cornerPointCount * 4;
    }

    float getRadius() const { return radius; }
    const sf::Vector2f &getSize() const { return size; }
    int getCornerPointCount() { return cornerPointCount; }
};