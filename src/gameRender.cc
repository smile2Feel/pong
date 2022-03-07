#include "../include/gameRender.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/pongGame.h"

gameRender::gameRender(sf::RenderTarget& target, const sf::Font& font)
//todo: decltype must be an object
// : window(new decltype(target))
 : window(target), mFont(font)
{
}

gameRender& gameRender::getInstance(sf::RenderTarget& target, const sf::Font& font)
{
    static gameRender render(target, font);
    return render;
}

void gameRender::render(const ball& Ball,
            const paddle& playerLeft, const paddle& playerRight,
            unsigned playerLeftScore, unsigned playerRightScore)
{
    window.clear();

    // render the ball and two paddles
    window.draw(Ball.getDrawableCircle());
    window.draw(playerLeft.getDrawableRect());
    window.draw(playerRight.getDrawableRect());

    // render the score text
    sf::Text score(std::to_string(playerLeftScore) + "   " + std::to_string(playerRightScore), mFont, 40);
    sf::FloatRect bounds = score.getLocalBounds();
    score.setPosition({pongGame::Width/2-bounds.width/2, 0});
    window.draw(score);
}


