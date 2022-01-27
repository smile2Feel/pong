#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class paddle;
class ball;

class gameRender
{
private:
    gameRender(sf::RenderTarget&, const sf::Font&);
    //std::unique_ptr<sf::RenderTarget> window;
    sf::RenderTarget& window;
    sf::Font mFont;
    //todo: font or something.
public:
    static gameRender& getInstance(sf::RenderTarget&, const sf::Font&);
    void render(const ball& Ball,
                const paddle& playerLeft, const paddle& playerRight,
                unsigned playerLeftScore, unsigned playerRightScore);
    gameRender(const gameRender&) = delete;
    gameRender& operator=(const gameRender&) = delete;
};

#endif