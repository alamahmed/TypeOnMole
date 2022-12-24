#include "game.h"

Game::Game(int width, int height, int fps, string title)
{
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    currentLevel = readLvl("level1.txt");
    unlockedLevels = readLvl("unlockedLevels.txt");

    initalizeVariables(width, height);
    currentState = mainMenuScreen;
    loadTextures();
}

Game::~Game() noexcept
{
    UnloadTexture(mole);
    UnloadTexture(hole);
    UnloadTexture(fullHeart);
    UnloadTexture(emptyHeart);
    UnloadTexture(levelBG);
    UnloadTexture(keyTexture);
    UnloadTexture(menu);
    UnloadTexture(menuBG);
    UnloadTexture(lockedLevel);
    UnloadTexture(mainMenu);
    UnloadTexture(levelButton);
    UnloadTexture(survivalButton);
    UnloadTexture(gameOver);
    UnloadFont(font);
    for (int i = 0; i < totalNoOfLevels; i++)
    {
        UnloadTexture(levelsTexture.at(i));
    }
    CloseWindow();
}

void Game::initalizeVariables(int width, int height)
{
    srand(time(0));
    score = 0;
    life = totalLives;
    row = 0;
    column = 0;
    miliSeconds = 0;
    seconds = 0;
    delay = 2;
    speed = 2;
    gameWidth = width - widthDiff;
    gameHeight = height - heightDiff;
    isPaused = false;

    buttonWidthDiff = (GetScreenWidth() - buttonWidth) - 50;
    levelTextureHeightDiff = (GetScreenHeight() / ((totalNoOfLevels / 5) + 1));
    levelTextureWidthDiff = (GetScreenWidth() / ((totalNoOfLevels / (totalNoOfLevels / 5)) + 1));
}

void Game::loadTextures()
{
    font = LoadFont("./resources/fonts/ARTHO-PersonalUse.otf");
    mole = LoadTexture("./resources/mole.png");
    hole = LoadTexture("./resources/hole.png");
    fullHeart = LoadTexture("./resources/life.png");
    emptyHeart = LoadTexture("./resources/lifeNull.png");
    levelBG = LoadTexture("./resources/levelsBG.png");
    keyTexture = LoadTexture("./resources/key.png");
    menu = LoadTexture("./resources/menu.png");
    menuBG = LoadTexture("./resources/menuBG.png");
    lockedLevel = LoadTexture("./resources/lockLevel.png");
    mainMenu = LoadTexture("./resources/mainMenu.png");
    survivalButton = LoadTexture("./resources/survival.png");
    levelButton = LoadTexture("./resources/level.png");
    gameOver = LoadTexture("./resources/gameOver.png");
    for (int i = 0; i < totalNoOfLevels; i++)
    {
        string textureToLoad = "./resources/" + to_string(i + 1) + ".png";
        levelsTexture.push_back(LoadTexture(textureToLoad.c_str()));
        levelsTexture.at(i).width = levelIconSize;
        levelsTexture.at(i).height = levelIconSize;
    }

    lockedLevel.width = levelIconSize;
    lockedLevel.height = levelIconSize;
    mole.width = holeWidth;
    mole.height = holeHeight;
    hole.width = holeWidth;
    hole.height = holeHeight;
    fullHeart.width = heartSize;
    fullHeart.height = heartSize;
    emptyHeart.width = heartSize;
    emptyHeart.height = heartSize;
    levelBG.width = GetScreenWidth();
    levelBG.height = GetScreenHeight();
    keyTexture.width = keySize;
    keyTexture.height = keySize;
    survivalButton.width = buttonWidth;
    survivalButton.height = buttonHeight;
    levelButton.width = buttonWidth;
    levelButton.height = buttonHeight;
    menu.width = GetScreenWidth();
    menu.height = GetScreenHeight();
    menuBG.width = GetScreenWidth();
    menuBG.height = GetScreenHeight();
    mainMenu.width = GetScreenWidth();
    mainMenu.height = GetScreenHeight();
    gameOver.width = GetScreenWidth();
    gameOver.height = GetScreenHeight();
}

