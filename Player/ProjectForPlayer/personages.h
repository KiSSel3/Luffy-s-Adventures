#ifndef PERSONAGES_H
#define PERSONAGES_H

#include <SFML/Graphics.hpp>

class Personages : public sf::Drawable {
protected:
    sf::Texture texture;                      // текстура объекта
    sf::Sprite sprite;                        // спрайт с объектом

    int xInTexture;                           // начальная координата Х спрайта в текстуре
    int yInTexture;                           // начальная координата Y спрайта в текстуре
    int width;                                // ширина спрайта
    int height;                               // высота спрайта
    int distanceBetweenTiles;                 // расстояние между тайлами

    float posX;                               // координата Х спрайта относительно карты
    float posY;                               // координата Y спрайта относительно карты

    float health;                             // здоровьте объекта

    float speedX;                             // cкорость объекта по Х

    float dTime;                              // пройденное время между итерациями основного цикла

    float motionFrame;                        // номер тайла в спрайте

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override final; // Для window.draw(Person)
    virtual void update() = 0;                // корректировка координат объекта относительно карты
    virtual void collision() = 0;             // функция для решения коллизии
    virtual void healthChange() = 0;          // изменение здоровья объекта
    virtual void motionFrameChange() = 0;     // изменение тайла в спрайте

public:
    void dTimeSet(float dTime);               // инициализация поля dTime
    void speedChange(float speedX);           // изменение скорости объекта
};

#endif // PERSONAGES_H
