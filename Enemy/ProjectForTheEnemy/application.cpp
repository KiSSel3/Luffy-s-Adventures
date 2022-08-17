#include "application.h"

Application::Application(std::string filePath) : filePath(filePath) {
    mainWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);

    this->filePath.erase(this->filePath.find("Enemy\\Project", 0));
    std::replace(this->filePath.begin(),this->filePath.end(),'\\','/');
}

Application::~Application() {
    mainWindow->close();
}

void Application::start() {
    Enemy enemy(filePath + "images/sprites/Enemy(temporarily).png", 0,0,192,312,0,10,10,100,0.1);

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

                if(flag = !flag)
                  mainWindow->create(sf::VideoMode::getDesktopMode(),"");

                else
                  mainWindow->create(sf::VideoMode(1520,860),"",sf::Style::Fullscreen);

              }
        }

        enemy.dTimeSet(mainTime);
        enemy.setPosPlayer(5500,5500);
        enemy.update();

        mainWindow->clear();
        mainWindow->draw(enemy);
        mainWindow->display();
    }
}