bool Game::gameShouldClose() const
{
    return WindowShouldClose();
}

void Game::tick()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Update();
    Draw();
    checkGameState();
    if (life <= 0)
        currentState = endGame;

    EndDrawing();
}

void Game::Draw()
{
    switch (currentState)
    {
    case mainMenuScreen:
        renderMainMenu();
        break;

    case Survival:
        renderLevel();
        break;

    case levelScreen:
        renderLevelMenu();
        break;

    case levels:
        renderLevel();
        break;

    case endGame:
        DrawTexture(gameOver, 0, 0, WHITE);
        string totalScore = to_string(score);
        Vector2 textSize = MeasureTextEx(font, totalScore.c_str(), fontSize, 0);
        DrawText(totalScore.c_str(), (GetScreenWidth() / 2) - (textSize.x / 4), (GetScreenHeight() / 2) - textSize.y * 2, fontSize, BLACK);
        break;
    }
}

void Game::calcTime()
{
    if (seconds == delay && miliSeconds == 0)
    {
        getMoleToHit();
        currentLevel.at(row).at(column) = '1';
    }
    miliSeconds++;
    if (miliSeconds == 60)
    {
        seconds++;
        miliSeconds = 0;
    }

    if (seconds >= delay && seconds <= delay + speed)
    {
        int keyPress = GetKeyPressed();
        if (checkKeyPress(keyPress) && keyPress == key.at(row).at(column))
        {
            score++;
            currentLevel.at(row).at(column) = '0';
            seconds = 0;
        }
        else if ((checkKeyPress(keyPress) && keyPress != key.at(row).at(column)) || seconds >= delay + speed)
        {
            life--;
            currentLevel.at(row).at(column) = '0';
            seconds = 0;
        }
    }
    else
        currentLevel.at(row).at(column) = '0';
}

bool Game::checkKeyPress(int keyPress)
{
    if (keyPress != 0 && keyPress != 32)
        return true;
    else
        return false;
}

void Game::Update()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        switch (currentState)
        {
        case mainMenuScreen:
            currentState = mainMenuScreen;
            break;

        case Survival:
            isPaused = true;
            break;

        case levelScreen:
            currentState = mainMenuScreen;
            break;

        case levels:
            isPaused = true;
            break;

        case endGame:
            life = totalLives;
            currentState = mainMenuScreen;
            break;
        }
    }
}

void Game::checkGameState()
{
    if (IsKeyPressed(KEY_SPACE))
        isPaused = !isPaused;
    if (life > 0)
    {
        if (currentState == levels || currentState == Survival)
        {
            if (isPaused)
                DrawTexture(menu, 0, 0, WHITE);
            else
                calcTime();
        }
    }
}

vector<vector<char>> Game::readLvl(string levelName)
{
    ifstream level("src/include/levels/" + levelName);
    vector<vector<char>> lvl;
    string line;
    if (!level)
        cout << "Failed to read file " << levelName << "\n";
    while (getline(level, line))
    {
        vector<char> temp;

        copy(line.begin(), line.end(), back_inserter(temp));

        lvl.push_back(temp);
    }
    return lvl;
}

void Game::initializeLevel(string levelToRead)
{
    score = 0;
    life = totalLives;
    currentLevel = readLvl(levelToRead);
    setKeys();
}

void Game::getMoleToHit()
{
    row = 1 + rand() % (currentLevel.size());
    row--;
    column = 1 + rand() % (currentLevel.at(row).size());
    column--;
}

void Game::renderMainMenu()
{
    DrawTexture(mainMenu, 0, 0, WHITE);

    DrawTexture(survivalButton, buttonWidthDiff, 1 * buttonHeight, WHITE);
    DrawTexture(levelButton, buttonWidthDiff, 2 * buttonHeight, WHITE);
    for (int i = 1; i <= 2; i++)
    {

        int tempX = GetMousePosition().x, tempY = GetMousePosition().y;
        if (tempX >= buttonWidthDiff && tempX <= buttonWidthDiff + buttonWidth && tempY >= i * buttonHeight && tempY <= (i + 1) * buttonHeight)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 1)
                {
                    initializeLevel("level0.txt");
                    currentState = Survival;
                }
                else
                    currentState = levelScreen;
            }
        }
    }
}

