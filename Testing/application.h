#ifndef APPLICATION_H
#define APPLICATION_H

#include "player.h"
#include "enemy.h"
#include "map.h"
#include "Entity.h"
#include "Coin.h"
#include "Fruit.h"
#include "Platform.h"
#include "Spike.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <sstream>

class Application {
public:
    Application(std::string filePath);
    ~Application();

    void startingGame();
    void createWindow();

private:
    sf::RenderWindow mainWindow;
    sf::View view;
    sf::Font font;
    sf::Text* textCoin;
    sf::Text* textHealth;

    sf::Texture textureHealth;
    sf::Sprite  spriteHealth;

    sf::Clock clock;

    Player* player;

    std::list<Enemy*> enemyList;
    std::list<Enemy*>::iterator itEnemy;

    std::list<Entity*> coinList;
    std::list<Entity*>::iterator itCoin;

    std::list<Entity*> fruitList;
    std::list<Entity*>::iterator itFruit;

    std::list<Entity*> spikeList;
    std::list<Entity*>::iterator itSpike;

    TileMap map;

    float mainTime;

    float viewPosX;
    float viewPosY;
    bool  viewTied;

    std::string filePath;

    Coin* statisticCoin;

    sf::SoundBuffer coinBuffer;
    sf::Sound coinSound;

    sf::Music music;

    void viewSetting(float posX);
    void playerStatisticView();

    void createEnemyList();
    void createCoinList();
    void createFruitList();
    void createSpikeList();
};
#endif // APPLICATION_H
