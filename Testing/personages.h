#ifndef PERSONAGES_H
#define PERSONAGES_H

#include "Bullet.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Personages {
public:
    virtual ~Personages() { };

    void speedChange(float speedX);                                   // изменение скорости объекта
    bool getIsLive();                                                 // получение состояния

    sf::FloatRect getRect();                                          // получение размеров спрайта
    Bullet* getBullet();                                              // возвращает пулю объекта

    virtual void healthChange(int damage)                       = 0;  // изменение здоровья объекта
    virtual void update(sf::RenderWindow& window, float dTime)  = 0;  // корректировка координат объекта относительно карты

protected:
    Bullet* bullet;                                                   // класс пули

    bool isLive;                                                      // cостояние объекта

    std::string filePath;                                             // путь в папку с ~~~.exe

    sf::Texture texture;                                              // текстура объекта
    sf::Sprite  sprite;                                               // спрайт с объектом

    int xInTexture;                                                   // начальная координата Х спрайта в текстуре
    int yInTexture;                                                   // начальная координата Y спрайта в текстуре
    int width;                                                        // ширина спрайта
    int height;                                                       // высота спрайта
    float scaleX;                                                     // масштабирование спрайта по X
    float scaleY;                                                     // масштабирование спрайта по Y
    int distanceBetweenTiles;                                         // расстояние между тайлами

    float posX;                                                       // координата Х спрайта относительно карты
    float posY;                                                       // координата Y спрайта относительно карты

    float health;                                                     // здоровьте объекта

    float speedX;                                                     // cкорость объекта по Х
    float speedY;                                                     // cкорость объекта по Y
    float currentSpeedX;                                              // текущая cкорость объекта по Х
    float currentSpeedY;                                              // текущая cкорость объекта по Y

    float dTime;                                                      // пройденное время между итерациями основного цикла

    int countFrames;                                                  // количество кадров объекта в тайлсете
    float motionFrame;                                                // номер тайла в тайлсете

    std::vector<Object> objectsOnMap;                                 // все объекты на карте(для коллизии)

    sf::SoundBuffer shootBuffer;                                      // буфер со звуком стрельбы
    sf::Sound shootSound;                                             // звук стрельбы

    virtual void collisionX()                  = 0;                   // функция для решения коллизиипо X
    virtual void collisionY()                  = 0;                   // функция для решения коллизиипо Y
    virtual void shoot()                       = 0;                   // стрельба
    virtual void recharge(sf::RenderWindow& window, float dTime) = 0; // логика перезарядки оружия

    void motionFrameChange();                                         // изменение тайла в тайлсете
};

#endif // PERSONAGES_H
