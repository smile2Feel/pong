#ifndef _PONG_GAME_H_
#define _PONG_GAME_H_

#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"
#include "pongMenu.h"

enum class playState : unsigned
{
    SERVE_PLAYER_LEFT,
    SERVE_PLAYER_RIGHT,
    TOWARD_PLAYER_LEFT,
    TOWARD_PLAYER_RIGHT    
};

class pongGame
{
private:
    unsigned playerLeftScore;
    unsigned playerRightScore;
    ball mBall;
    paddle mPlayerLeft;
    paddle mPlayerRight;
    playState mPlayState;    
public:
    static const unsigned Width = 640;
    static const unsigned Height = 480;
    static const unsigned MaxScore = 5;
    static const sf::Time TimePerFrame;
public:
    pongGame();
    ~pongGame() = default;
    void run(void);
    void handleEvent(sf::Window&);
    gameState update(const sf::Time& time);
};

#endif
