#include <string>
class Game
{
    public:
    Game(int width, int height, int fps, std::string title);
    ~Game() noexcept;
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    bool GameShouldClose() const;
    void Tick();

    private:
    void Update();
    void Draw();

};