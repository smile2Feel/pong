#ifndef _PADDLE_H_
#define _PADDLE_H_
#include <SFML/Graphics.hpp>
#include "ball.h"

enum class Side : bool
{
    LEFT_PADDLE,
    RIGHT_PADDLE
};
class paddle
{
friend bool ball::collide(const paddle&) const; 
private:
    const Side side;
    sf::RectangleShape mRect;
    static const float speed;
public:
    paddle(Side);
    paddle() = default;
    ~paddle() = default;
    paddle(const paddle&) = default;
    paddle& operator=(const paddle&) = default;
    void setPosition(float);
    const sf::Vector2f& getPosition(void) const;
    void update(const sf::Time&);
    const sf::RectangleShape& getDrawableRect(void) const;
    float getPaddleHeight(void) const;
    float getPaddleWidth(void) const;
    const Side& whichSide(void) const;
};

#endif