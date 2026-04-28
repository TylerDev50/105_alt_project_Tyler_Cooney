#include "JungleLevelTwo.h"

JungleLevelTwo::JungleLevelTwo(sf::RenderWindow& window, Input& input,
    GameState& gameState, AudioManager& audio)
    : Scene(window, input, gameState, audio), m_alertText(m_font), m_bananaCountText(m_font)
{
    // -------------------------------------------------------
    // TILESET - identical setup to JungleLevelOne
    // -------------------------------------------------------
    GameObject tile;
    std::vector<GameObject> tileSet;

    int num_columns = 20;
    int num_rows = 9;
    int tile_size = 18;
    int sheet_spacing = 1;

    tile.setSize(sf::Vector2f(tile_size * 4, tile_size * 4));
    tile.setCollisionBox({ {0, 0}, tile.getSize() });

    for (int i = 0; i < num_columns * num_rows; i++)
    {
        int row = i / num_columns;
        int col = i % num_columns;
        tile.setTextureRect({
            {(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
            {tile_size, tile_size}
            });
        if (col <= 4 || col >= 12) tile.setCollider(true);
        else                        tile.setCollider(false);
        tileSet.push_back(tile);
    }

    tile.setTextureRect({ {0, 0}, {-24, -24} });
    tile.setCollider(false);
    int b = tileSet.size();
    tileSet.push_back(tile);

	//Level design 
    sf::Vector2u mapDimensions{ 40, 7 };
    std::vector<int> tileMap = {
        21 , 22 , 22 , 22 , 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , 21 , 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
        141, 142, 142, 142, 142, 142, 143, b  , 21 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , 141, 142, 142, 123, b  , 21 , 22 , 22 , 22 , 22 , 22 , 22 , 23 , b  ,
        b  , b  , b  , b  , b  , b  , b  , b  , 121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , 123, b  , 141, 142, 142, 142, 142, 142, 142, 123, b  ,
        21 , 22 , 22 , 22 , 22 , 22 , 22 , 22 , 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123, b  , b  , b  , b  , b  , 21 , 22 , 22 , 22 , 22 , 123, b  , b  , b  , b  , b  , b  , b  , b  , 123, b  ,
        121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123, b  , b  , b  , b  , b  , 121, 122, 122, 122, 122, 122, 22 , 22 , 22 , 22 , 22 ,  22,  22,  22, 123, b  ,
        121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123, b  , b  , b  , b  , b  , 121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 123, b  ,
        141, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, b  , b  , b  , b  , b  , 141, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, b  ,
    };

    m_tilemap.loadTexture("gfx/tilemap.png");
    m_tilemap.setTileSet(tileSet);
    m_tilemap.setTileMap(tileMap, mapDimensions);
    m_tilemap.setPosition({ 0, 100 });
    m_tilemap.buildLevel();
    tileSet.clear();

    // -------------------------------------------------------
    // BACKGROUND - same as level 1
    // -------------------------------------------------------
    tile_size = 24;
    num_columns = 8;
    num_rows = 3;
    tile.setSize(sf::Vector2f(tile_size * 9, tile_size * 9));

    for (int i = 0; i < num_columns * num_rows; i++)
    {
        int row = i / num_columns;
        int col = i % num_columns;
        tile.setTextureRect({
            {(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
            {tile_size, tile_size}
            });
        tile.setCollider(false);
        tileSet.push_back(tile);
    }
    mapDimensions = { 14, 3 };
    std::vector<int> bgMap = {
        6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 ,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
    };
    m_bgtilemap.loadTexture("gfx/tilemap-backgrounds.png");
    m_bgtilemap.setTileSet(tileSet);
    m_bgtilemap.setTileMap(bgMap, mapDimensions);
    m_bgtilemap.setPosition({ 0, 0 });
    m_bgtilemap.buildLevel();

    // -------------------------------------------------------
    // PLAYER
    // -------------------------------------------------------
    m_player.setInput(&m_input);
    m_player.setEdges(0, WORLD_SIZE.x);
    m_player.setCanDoubleJump(true);
    m_player.setAudio(&m_audio);

    // -------------------------------------------------------
    // FONT + UI
    // -------------------------------------------------------
    if (!m_font.openFromFile("font/bitcount.ttf"))
        std::cerr << "no font found\n";

    m_alertText.setCharacterSize(24);
    m_alertText.setFillColor(sf::Color::Black);

    m_bananaCountText.setCharacterSize(20);
    m_bananaCountText.setFillColor(sf::Color::Yellow);
    m_bananaCountText.setString("Bananas: 0 / 3");

    if (!m_tileTexture.loadFromFile("gfx/tilemap.png"))
        std::cerr << "no tile texture\n";

    // -------------------------------------------------------
    // BANANAS
    // -------------------------------------------------------
    std::vector<sf::Vector2f> bananaPositions = {
        {  1 * 72.f, 100.f + (2 * 72.f) },   // top of left climb
        { 28 * 72.f, 100.f + (2 * 72.f) },   // top of middle-right climb
        { 35 * 72.f, 100.f + (3 * 72.f) },   // top of far right climb
    };
    for (auto& pos : bananaPositions)
    {
        Banana* ban = new Banana();
        ban->setup();
        ban->placeAt(pos);
        m_bananas.push_back(ban);
    }

    // -------------------------------------------------------
    // RUBBLE
    // -------------------------------------------------------
    std::vector<sf::Vector2f> rubblePositions = {
        {  3 * 72.f, 3.4 * 72.f },    // right in front of spawn - easy to see
        { 26  * 72.f, 3.4 * 72.f },
        { 31 * 72.f, 5.4 * 72.f },
    };

    for (auto& pos : rubblePositions)
    {
        Rubble* r = new Rubble();
        r->setup(pos, &m_tileTexture);
        m_rubble.push_back(r);
    }

    // -------------------------------------------------------
    // MONKEYS - one per section, each near their banana
    // -------------------------------------------------------
    std::vector<std::pair<sf::Vector2f, std::string>> monkeyData = {
        { {  9 * 72.f, 1.5 * 72.f}, "SMASH the rocks!\nDASH through them!" },
        { { 18 * 72.f, 1.5 * 72.f }, "My banana is Stuck!\nIn that Wall Over the gap!" },
        { { 27 * 72.f, .4 * 72.f }, "Better Get my Banana,\n " },
    };

    for (auto& [pos, line] : monkeyData)
    {
        Monkey* monk = new Monkey();
        monk->setup(pos);
        monk->setDialogue(line);
        m_monkeys.push_back(monk);
    }
}

// -------------------------------------------------------
// INPUT
// -------------------------------------------------------
void JungleLevelTwo::handleInput(float dt)
{
    m_player.handleInput(dt);
    if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
        m_gameState.setCurrentState(State::MENU);
}

// -------------------------------------------------------
// UPDATE
// -------------------------------------------------------
void JungleLevelTwo::update(float dt)
{
    m_player.update(dt);

    // Tile collisions
    for (auto& t : *m_tilemap.getLevel())
        if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
            m_player.collisionResponse(t);

    // Rubble - must come before banana so dash-through works this frame
    checkRubbleCollisions();

    // Bananas
    checkBananaCollisions(dt);

    // Monkey dialogue
    checkMonkeyDialogue(dt);

    // Prompt timer
    if (m_promptTimer > 0) m_promptTimer -= dt;
    else if (!m_levelComplete) m_alertText.setString("");

    // Win condition
    if (m_bananasCollected >= BANANAS_NEEDED && !m_levelComplete)
    {
        m_levelComplete = true;
        m_alertText.setString("All bananas found!\nThe monkeys cheer!\nPress F to finish!");
        m_alertText.setPosition(
            m_window.getView().getCenter() + sf::Vector2f(-120.f, -150.f));
        m_promptTimer = 999.f;
    }
    if (m_levelComplete && m_input.isPressed(sf::Keyboard::Scancode::F))
        m_gameState.setCurrentState(State::MENU);

    // Death reset
    if (m_player.getPosition().y > 1200)
    {
        m_player.reset();
        m_audio.playSoundbyName("death");
    }

    // HUD anchor to view
    m_bananaCountText.setPosition(
        m_window.getView().getCenter() + sf::Vector2f(-210.f, -210.f));

    updateCameraAndBackground();
}

void JungleLevelTwo::checkRubbleCollisions()
{
    for (auto& rubble : m_rubble)
    {
        if (rubble->isDestroyed()) continue;

        if (Collision::checkBoundingBox(m_player, *rubble))
        {
            if (m_player.isDashing())
            {
                rubble->destroy();
                m_audio.playSoundbyName("coin");  
            }
            else
            {
                m_player.collisionResponse(*rubble);
            }
        }
    }
}

void JungleLevelTwo::checkBananaCollisions(float dt)
{
    for (auto& banana : m_bananas)
    {
        if (banana->isCollected()) continue;
        banana->update(dt);
        if (Collision::checkBoundingBox(m_player, *banana))
        {
            banana->collect();
            m_bananasCollected++;
            m_bananaCountText.setString(
                "Bananas: " + std::to_string(m_bananasCollected) + " / 3");
            m_audio.playSoundbyName("coin");
        }
    }
}

void JungleLevelTwo::checkMonkeyDialogue(float dt)
{
    for (auto& monkey : m_monkeys)
    {
        monkey->update(dt);
        if (monkey->playerInRange(m_player.getPosition()) && !m_levelComplete)
        {
            m_alertText.setString(monkey->getDialogue());
            m_alertText.setCharacterSize(20);
            m_alertText.setPosition(
                m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
            m_promptTimer = 0.1f;
        }
    }
}

// -------------------------------------------------------
// CAMERA - identical to level 1
// -------------------------------------------------------
void JungleLevelTwo::updateCameraAndBackground()
{
    auto view = m_window.getView();
    auto player_pos = m_player.getPosition() + m_player.getSize() * 0.5f;

    float halfW = VIEW_SIZE.x / 2.f;
    float halfH = VIEW_SIZE.y / 2.f;
    player_pos.x = std::clamp(player_pos.x, halfW, (float)WORLD_SIZE.x - halfW);
    player_pos.y = std::clamp(player_pos.y, halfH, (float)WORLD_SIZE.y - halfH);

    view.setCenter(player_pos);
    m_window.setView(view);
    m_bgtilemap.setPosition({ player_pos.x - halfW, 0 });
}

// -------------------------------------------------------
// RENDER
// -------------------------------------------------------
void JungleLevelTwo::render()
{
    beginDraw();
    m_bgtilemap.render(m_window);
    m_tilemap.render(m_window);
    for (auto& rubble : m_rubble)
        if (!rubble->isDestroyed()) m_window.draw(*rubble);
    for (auto& banana : m_bananas)
        if (!banana->isCollected()) m_window.draw(*banana);
    for (auto& monkey : m_monkeys)
        m_window.draw(*monkey);
    m_window.draw(m_player);
    m_window.draw(m_alertText);
    m_window.draw(m_bananaCountText);
    endDraw();

    // TEMP DEBUG - remove later
    for (auto& rubble : m_rubble)
    {
        std::cout << "Rubble at: " << rubble->getPosition().x
            << "/" << rubble->getPosition().y
            << " destroyed: " << rubble->isDestroyed() << "\n";
    }
}

// -------------------------------------------------------
// LIFECYCLE
// -------------------------------------------------------
void JungleLevelTwo::onBegin()
{
    std::cout << "Jungle level two started\n";
    m_audio.playMusicbyName("bgm1");
    m_player.reset();
    m_player.setPosition({ 72.f, 50.f });

    m_alertText.setString("Deeper in the jungle!\nSmash rubble to\nfind the bananas!");
    m_alertText.setPosition({ 50, 150 });
    m_alertText.setCharacterSize(24);
    m_alertText.setFillColor(sf::Color::Black);
    m_promptTimer = PROMPT_TIME;
}

void JungleLevelTwo::onEnd()
{
    std::cout << "Jungle level two ended\n";
    m_player.reset();
    m_bananasCollected = 0;
    m_levelComplete = false;
    m_bananaCountText.setString("Bananas: 0 / 3");
    for (auto& ban : m_bananas) ban->reset();
    for (auto& r : m_rubble)
    {
        for (auto& r : m_rubble) r->reset();
    }
    m_audio.stopAllSounds();
    m_audio.stopAllMusic();
}