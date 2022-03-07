#ifndef _BALL_H_
#define _BALL_H_

#include <SFML/Graphics.hpp>
class paddle;

enum class ballState : unsigned
{
    OUT_LEFT_RIGHT_BOUNDS,
    HIT_UP_DOWN_BOUNDS,
    HIT_LEFT_RIGHT_BOUNDS,
    NORMAL_MOVING_OR_STATIC
};

class ball
{
private:
    sf::CircleShape entity; // literally a static ball.
    sf::Vector2f velocity;
    ballState bState;
public:
    static const float BallInitVelo;
    static const float BallIncrPace;
    explicit ball(float radius = 10, float vel_x = BallInitVelo, float vel_y = BallInitVelo);
    ball(const ball&) = default;
    ball& operator=(const ball&) = default;
    ~ball() = default;
    const sf::Vector2f& getPosition(void) const
    {
        return entity.getPosition();
    }
    void setPosition(const sf::Vector2f& newPosition)
    {
        entity.setPosition(newPosition);
    }
    const sf::Vector2f& getVelocity(void) const
    {
        return velocity;
    }
    void setVelocity(const sf::Vector2f& newVelocity)
    {
        velocity = newVelocity;
    }
    float getRadius(void) const
    {
        return entity.getRadius();
    }
    void setRadius(float newRadius)
    {
        entity.setRadius(newRadius);
    }
    const sf::CircleShape& getDrawableCircle(void) const
    {
        return entity;
    }
    ballState update(const sf::Time interval, const paddle& pad);
    bool collide(const paddle& pad) const;
};


#endif