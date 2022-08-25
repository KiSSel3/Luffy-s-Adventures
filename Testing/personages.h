#ifndef PERSONAGES_H
#define PERSONAGES_H

#include "map.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Personages : public sf::Drawable {
public:
    virtual ~Personages() { };
    void dTimeSet(float dTime);                         // инициализация поля dTime
    void speedChange(float speedX);                     // изменение скорости объекта
    sf::FloatRect getRect();                            // получение размеров спрайта

    virtual void update()  = 0;                         // корректировка координат объекта относительно карты

protected:
    sf::Texture texture;                                // текстура объекта
    sf::Sprite  sprite;                                  // спрайт с объектом

    int xInTexture;                                     // начальная координата Х спрайта в текстуре
    int yInTexture;                                     // начальная координата Y спрайта в текстуре
    int width;                                          // ширина спрайта
    int height;                                         // высота спрайта
    float scaleX;                                       // масштабирование спрайта по X
    float scaleY;                                       // масштабирование спрайта по Y
    int distanceBetweenTiles;                           // расстояние между тайлами

    float posX;                                         // координата Х спрайта относительно карты
    float posY;                                         // координата Y спрайта относительно карты

    float health;                                       // здоровьте объекта

    float speedX;                                       // cкорость объекта по Х
    float speedY;                                       // cкорость объекта по Y
    float currentSpeedX;                                // текущая cкорость объекта по Х
    float currentSpeedY;                                // текущая cкорость объекта по Y

    float dTime;                                        // пройденное время между итерациями основного цикла

    int countFrames;                                    // количество кадров объекта в тайлсете
    float motionFrame;                                  // номер тайла в тайлсете

    std::vector<Object> objectsOnMap;                   // все объекты на карте(для коллизии)

    virtual void collisionX()        = 0;               // функция для решения коллизиипо X
    virtual void collisionY()        = 0;               // функция для решения коллизиипо Y
    virtual void healthChange()      = 0;               // изменение здоровья объекта
    virtual void motionFrameChange() = 0;               // изменение тайла в тайлсете

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override final; // Для window.draw(Person)
};

#endif // PERSONAGES_H
