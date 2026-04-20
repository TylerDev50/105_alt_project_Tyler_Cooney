#pragma once
#include <iostream>
#include <cmath>
#include "Framework/GameObject.h"

class Banana : public GameObject
{
public:
    Banana() = default;

    void setup()
    {
        if (!m_bananaTexture.loadFromFile("gfx/Bannana_Sprite.png"))
            std::cerr << "Could not load banana sprite\n";

        setTexture(&m_bananaTexture);
        setTextureRect({ {0, 0}, {300, 270} });
        setSize({ 72, 72 });
        setCollisionBox({ {10, 10}, {52, 52} });
    }

    void update(float dt)
    {
        if (m_collected) return;
        m_bobTimer += dt;
        float offset = std::sin(m_bobTimer * 3.0f) * 4.0f;
        GameObject::setPosition({ m_baseX, m_baseY + offset });
    }

    void placeAt(sf::Vector2f pos)
    {
        m_baseX = pos.x;
        m_baseY = pos.y;
        GameObject::setPosition(pos);
    }

    bool isCollected() const { return m_collected; }

    void collect()
    {
        m_collected = true;
    }

    void reset()
    {
        m_collected = false;
        m_bobTimer = 0.f;
        GameObject::setPosition({ m_baseX, m_baseY });
    }

private:
    sf::Texture  m_bananaTexture;
    float        m_baseX = 0.f;
    float        m_baseY = 0.f;
    float        m_bobTimer = 0.f;
    bool         m_collected = false;
}; 