#include "GameMode.h"

GameMode::GameMode(Game *game, string levelName) : Screen(game)
{
    initializeLevel(levelName);
    updateSurvival = false;
    bonus = false;
    limit = 60;
    delay = 2;
    speed = 5;
    life = totalLives;
    row = 0;
    column = 0;
    miliSeconds = 0;
    seconds = 0;
    currentAnimationFrame = 0;
    gameWidth = GetScreenWidth() - widthDiff;
    gameHeight = GetScreenHeight() - heightDiff;
    isPaused = false;
    loadTextures();
}

GameMode::~GameMode()
{
}

void GameMode::unloadTextures()
{
    UnloadTexture(levelBG);
    UnloadTexture(emptyHeart);
    UnloadTexture(fullHeart);
    UnloadTexture(hole);
    UnloadTexture(keyTexture);
    UnloadTexture(menu);
}

void GameMode::loadTextures()
{
    levelBG = LoadTexture("./resources/levelsBG.png");
    emptyHeart = LoadTexture("./resources/lifeNull.png");
    fullHeart = LoadTexture("./resources/life.png");
    hole = LoadTexture("./resources/hole.png");
    keyTexture = LoadTexture("./resources/key.png");
    menu = LoadTexture("./resources/menu.png");
    
    for(int i = 0; i < totalNoOfMoles; i++)
    {
        string textureToLoad = "./resources/moles/mole" + to_string(i + 1) + ".png";
        Texture2D loadedTexture = LoadTexture(textureToLoad.c_str());
        moles.push_back(loadedTexture);
        moles.at(i).width = holeWidth;
        moles.at(i).height = holeHeight;
    }

    main.setTexture(LoadTexture("./resources/main.png"));
    restart.setTexture(LoadTexture("./resources/restart.png"));
    Continue.setTexture(LoadTexture("./resources/continue.png"));
    float widthSub = 150, 
        heightSub = 70;
    for(int i = 1; i <= 3; i++)
    {
        Vector2 position = { float(GetScreenWidth() / 2 - (buttonWidth - widthSub) / 2), float((GetScreenHeight() / 5 * i) + ((buttonHeight - 40) / 5)) },
                Size     = { buttonWidth - widthSub, buttonHeight - heightSub };
        if(i == 1)
        {
            restart.setPosition(position);
            restart.setSize(Size);
        }
        else if(i == 2)
        {
            Continue.setPosition(position);
            Continue.setSize(Size);
        }
        else
        {
            main.setPosition(position);
            main.setSize(Size);
        }

    }
    
    hole.width = holeWidth;
    hole.height = holeHeight;
    fullHeart.width = heartSize;
    fullHeart.height = heartSize;
    emptyHeart.width = heartSize;
    emptyHeart.height = heartSize;
    keyTexture.width = keySize;
    keyTexture.height = keySize;
    levelBG.width = GetScreenWidth();
    levelBG.height = GetScreenHeight();
    menu.width = GetScreenWidth();
    menu.height = GetScreenHeight();
}   

void GameMode::calcTime()
{
    if (seconds == delay && miliSeconds == 0)
    {
        getMoleToHit();
        currentLevel.at(row).at(column) = '1';
    }
    miliSeconds++;
    if (miliSeconds == limit)
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
            if(score % 7 == 0)
                updateSurvival = true;
            if(score % 10 == 0 && life < totalLives && life != 0)
                bonus = true;

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
    
    // if (life <= 0)
    // {
    //     Screen *s = new GameOver(gameState);
    //     gameState.changeScreen(s);
    // }
}

void GameMode::update()
{
    if (IsKeyPressed(KEY_SPACE))
        isPaused = !isPaused;
    if (life > 0)
    {
        if(isPaused)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 position = main.getPosition(),
                        size = main.getSize(),
                        mouse = GetMousePosition();

                if(mouse.x > position.x && mouse.x < position.x + size.x && mouse.y > position.y && mouse.y < position.y + size.y)
                {
                    // Screen * s = new MainMenuScreen(gameState);
                    // gameState -> changeScreen(s);
                }
            }
        }
        else
            calcTime();
        
    }
    checkLevelStatus();
}

void GameMode::checkLevelStatus()
{

}

void GameMode::draw()
{
    // -------------------------------------------------------------------------------------
    // ADDING BACKGROUND
    if(currentAnimationFrame < totalNoOfMoles - 2)
        currentAnimationFrame += 2;
    else
        currentAnimationFrame = totalNoOfMoles - 1;

    DrawTexture(levelBG, 0, 0, WHITE);
    // --------------------------------------------------------------------------------------
    // Draw Text
    string totalScore = "SCORE : " + to_string(score);
    DrawRectangle(GetScreenWidth() - 360, 17, 330, 50, BLACK);
    DrawText(totalScore.c_str(), GetScreenWidth() - 350, 20, 50, RAYWHITE);
    // --------------------------------------------------------------------------------------
    // Draw Hearts
    for (int i = 0; i < totalLives; i++)
    {
        Texture2D isFullHeart = fullHeart;
        if (i >= life)
            isFullHeart = emptyHeart;
        DrawTexture(isFullHeart, i * heartSize + 20, 20, WHITE);
    }

    // --------------------------------------------------------------------------------------
    // DRAW LEVEL
    int ySpace = heightDiff,
        tempHDiff = (holeWidth / 2) - (keySize / 2),
        tempWDiff;
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

            DrawTexture(hole, tempWDiff, ySpace, WHITE);

            if (currentLevel.at(i).at(j) == '1')
                DrawTexture(moles[currentAnimationFrame], tempWDiff, ySpace, WHITE);
            
            DrawTexture(keyTexture, tempWDiff + tempHDiff, ySpace + holeHeight, WHITE);
            string keyToPress(1, char(key.at(i).at(j)));
            DrawText(keyToPress.c_str(), tempWDiff + tempHDiff + 13, ySpace + holeHeight + 5, keySize - 15, BLACK);

        }
    }
    if (isPaused)
    {
        DrawTexture(menu, 0, 0, WHITE);
        main.draw();
        restart.draw();
        Continue.draw();
    }
}

void GameMode::initializeLevel(string levelToRead)
{
    score = 0;
    life = totalLives;
    currentLevel = readLvl(levelToRead);
    setKeys();
}

vector<vector<char>> GameMode::readLvl(string levelName)
{
    ifstream level("src/include/levels/" + levelName + ".txt");
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

bool GameMode::checkKeyPress(int keyPress)
{
    if (keyPress != 0 && keyPress != 32)
        return true;
    else
        return false;
}

void GameMode::getMoleToHit()
{
    row = 1 + rand() % (currentLevel.size());
    row--;
    column = 1 + rand() % (currentLevel.at(row).size());
    column--;
    currentAnimationFrame = 0;
}

void GameMode::setKeys()
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
