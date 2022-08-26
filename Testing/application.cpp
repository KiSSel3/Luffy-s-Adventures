#include "application.h"

#include <QDebug>
#include <iostream>

Application::Application(std::string filePath) {
    filePath.erase(filePath.find("Testing.exe", 0));
    std::replace(filePath.begin(), filePath.end(),'\\','/');

    mainWindow.create(sf::VideoMode(1920,1080),"",sf::Style::Fullscreen);

    map.load(filePath + "images/Map/Map.tmx", filePath + "images/forMap/all_tiles.png");

    player = new Player(filePath, 0, 0, 240, 324, 0, 4, map, 64, -800, 100, 0.2);

    firstEnemy = new Enemy(filePath, 0, 0, 234, 372,/*192, 312,*/ 0, 4, map, 608, -400,100, 0.03,0.35, 400, 96 - 0.258064516 * 192, 0.258064516,0.258064516);
    secondEnemy = new Enemy(filePath, 0, 0, 234, 372, /*192, 312,*/ 0, 4, map, 832, -400,100, 0.1,0.35, 400, 448 - 0.258064516 * 192, 0.258064516,0.258064516);
    thirdEnemy = new Enemy(filePath , 0, 0, 234, 372, 0, 4, map, 832,200,100, 0.1,0.35, 400, 448 - 0.258064516 * 192, 0.258064516, 0.258064516);

    enemyList.push_back(firstEnemy);
    enemyList.push_back(secondEnemy);
    enemyList.push_back(thirdEnemy);
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

        player->dTimeSet(mainTime);
        player->update();

        for (auto* object : enemyList) {
            object->dTimeSet(mainTime);
            object->setPosPlayer(player->getPosX(),player->getPosY());
            object->update();

            if(object->getBullet() != nullptr) {
                object->getBullet()->dTimeSet(mainTime);
                object->getBullet()->update();
            }
        }

        mainWindow.clear();
        mainWindow.draw(map);

        for (auto* object : enemyList) {
            mainWindow.draw(*object);
            if(object->getBullet() != nullptr) {
                mainWindow.draw(*(object->getBullet()));
            }
        }

        if(player->getBullet() != nullptr) {
            player->getBullet()->dTimeSet(mainTime);
            player->getBullet()->update();
            mainWindow.draw(*(player->getBullet()));
        }

        mainWindow.draw(*player);
        mainWindow.display();
    }
}

