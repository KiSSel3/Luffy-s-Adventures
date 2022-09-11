#pragma once

#include "SFML/Graphics.hpp"

class Entity
{
public:
    virtual ~Entity() { };
                                          
    sf::FloatRect getRect();                                                                                   

    virtual void update(sf::RenderWindow& window, float dTime) = 0;  

protected:                                                                                                   

    std::string filePath;                                            

    sf::Texture texture;                                              
    sf::Sprite sprite;                                               

    int xInTexture;                                                  
    int yInTexture;                                                  
    int width;                                                        
    int height;                                                       
    float scaleX;                                                    
    float scaleY;                                                                                         
    float posX;                                                      
    float posY;                                                                                                                                                                                                       

    float dTime;     
    float motionFrame;                                                                                   
};

