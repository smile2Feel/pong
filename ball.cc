#include "ball.h"
#include "pongGame.h"

const float ball::BallInitVelo = 100;
const float ball::BallIncrPace = 1.5;

ball::ball(float radius, float vel_x, float vel_y)
: entity(radius), velocity(vel_x, vel_y), bState(ballState::NORMAL_MOVING_OR_STATIC)
{
    entity.setPosition(sf::Vector2f(pongGame::Width / 2 - radius, pongGame::Height / 2 -radius));
    entity.setFillColor(sf::Color::Green);
}

ballState ball::update(const sf::Time interval, const paddle& pad)
{
    auto pos = entity.getPosition();
    pos += velocity * interval.asSeconds();
    entity.setPosition(pos);
    
    // overpass the boarder
    float radius = entity.getRadius();
    float padWidth = pad.getPaddleWidth();

    bState = ballState::NORMAL_MOVING_OR_STATIC;
    if (pos.x < padWidth || pos.x > (pongGame::Width - radius * 2 - padWidth))
    {
        if (collide(pad))
        {
            float newPosX = ((pos.x < padWidth) ? padWidth : (pongGame::Width - radius * 2 - padWidth));
            setPosition({newPosX, pos.y});
            setVelocity({-velocity.x * BallIncrPace, velocity.y * BallIncrPace});
            bState = ballState::HIT_LEFT_RIGHT_BOUNDS;
        } else {
            // reset the ball.
            setPosition({pongGame::Width / 2 - radius, pongGame::Height / 2 - radius});
            setVelocity({0, 0});
            bState = ballState::OUT_LEFT_RIGHT_BOUNDS;
        }
    }
    if (pos.y < 0 || pos.y > (pongGame::Height - radius * 2))
    {
        float newPosY = (pos.y < 0 ? 0 : (pongGame::Height - radius * 2));
        setPosition({pos.x, newPosY});
        setVelocity({velocity.x, -velocity.y});
        bState = ballState::HIT_UP_DOWN_BOUNDS;
    }
    return bState;
}

bool ball::collide(const paddle& pad) const
{
    if (entity.getGlobalBounds().intersects(pad.mRect.getGlobalBounds()))
    {
        return true;
    }
    return false;
}