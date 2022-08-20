#include "application.h"

Application::Application(std::string filePath) {
    filePath.erase(filePath.find("Player\\ProjectFor", 0));
    std::replace(filePath.begin(), filePath.end(),'\\','/');

    mainWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);
    player = Player(filePath + "images/sprites/Luffy.png", 0,0,240,324,0);
    firstEnemy = Enemy(filePath + "images/sprites/Enemy(temporarily).png", 0,0,192,312,0,1920-500,10,100,0.1);
}

Application::~Application() {
    mainWindow->close();
}

void Application::start() {
    while(mainWindow->isOpen()){
        sf::Event mainEvent;

        mainTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        mainTime = mainTime/800;

        while(mainWindow->pollEvent(mainEvent)) {
            if(mainEvent.type == sf::Event::Closed) {
                mainWindow->close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                mainWindow->close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                static bool flag = false;

                if(flag = !flag) {
                    mainWindow->create(sf::VideoMode::getDesktopMode(),"");
                }
                else {
                    mainWindow->create(sf::VideoMode(1520,860),"",sf::Style::Fullscreen);
                }
            }
        }

        player.dTimeSet(mainTime);
        player.update();

        firstEnemy.dTimeSet(mainTime);
        firstEnemy.setPosPlayer(player.getPosX(),player.getPosY());
        firstEnemy.update();

        mainWindow->clear();
        mainWindow->draw(firstEnemy);
        mainWindow->draw(player);
        mainWindow->display();

    }
}

