#ifndef APPLICATION_H
#define APPLICATION_H

#include "player.h"
#include "enemy.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Application {
public:
    Application(std::string filePath);
    ~Application();

    void start();

private:
    std::shared_ptr<sf::RenderWindow> mainWindow;
    sf::Clock clock;

    Player player;
    Enemy firstEnemy;

    float mainTime;
};
#endif // APPLICATION_H
