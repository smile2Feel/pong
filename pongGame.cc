#include "pongGame.h"
#include "ball.h"
#include "gameRender.h"


const unsigned pongGame::Width;
const unsigned pongGame::Height;
const sf::Time pongGame::TimePerFrame = sf::seconds(1.f / 60.f);
const unsigned pongGame::MaxScore;

pongGame::pongGame()
 : mPlayerLeft(Side::LEFT_PADDLE), mPlayerRight(Side::RIGHT_PADDLE),
   mPlayState(playState::SERVE_PLAYER_RIGHT),
   playerRightScore(0), playerLeftScore(0)
{}

void pongGame::handleEvent(sf::Window& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        break;
    }
}

void pongGame::run(void)
{
    sf::Clock clock;
    sf::Time timeLag = sf::Time::Zero;
    bool playerLeft = false;

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Pong");
    sf::Font font;
    font.loadFromFile("Fonts/arial.ttf");
    gameRender& renderGame = gameRender::getInstance(window, font);

    while (window.isOpen())
    {
        sf::Time delta = clock.restart();
        timeLag += delta;
        while (timeLag >= TimePerFrame)
        {
            update(TimePerFrame);
            timeLag -= TimePerFrame;
            playerLeft = !playerLeft;
        }
        renderGame.render(mBall, mPlayerLeft, mPlayerRight, playerLeftScore, playerRightScore);
        window.display();
        handleEvent(window);
    }
}

gameState pongGame::update(const sf::Time& time)
{
    mPlayerLeft.update(time);
    mPlayerRight.update(time);

    switch (mPlayState)
    {
    case playState::SERVE_PLAYER_LEFT:
        //mBall.setVelocity({0, 0});
        //mBall.setPosition({pongGame::Width / 2 - mBall.getRadius(), pongGame::Height / 2 - mBall.getRadius()});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            mBall.setVelocity({-ball::BallInitVelo, -ball::BallInitVelo});
            mPlayState = playState::TOWARD_PLAYER_LEFT;
        }
        break;
    case playState::SERVE_PLAYER_RIGHT:
        //mBall.setVelocity({0, 0});
        //mBall.setPosition({pongGame::Width / 2 - mBall.getRadius(), pongGame::Height / 2 - mBall.getRadius()});
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            mBall.setVelocity({ball::BallInitVelo, ball::BallInitVelo});
            mPlayState = playState::TOWARD_PLAYER_RIGHT;
        }
        break;
    default:
        break;
    }

    ballState bState = ballState::NORMAL_MOVING_OR_STATIC;
    switch (mPlayState)
    {
    case playState::TOWARD_PLAYER_LEFT:
        bState = mBall.update(time, mPlayerLeft);
        if (bState == ballState::OUT_LEFT_RIGHT_BOUNDS)
        {
            playerRightScore++;
            mPlayState = playState::SERVE_PLAYER_RIGHT;
        } else if (bState == ballState::HIT_LEFT_RIGHT_BOUNDS)
        {
            mPlayState = playState::TOWARD_PLAYER_RIGHT;
        }
        break;
    case playState::TOWARD_PLAYER_RIGHT:
        bState = mBall.update(time, mPlayerRight);
        if (bState == ballState::OUT_LEFT_RIGHT_BOUNDS)
        {
            playerLeftScore++;
            mPlayState = playState::SERVE_PLAYER_LEFT;
        } else if (bState == ballState::HIT_LEFT_RIGHT_BOUNDS)
        {
            mPlayState = playState::TOWARD_PLAYER_LEFT;
        }
        break;
    default:
        break;
    }
    
    if (playerLeftScore >= MaxScore || playerRightScore >= MaxScore)
    {
        return gameState::MENU;
    }

    return gameState::IN_GAME;
}