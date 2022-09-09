#include "application.h"

#include <QDebug>
#include <iostream>

Application::Application(std::string FilePath): filePath(FilePath) {
    mainWindow.create(sf::VideoMode(11520,1080),"",sf::Style::Fullscreen);
    mainWindow.setVerticalSyncEnabled(true);

    map.load(filePath + "images/Map/TestViewMap.tmx", filePath + "images/forMap/all_tiles.png");

    Object Enemy_1 = map.getObject("Enemy_1");
    Object Enemy_2 = map.getObject("Enemy_2");
    Object Enemy_3 = map.getObject("Enemy_3");
    Object Enemy_4 = map.getObject("Enemy_4");

    player  = new Player(filePath, 0, 0, 240, 324, 0, 4, map, 64, -800, 100, 0.2);
    enemy_1 = new Enemy (filePath, 0, 0, 234, 372, 0, 4, map, Enemy_1.rect.left, Enemy_1.rect.top, 100, 0.10, 0.35, 400, 1344  - 0.258064516 * 234, 0.258064516, 0.258064516);
    enemy_2 = new Enemy (filePath, 0, 0, 234, 372, 0, 4, map, Enemy_2.rect.left, Enemy_2.rect.top, 100, 0.05, 0.35, 400, 224   - 0.258064516 * 234, 0.258064516, 0.258064516);
    enemy_3 = new Enemy (filePath, 0, 0, 234, 372, 0, 4, map, Enemy_3.rect.left, Enemy_3.rect.top, 100, 0.02, 0.35, 400, 96    - 0.258064516 * 234, 0.258064516, 0.258064516);
    enemy_4 = new Enemy (filePath, 0, 0, 234, 372, 0, 4, map, Enemy_4.rect.left, Enemy_4.rect.top, 100, 0.20, 0.35, 400, 11100 - 0.258064516 * 234, 0.258064516, 0.258064516);

    enemyList.push_back(enemy_1);
    enemyList.push_back(enemy_2);
    enemyList.push_back(enemy_3);
    enemyList.push_back(enemy_4);

    view.reset(sf::FloatRect(0,0,1920,1080));
    viewTied = true;
    viewPosX = 960;
    viewPosY = 540;

    pauseMenu = new PauseMenu(filePath);
}

Application::~Application() {
    mainWindow.close();

    delete pauseMenu;
    delete player;

    enemyList.clear();
}

void Application::startingGame() {
    while(mainWindow.isOpen()){
        sf::Event mainEvent;

        mainTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        mainTime = mainTime/800;

        if(pauseMenu->isVisible()) { //временное(но это не точно AXAXAXAX) решение паузы и выхода
            if(pauseMenu->stopGame()) {
                mainWindow.close();
            }
            mainTime = 0;
        }

        while(mainWindow.pollEvent(mainEvent)) {
            if(mainEvent.type == sf::Event::Closed) {
                mainWindow.close();
            }

            if(mainEvent.type == sf::Event::KeyPressed){
                if(mainEvent.key.code == sf::Keyboard::E){
                    player->changeGunState();
                }
                if(mainEvent.key.code == sf::Keyboard::Escape){
                    pauseMenu->showFullScreen();
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
                //mainWindow.close();
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

void Application::viewSetting(float playerPosX) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
        if(viewPosX < 10560){
            viewPosX += 0.3 * mainTime;
        }

        viewTied = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        if(viewPosX > 960){
            viewPosX += -0.3 * mainTime;
        }

        viewTied = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
        viewTied = true;
    }

    if(viewTied) {
        viewPosX = playerPosX;

        if(viewPosX < 960) {
            viewPosX = 960;
        }
        else if(viewPosX > 10560) {
            viewPosX = 10560;
        }
    }

    view.setCenter(viewPosX, viewPosY);
}
