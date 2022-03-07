#include "../include/ball.h"
#include "../include/pongGame.h"

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
    
    // get the paddle and ball position
    float radius = entity.getRadius();
    float padWidth = pad.getPaddleWidth();
    float padHeight = pad.getPaddleHeight();
    const sf::Vector2f& padPos = pad.getPosition();

    bState = ballState::NORMAL_MOVING_OR_STATIC;

    // if ball and paddle collided, reset the speed, direction, ball position
    if (collide(pad))
    {
        // reset the ball position, we don't want the ball embedded into the paddle
        float newPosX = ((pad.whichSide() == Side::LEFT_PADDLE) ? (padPos.x + padWidth): (padPos.x- radius * 2));
        setPosition({newPosX, pos.y});
        setVelocity({-velocity.x * BallIncrPace, velocity.y * BallIncrPace});
        bState = ballState::HIT_LEFT_RIGHT_BOUNDS;
    }

    // if ball hits the up or down wall, bounce back
    if (pos.y < 0 || pos.y > (pongGame::Height - radius * 2))
    {
        float newPosY = (pos.y < 0 ? 0 : (pongGame::Height - radius * 2));
        setPosition({pos.x, newPosY});
        setVelocity({velocity.x, -velocity.y});
        bState = ballState::HIT_UP_DOWN_BOUNDS;
    }

    // if ball are out of the left or right wall, reset the gameStatus and so on
    if ((pos.x + 2 * radius) < 0 || pos.x > pongGame::Width) 
    {
        setPosition({pongGame::Width / 2 - radius, pongGame::Height / 2 - radius});
        setVelocity({0, 0});
        bState = ballState::OUT_LEFT_RIGHT_BOUNDS;
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