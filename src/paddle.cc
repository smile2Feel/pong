#include "../include/paddle.h"
#include "../include/pongGame.h"

const float paddle::speed = 100.f;

paddle::paddle(Side s)
: side(s), mRect(sf::Vector2f(pongGame::Width / 40, pongGame::Height / 7))
{
    mRect.setPosition(((side == Side::LEFT_PADDLE) ? pongGame::Width * 1 / 40 : pongGame::Width * 38 / 40),
                        ((side == Side::LEFT_PADDLE) ? 0 : pongGame::Height * 6 / 7));
    mRect.setFillColor(sf::Color::Blue);
}

void paddle::setPosition(float y)
{
    float x = ((side == Side::LEFT_PADDLE) ? 0 : mRect.getPosition().x);
    mRect.setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f& paddle::getPosition(void) const
{
    return mRect.getPosition();
}

void paddle::update(const sf::Time& interval)
{
    float pos = getPosition().y;
    if (side == Side::LEFT_PADDLE)
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

const Side& paddle::whichSide(void) const
{
    return side;
}
