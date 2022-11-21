#include "application.h"

#include <QDebug>
#include <iostream>

Application::Application(std::string FilePath): filePath(FilePath) {
    mainWindow.create(sf::VideoMode(11520,1080),"",sf::Style::Fullscreen);
    mainWindow.setVerticalSyncEnabled(true);

    map.load(filePath + "images/Map.tmx", filePath + "images/TileMap.png");


    Object playerObject = map.getObject("begin");
    player  = new Player(filePath, 0, 0, 240, 324, 0, 4, map, playerObject.rect.left,-100 /*playerObject.rect.top*/, 100, 0.2);

    view.reset(sf::FloatRect(0,0,1920,1080));
    viewTied = true;
    viewPosX = 960;
    viewPosY = 540;

    statisticCoin = new Coin(filePath, 0, 0, 32,32, viewPosX - 950, 74,2,2);

    createCoinList();
    createFruitList();
    createSpikeList();
    createEnemyList();

    font.loadFromFile(filePath + "images/Font.ttf");
    textCoin = new sf::Text("", font, 50);
    textCoin->setColor(sf::Color::Black);
    textCoin->setStyle(sf::Text::Bold);

    textHealth = new sf::Text("", font, 50);
    textHealth->setColor(sf::Color::Black);
    textHealth->setStyle(sf::Text::Bold);

    textureHealth.loadFromFile(filePath + "images/Sprites/Health.png");
    spriteHealth.setTexture(textureHealth);
    spriteHealth.setTextureRect(sf::IntRect(100, 109, 595, 502));
    spriteHealth.setScale(0.107563025,0.12749004);

    coinBuffer.loadFromFile(FilePath + "sound/Coin.ogg");
    coinSound.setBuffer(coinBuffer);

    music.openFromFile(filePath + "sound/Music.ogg");
    music.setLoop(true);
}

Application::~Application() {
    mainWindow.close();

    delete player;

    enemyList.clear();
}

void Application::startingGame() {
    music.play();

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
        }

        viewSetting(player->getPosX());
        mainWindow.setView(view);

        mainWindow.clear();
        mainWindow.draw(map);

        player->update(mainWindow, mainTime);

        for(itSpike = spikeList.begin(); itSpike != spikeList.end();) {
            Entity* object = *itSpike;

            object->update(mainWindow, mainTime);

            if(player->getRect().intersects(object->getRect())) {
                player->healthChange(5);
            }

            ++itSpike;
        }

        for(itCoin = coinList.begin(); itCoin != coinList.end();) {
            Entity* object = *itCoin;

            object->update(mainWindow, mainTime);

            if(player->getRect().intersects(object->getRect())) {
                itCoin = coinList.erase(itCoin);
                delete object;

                player->changeCountCoin();
                coinSound.play();
            }
            else {
                ++itCoin;
            }
        }

        for(itFruit = fruitList.begin(); itFruit != fruitList.end();) {
            Entity* object = *itFruit;

            object->update(mainWindow, mainTime);

            if(player->getRect().intersects(object->getRect())) {
                itFruit = fruitList.erase(itFruit);
                delete object;

                player->healthChange(-100);
            }
            else {
                ++itFruit;
            }
        }

        for (itEnemy = enemyList.begin(); itEnemy != enemyList.end();) {
            Enemy* object = *itEnemy;

            object->setPosPlayer(player->getPosX(),player->getPosY());
            object->update(mainWindow, mainTime);

            //cтрельба врагов
            if(object->getBullet() != nullptr && object->getBullet()->getRect().intersects(player->getRect())){
                player->healthChange(object->getBullet()->getDamage());
                object->getBullet()->changeIsLive();
            }

            //стрельба персонажа
            if(player->getBullet() != nullptr && player->getBullet()->getRect().intersects(object->getRect())){
                object->healthChange(player->getBullet()->getDamage());
                player->getBullet()->changeIsLive();
            }

            if (!object->getIsLive()){
                itEnemy = enemyList.erase(itEnemy);
                delete object;
            }
            else {
                ++itEnemy;
            }
        }

        if(!player->getIsLive()) {
            mainWindow.close();
        }

        playerStatisticView();
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

void Application::playerStatisticView() {
    statisticCoin->update(mainWindow, mainTime);
    statisticCoin->setPosX(viewPosX - 950);

    std::ostringstream countCoin;
    countCoin << player->getCountCoin();

    textCoin->setString(countCoin.str());
    textCoin->setPosition(statisticCoin->getPosX() + 70, statisticCoin->getPosY());
    mainWindow.draw(*textCoin);

    spriteHealth.setPosition(viewPosX - 950,5);
    mainWindow.draw(spriteHealth);

    std::ostringstream health;
    health << player->getHealth();

    textHealth->setString(health.str());
    textHealth->setPosition(spriteHealth.getPosition().x + 70, spriteHealth.getPosition().y);
    mainWindow.draw(*textHealth);

}

void Application::createEnemyList() {
    std::vector<Object> objectEnemy = map.getObjectsByName("enemy");

    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[0].rect.left, -200, 100, 0.10, 0.35, 400, 1000  - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[1].rect.left, -200, 100, 0.02, 0.35, 400, 96    - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[2].rect.left, -200, 100, 0.02, 0.35, 400, 96    - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[3].rect.left, -200, 100, 0.02, 0.35, 400, 128   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[4].rect.left, -200, 100, 0.02, 0.35, 400, 1000   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[5].rect.left, -200, 100, 0.02, 0.35, 400, 64   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[6].rect.left, -200, 100, 0.02, 0.35, 400, 64   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[7].rect.left, -200, 100, 0.02, 0.35, 400, 1000   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[8].rect.left, -200, 100, 0.02, 0.35, 400, 32   - 0.258064516 * 234, 0.258064516, 0.258064516));
    enemyList.push_back(new Enemy (filePath, 0, 0, 234, 372, 0, 4, map,objectEnemy[9].rect.left, -200, 100, 0.02, 0.35, 400, 128   - 0.258064516 * 234, 0.258064516, 0.258064516));

}

void Application::createCoinList() {
    std::vector<Object> objectCoin = map.getObjectsByName("coin");

    for(auto& coin : objectCoin){
        coinList.push_back(new Coin(filePath, 0, 0, 32,32, coin.rect.left, coin.rect.top));
    }

    objectCoin.clear();
}

void Application::createFruitList() {
    std::vector<Object> objectFruit = map.getObjectsByName("fruit");

    for(auto& fruit : objectFruit){
        fruitList.push_back(new Fruit(filePath, 1, 381, 78,95, fruit.rect.left, fruit.rect.top, 0.41025641,0.336842105));
    }

    objectFruit.clear();
}

void Application::createSpikeList() {
    std::vector<Object> objectSpike = map.getObjectsByName("spike");

    for(auto& spike : objectSpike) {
        spikeList.push_back(new Spike(filePath,0, 95,128, 32, spike.rect.left, spike.rect.top,1,1));
    }

    objectSpike.clear();
}