void Game::renderLevel()
{
    // -------------------------------------------------------------------------------------
    // ADDING BACKGROUND
    DrawTexture(levelBG, 0, 0, WHITE);
    // --------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------
    // Draw Text
    string totalScore = "SCORE : " + to_string(score);
    DrawRectangle(GetScreenWidth() - 360, 17, 330, 50, BLACK);
    DrawText(totalScore.c_str(), GetScreenWidth() - 350, 20, 50, RAYWHITE);

    // --------------------------------------------------------------------------------------
    // Draw Hearts
    for (int i = 0; i < totalLives; i++)
    {
        if (i < life)
            DrawTexture(fullHeart, i * heartSize + 20, 20, WHITE);
        else
            DrawTexture(emptyHeart, i * heartSize + 20, 20, WHITE);
    }

    // --------------------------------------------------------------------------------------
    // DRAW LEVEL
    int ySpace = heightDiff, tempHDiff = (holeWidth / 2) - (keySize / 2), tempWDiff;
    for (int i = 0; i < currentLevel.size(); i++)
    {
        ySpace += (gameHeight / (currentLevel.size() + 1));
        if (i == 0)
            ySpace -= holeHeight / 2;
        int xSpace = gameWidth / (currentLevel.at(i).size() + 1);
        tempWDiff = widthDiff;
        for (int j = 0; j < currentLevel.at(i).size(); j++)
        {
            if (j < 1)
                tempWDiff += xSpace - holeWidth / 2;
            else
                tempWDiff += xSpace;

            if (currentLevel.at(i).at(j) == '1')
                DrawTexture(mole, tempWDiff, ySpace, WHITE);
            else if (currentLevel.at(i).at(j) == '0')
                DrawTexture(hole, tempWDiff, ySpace, WHITE);
            DrawTexture(keyTexture, tempWDiff + tempHDiff, ySpace + holeHeight, WHITE);
            string keyToPress(1, char(key.at(i).at(j)));
            DrawText(keyToPress.c_str(), tempWDiff + tempHDiff + 13, ySpace + holeHeight + 5, keySize - 15, BLACK);
        }
    }
}

void Game::renderLevelMenu()
{
    DrawTexture(menuBG, 0, 0, WHITE);
    int count = 0;
    for (int i = 0; i < (totalNoOfLevels / 5); i++)
    {
        for (int j = 0; j < totalNoOfLevels / (totalNoOfLevels / 5); j++)
        {
            int x = j * levelTextureWidthDiff + levelIconSize,
                y = i * levelTextureHeightDiff + levelIconSize;

            int tempX = GetMousePosition().x, tempY = GetMousePosition().y;

            if (count < unlockedLevels.size())
            {
                DrawTexture(levelsTexture.at(count), x, y, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if ((tempX >= x && tempX <= x + levelIconSize) && (tempY >= y && tempY <= y + levelIconSize))
                    {
                        string levelToRead = "level" + to_string(count + 1) + ".txt";
                        initializeLevel(levelToRead.c_str());
                        currentState = levels;
                    }
                }
            }
            else
                DrawTexture(lockedLevel, x, y, WHITE);
            count++;
        }
    }
}

void Game::setKeys()
{
    set<int> keysAdded;
    for (int i = 0; i < currentLevel.size(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < currentLevel.at(i).size(); j++)
        {
            int tempKey = 0;
            do
            {
                tempKey = 65 + rand() % (90 - 66);
            } while (keysAdded.contains(tempKey));
            keysAdded.insert(tempKey);
            temp.push_back(tempKey);
            currentLevel.at(i).at(j) = '0';
        }
        key.push_back(temp);
    }
}
