#include <tools/Tool.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <tools/Json.hpp>
#include <entities/Ball.hpp>
#include <entities/Player.hpp>
#include <cache/visuals/BaseUI.hpp>


int Tool::CD = 0;
int Tool::maxCD = Json::Int("setting.maxCD");

int Tool::P1_SCORE = 0;
int Tool::P2_SCORE = 0;
int Tool::maxScore = Json::Int("setting.maxScore");
bool Tool::goalScored = false;
char Tool::ballOrient = '?';

int Tool::WIDTH = Json::Int("win.W");
int Tool::HEIGHT = Json::Int("win.H");
int Tool::W_EDGE = Json::Int("win.edge");

sf::Vector2f Tool::W_CTR = {
    Tool::WIDTH / 2.0f,
    Tool::HEIGHT / 2.0f
};

// REVIEW THIS SHIT, google it
std::array<sf::Vector2f, 4> Tool::Norms = {
    sf::Vector2f( {0.0f, -1.0f} ),
    sf::Vector2f( {-1.0f, 0.0f} ),
    sf::Vector2f( {0.0f,  1.0f} ),
    sf::Vector2f( {1.0f,  0.0f} )
};

// REVIEW THIS SHIT
sf::Rect<int> Tool::getBound( const sf::Sprite& spr ) {
    return sf::IntRect(
        static_cast<sf::Vector2i>(spr.getGlobalBounds().position), // local bounds?
        static_cast<sf::Vector2i>(spr.getGlobalBounds().size)
    );
}