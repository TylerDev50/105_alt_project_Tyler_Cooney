#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Banana.h"
#include "Monkey.h"
#include <algorithm>

class JungleLevelOne : public Scene
{
public:
    JungleLevelOne(sf::RenderWindow& window, Input& input,
        GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt)      override;
    void render()              override;
    void onBegin()             override;
    void onEnd()               override;

private:
    void updateCameraAndBackground();
    void checkBananaCollisions(float dt);
    void checkMonkeyDialogue();

    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player  m_player;

    sf::Texture m_tileTexture;
    sf::Font    m_font;
    sf::Text    m_alertText;
    sf::Text    m_bananaCountText;

    std::vector<Banana*> m_bananas;
    std::vector<Monkey*> m_monkeys;

    int m_bananasCollected = 0;
    const int BANANAS_NEEDED = 3;

    bool  m_levelComplete = false;
    float m_promptTimer = 0.f;
    const float PROMPT_TIME = 2.f;

    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432,  432 };
};

