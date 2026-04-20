#pragma once
#include <iostream>
#include <string>
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Monkey : public GameObject
{
public:
    Monkey() = default;

    void setup(sf::Vector2f pos)
    {
        if (!m_monkeyTexture.loadFromFile("gfx/Monke_SpriteSheet.png"))
            std::cerr << "Could not load monkey sprite\n";

        setTexture(&m_monkeyTexture);
        setSize({ 72, 72 });
        GameObject::setPosition(pos);

        // Sheet is 600x270 — two frames each 300x270
        m_idle.addFrame({ {0,   0}, {300, 270} });
        m_idle.addFrame({ {300, 0}, {300, 270} });
        m_idle.setFrameSpeed(1.f / 2.f);

        setTextureRect(m_idle.getCurrentFrame());
    }

    void update(float dt)
    {
        m_idle.animate(dt);
        setTextureRect(m_idle.getCurrentFrame());
    }

    void setDialogue(const std::string& text) { m_dialogue = text; }
    std::string getDialogue() const { return m_dialogue; }

    bool playerInRange(sf::Vector2f playerPos) const
    {
        sf::Vector2f diff = playerPos - getPosition();
        return (diff.x * diff.x + diff.y * diff.y) < TRIGGER_RANGE_SQ;
    }

private:
    sf::Texture  m_monkeyTexture;
    Animation    m_idle;
    std::string  m_dialogue;
    const float  TRIGGER_RANGE_SQ = 150.f * 150.f;
};

