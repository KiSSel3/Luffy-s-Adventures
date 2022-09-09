#ifndef APPLICATION_H
#define APPLICATION_H

#include "pausemenu.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Application {
public:
    Application(std::string filePath);
    ~Application();

    void startingGame();
    void createWindow();

private:
    sf::RenderWindow mainWindow;
    sf::View view;

    sf::Clock clock;

    Player* player;

    Enemy* enemy_1;
    Enemy* enemy_2;
    Enemy* enemy_3;
    Enemy* enemy_4;

    std::list<Enemy*> enemyList;
    std::list<Enemy*>::iterator it;

    TileMap map;

    float mainTime;

    float viewPosX;
    float viewPosY;
    bool  viewTied;

    std::string filePath;

    PauseMenu* pauseMenu;

    void viewSetting(float posX);
};
#endif // APPLICATION_H
