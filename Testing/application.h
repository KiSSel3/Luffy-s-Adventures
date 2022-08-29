#ifndef APPLICATION_H
#define APPLICATION_H

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

    void start();

private:
    sf::RenderWindow mainWindow;
    sf::View view;
    sf::Clock clock;
    Player* player;

    Enemy* firstEnemy;
    Enemy* secondEnemy;
    Enemy* thirdEnemy;

    std::list<Enemy*> enemyList;
    std::list<Enemy*>::iterator it;

    TileMap map;

    float mainTime;

    float viewPosX;
    float viewPosY;

    bool viewTied;

    void viewSetting(float posX); // настройка вида
};
#endif // APPLICATION_H
