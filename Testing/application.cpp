#include "application.h"

#include <QDebug>
#include <iostream>

Application::Application(std::string filePath) {
    filePath.erase(filePath.find("Testing.exe", 0));
    std::replace(filePath.begin(), filePath.end(),'\\','/');

    mainWindow.create(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);

    map.load(filePath + "images/Map/Map.tmx", filePath + "images/forMap/160.png");

    player = Player(filePath + "images/sprites/Luffy.png", 0, 0, 240, 324, 0, 4, map, 40, -200);

    firstEnemy = Enemy(filePath + "images/sprites/Enemy(temporarily).png", 0, 0, 192, 312, 0, map, 1920-500,10,100,0.1);
}

Application::~Application() {
    mainWindow.close();
}

void Application::start() {
    while(mainWindow.isOpen()){
        sf::Event mainEvent;

        mainTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        mainTime = mainTime/800;

        while(mainWindow.pollEvent(mainEvent)) {
            if(mainEvent.type == sf::Event::Closed) {
                mainWindow.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                mainWindow.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                static bool flag = false;

                if(flag = !flag) {
                    mainWindow.create(sf::VideoMode::getDesktopMode(),"");
                }
                else {
                    mainWindow.create(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);
                }
            }
        }

        player.dTimeSet(mainTime);
        player.update(mainWindow);

        //firstEnemy.dTimeSet(mainTime);
        //firstEnemy.setPosPlayer(player.getPosX(),player.getPosY());
        //firstEnemy.update(mainWindow);

        mainWindow.clear();
        mainWindow.draw(map);
        //mainWindow.draw(firstEnemy);
        mainWindow.draw(player);
        mainWindow.display();
    }
}

