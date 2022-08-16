#include "application.h"

Application::Application(std::string filePath) : filePath(filePath) {
    mainWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);

    this->filePath.erase(this->filePath.find("Player\\build", 0));
    std::replace(this->filePath.begin(),this->filePath.end(),'\\','/');
}

Application::~Application() {
    mainWindow->close();
}

void Application::start() {
    Player player(filePath + "images/sprites/Luffy.png", 0,0,240,324,0,0,0,100,0.3);

    while(mainWindow->isOpen()){
        sf::Event mainEvent;

        mainTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        mainTime = mainTime/800;

        player.dTimeSet(mainTime);

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

        player.update();

        mainWindow->clear();
        mainWindow->draw(player);
        mainWindow->display();

    }
}

