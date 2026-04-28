#pragma once
#include <iostream>
#include "Framework/GameObject.h"

class Rubble : public GameObject
{
public:
    Rubble() = default;

    void setup(sf::Vector2f pos, sf::Texture* tex)
    {
        setSize({ 72, 72 });
        setCollisionBox({ {0, 0}, {72, 72} });
        GameObject::setPosition(pos);

        if (tex)
        {
            setTexture(tex);
            setTextureRect({ {133, 38}, {18, 18} });
            setFillColor(sf::Color::White);  // MUST be white or tint blocks texture
        }
        else
        {
            // Fallback if texture fails
            setFillColor(sf::Color(139, 69, 19));
        }
    }

    bool isDestroyed() const { return m_destroyed; }
    void destroy() { m_destroyed = true; }
    void reset() { m_destroyed = false; }

private:
    bool m_destroyed = false;
};

