#include <string>
#include <raylib.h>
#include <vector>
using std::string;
using std::vector;
class Game
{
    public:
    Game(int width, int height, int fps, string title);
    ~Game() noexcept;
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    bool gameShouldClose() const;
    void tick();
    void readLvl(string levelName);
    void renderLevel();
    void calcTime();
    inline void generateKey();


    private:
    vector<vector<char> > currentLevel;
    int frames = 0, seconds = 0, key = 0, delay = 2, interval = 0, score = 0;
    Color holes = { 230, 41, 55, 255 };
    void Update();
    void Draw();

};