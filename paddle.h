#ifndef _PADDLE_H_
#define _PADDLE_H_
#include <SFML/Graphics.hpp>
#include "ball.h"

class paddle
{
friend bool ball::collide(const paddle&) const; 
private:
    bool leftPaddle;
    sf::RectangleShape mRect;
    static const float speed;
public:
    paddle(bool isleftPaddle, float yPos);
    paddle() = default;
    ~paddle() = default;
    paddle(const paddle&) = default;
    paddle& operator=(const paddle&) = default;
    void setPosition(float);
    float getPosition(void) const;
    void update(const sf::Time&);
    const sf::RectangleShape& getDrawableRect(void) const;
    float getPaddleHeight(void) const;
    float getPaddleWidth(void) const;
};

#endif