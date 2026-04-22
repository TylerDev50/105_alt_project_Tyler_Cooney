#include "JungleLevelOne.h"

JungleLevelOne::JungleLevelOne(sf::RenderWindow& window, Input& input,
    GameState& gameState, AudioManager& audio)
    : Scene(window, input, gameState, audio), m_alertText(m_font), m_bananaCountText(m_font)
{
    // -------------------------------------------------------
    // TILESET  (identical convention to LevelWithTiles)
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

    // Blank tile
    tile.setTextureRect({ {0, 0}, {-24, -24} });
    tile.setCollider(false);
    int b = tileSet.size();
    tileSet.push_back(tile);

    // -------------------------------------------------------
    // LEVEL MAP
    // -------------------------------------------------------
    sf::Vector2u mapDimensions{ 40, 8 };
    std::vector<int> tileMap = {
        b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
        b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
        b  , b  , b  , 21 , 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  , 21 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  , 21 , 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
        b  , b  , b  , 121, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , 121, 122, 123, b  , b  , b  , b  , 21 , 22 , 22 , 22 , 121, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
        21 , 22 , 22 , 121, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , 121, 122, 123, b  , b  , 121, 122, 121, 122, 122, 122, 121, 122, 122, 123, b  , b  , 21 , 22 , 22 , 22 , 22 , 22 , 22 , 23 ,
        121, 122, 122, 121, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , 121, 122, 123, b  , b  , 121, 122, 121, 122, 122, 122, 121, 122, 122, 123, b  , b  , 121, 122, 122, 122, 122, 122, 122, 123,
        121, 122, 122, 121, 122, 122, 123, b  , b  , b  , b  , b  , b  , b  , b  , 121, 122, 123, b  , b  , 121, 122, 121, 122, 122, 122, 121, 122, 122, 123, b  , b  , 121, 122, 122, 122, 122, 122, 122, 123,
        141, 142, 142, 141, 142, 142, 143, b  , b  , b  , b  , b  , b  , b  , b  , 141, 142, 143, b  , b  , 141, 142, 141, 142, 142, 142, 141, 142, 142, 143, b  , b  , 141, 142, 142, 142, 142, 142, 142, 143,
    };
    

    m_tilemap.loadTexture("gfx/tilemap.png");
    m_tilemap.setTileSet(tileSet);
    m_tilemap.setTileMap(tileMap, mapDimensions);
    m_tilemap.setPosition({ 0, 100 });
    m_tilemap.buildLevel();
    tileSet.clear();

    // -------------------------------------------------------
    // BACKGROUND
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

    
// BANANAS - above their platforms, accounting for the 100px tilemap offset
    std::vector<sf::Vector2f> bananaPositions = {
        {  3 * 72.f, 100.f + (1 * 72.f) },    // above left platform
        { 15 * 72.f, 100.f + (1 * 72.f) },    // above middle platform
        { 27 * 72.f, 100.f + (0 * 72.f) },    // above far right platform
    };
    for (auto& pos : bananaPositions)
    {
        Banana* ban = new Banana();
        ban->setup();
        ban->placeAt(pos);
        m_bananas.push_back(ban);
    }

    
    // MONKEYS - standing on the ground row (row 4 is ground top, so place at row 3)
    std::vector<std::pair<sf::Vector2f, std::string>> monkeyData = {
        { {  0 * 72.f,  316.f }, "You! Find my\nbanana or ELSE!" },
        { { 13 * 72.f,  316.f }, "My banana is\nup there somewhere!" },
        { { 25 * 72.f,  244.f }, "Don't come back\nwithout it, Dino!" },
	};
    for (auto& [pos, line] : monkeyData)
    {
        Monkey* monk = new Monkey();
        monk->setup(pos);
        monk->setDialogue(line);
        m_monkeys.push_back(monk);
    }
}

void JungleLevelOne::handleInput(float dt)
{
    m_player.handleInput(dt);
    if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
        m_gameState.setCurrentState(State::MENU);
}

void JungleLevelOne::update(float dt)
{
    m_player.update(dt);

    // Tile collision
    for (auto& t : *m_tilemap.getLevel())
        if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
            m_player.collisionResponse(t);

    // Update and collect bananas
    checkBananaCollisions(dt);

    // Update monkeys + show dialogue
    checkMonkeyDialogue();

    // Prompt timer countdown
    if (m_promptTimer > 0) m_promptTimer -= dt;
    else if (!m_levelComplete) m_alertText.setString("");

    // Win condition
    if (m_bananasCollected >= BANANAS_NEEDED && !m_levelComplete)
    {
        m_levelComplete = true;
        m_alertText.setString("The monkeys are\npleased! Press F\nto escape!");
        m_alertText.setPosition(
            m_window.getView().getCenter() + sf::Vector2f(-120.f, -150.f));
        m_promptTimer = 999.f;
    }
    if (m_levelComplete && m_input.isPressed(sf::Keyboard::Scancode::F))
        m_gameState.setCurrentState(State::MENU);

    // Death
    if (m_player.getPosition().y > 1200)
    {
        m_player.reset();
        m_audio.playSoundbyName("death");
    }

    // Banana HUD anchored to view
    m_bananaCountText.setPosition(
        m_window.getView().getCenter() + sf::Vector2f(-210.f, -210.f));

    updateCameraAndBackground();
}

void JungleLevelOne::checkBananaCollisions(float dt)
{
    for (auto& banana : m_bananas)
    {
        if (banana->isCollected()) continue;
        banana->update(dt);   // now uses real dt
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

void JungleLevelOne::checkMonkeyDialogue()
{
    bool nearMonkey = false;
    for (auto& monkey : m_monkeys)
    {
        monkey->update(0.016f);
        if (monkey->playerInRange(m_player.getPosition()))
        {
            nearMonkey = true;
            if (!m_levelComplete)
            {
                m_alertText.setString(monkey->getDialogue());
                m_alertText.setCharacterSize(20);
                m_alertText.setPosition(
                    m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
                m_promptTimer = 0.1f;  // keep refreshing while in range
            }
        }
    }
}

void JungleLevelOne::updateCameraAndBackground()
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

void JungleLevelOne::render()
{
    beginDraw();
    m_bgtilemap.render(m_window);
    m_tilemap.render(m_window);
    for (auto& banana : m_bananas)
        if (!banana->isCollected()) m_window.draw(*banana);
    for (auto& monkey : m_monkeys)
        m_window.draw(*monkey);
    m_window.draw(m_player);
    m_window.draw(m_alertText);
    m_window.draw(m_bananaCountText);
    endDraw();
}

void JungleLevelOne::onBegin()
{
    std::cout << "Jungle level one started\n";
    m_audio.playMusicbyName("bgm1");
    m_player.reset();
    m_player.setPosition({ 72.f, 50.f });

    m_alertText.setString("The monkeys have\nkidnapped you!\nFind their bananas!");
    m_alertText.setPosition({ 50, 150 });
    m_alertText.setCharacterSize(24);
    m_alertText.setFillColor(sf::Color::Black);
    m_promptTimer = PROMPT_TIME;
}

void JungleLevelOne::onEnd()
{
    std::cout << "Jungle level one ended\n";
    m_player.reset();
    m_bananasCollected = 0;
    m_levelComplete = false;
    m_bananaCountText.setString("Bananas: 0 / 3");
    for (auto& ban : m_bananas) ban->reset();
    m_audio.stopAllSounds();
    m_audio.stopAllMusic();
}