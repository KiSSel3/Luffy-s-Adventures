#include "application.h"

#include <QDebug>
#include <iostream>

Application::Application(std::string filePath) {
    filePath.erase(filePath.find("Testing.exe", 0));
    std::replace(filePath.begin(), filePath.end(),'\\','/');

    mainWindow.create(sf::VideoMode(11520,1080),"",sf::Style::Fullscreen);
    mainWindow.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(0,0,1920,1080));

    map.load(filePath + "images/Map/TestViewMap.tmx", filePath + "images/forMap/all_tiles.png");

    player = new Player(filePath, 0, 0, 240, 324, 0, 4, map, 64, -800, 100, 0.2);

    firstEnemy = new Enemy(filePath, 0, 0, 234, 372,/*192, 312,*/ 0, 4, map, 608, -400,100, 0.03,0.35, 400, 96 - 0.258064516 * 192, 0.258064516,0.258064516);
    secondEnemy = new Enemy(filePath, 0, 0, 234, 372, /*192, 312,*/ 0, 4, map, 832, -400,100, 0.1,0.35, 400, 448 - 0.258064516 * 192, 0.258064516,0.258064516);
    thirdEnemy = new Enemy(filePath , 0, 0, 234, 372, 0, 4, map, 1000,200,100, 0.1,0.35, 400, 448 - 0.258064516 * 192, 0.258064516, 0.258064516);

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

            if(mainEvent.type == sf::Event::KeyPressed){
                if(mainEvent.key.code == sf::Keyboard::E){
                    player->changeGunState();
                }
                if(mainEvent.key.code == sf::Keyboard::Escape){
                    mainWindow.close();
                }

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                static bool flag = false;

                if(flag = !flag) {
                    mainWindow.create(sf::VideoMode::getDesktopMode(),"");
                }
                else {
                    mainWindow.create(sf::VideoMode(11520,1080),"",sf::Style::Fullscreen);
                }
            }
        }

        viewSetting(player->getPosX());
        mainWindow.setView(view);

        mainWindow.clear();
        mainWindow.draw(map);
        player->update(mainWindow, mainTime);

        for (it = enemyList.begin(); it != enemyList.end();) {
            Enemy* object = *it;

            object->setPosPlayer(player->getPosX(),player->getPosY());
            object->update(mainWindow, mainTime);

            //cтрельба врагов
            if(object->getBullet() != nullptr && object->getBullet()->getRect().intersects(player->getRect())){
                player->healthChange(object->getBullet()->getDamage());
                object->getBullet()->changeIsLive();
            }

            if(!player->getIsLive()) {
                mainWindow.close();
            }

            //стрельба персонажа
            if(player->getBullet() != nullptr && player->getBullet()->getRect().intersects(object->getRect())){
                object->healthChange(player->getBullet()->getDamage());
                player->getBullet()->changeIsLive();
            }

            if (!object->getIsLive()){
                it = enemyList.erase(it);
                delete object;
            }
            else {
                ++it;
            }
        }

        mainWindow.display();
    }
}

void Application::viewSetting(float X) {
    static bool viewMoving = false;
    static float x = 960;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(x < 10560){
            x += 0.2 * mainTime;
            view.setCenter(x,540);
            viewMoving = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(x > 960){
            x += -0.2 * mainTime;
            view.setCenter(x,540);
            viewMoving = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        viewMoving = false;
    }

    if(!viewMoving){
        if(X < 960) X = 960;
        if(X > 10560) X = 10560;

        x = X;
        view.setCenter(X,540);
    }
}

