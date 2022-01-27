#include "paddle.h"
#include "pongGame.h"

const float paddle::speed = 100.f;

paddle::paddle(bool isLeftPaddle, float yPos)
: leftPaddle(isLeftPaddle), mRect(sf::Vector2f(pongGame::Width / 40, pongGame::Height / 7))
{
    mRect.setPosition((leftPaddle ? 0 : pongGame::Width * 39 / 40), yPos);
    mRect.setFillColor(sf::Color::Blue);
}

void paddle::setPosition(float y)
{
    float x = (leftPaddle ? 0 : mRect.getPosition().x);
    mRect.setPosition(sf::Vector2f(x, y));
}

float paddle::getPosition(void) const
{
    return mRect.getPosition().y;
}

void paddle::update(const sf::Time& interval)
{
    float pos = getPosition();
    if (leftPaddle)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pos -= speed * interval.asSeconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pos += speed * interval.asSeconds();
        } else {
            return;
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pos -= speed * interval.asSeconds();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pos += speed * interval.asSeconds();
        } else {
            return;
        }
    }

    // limit the height
    float RectHeight = mRect.getSize().y; 
    if (pos < 0)
    {
        pos = 0.f;
    }
    if (pos > pongGame::Height - RectHeight)
    {
        pos = pongGame::Height - RectHeight;
    }

    setPosition(pos);
}

const sf::RectangleShape& paddle::getDrawableRect(void) const
{
    return mRect;
}

float paddle::getPaddleHeight(void) const
{
    return mRect.getSize().y;
}
float paddle::getPaddleWidth(void) const
{
    return mRect.getSize().x;
}
