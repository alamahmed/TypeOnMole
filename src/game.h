#include <string>
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
    bool GameShouldClose() const;
    void Tick();
    void readLvl(string levelName);
    void renderLevel();

    private:
    vector<vector<char> > currentLevel;
    void Update();
    void Draw();

};