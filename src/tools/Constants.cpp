#include <tools/Constants.hpp>

#include <tools/Json.hpp>


int Constants::CD = 0;
int Constants::maxCD = Json::Int("setting.maxCD");
int Constants::P1_SCORE = 0;
int Constants::P2_SCORE = 0;
int Constants::maxScore = Json::Int("setting.maxScore");
int Constants::DELAY_t = 200;
char Constants::ballOrient = '?';

int Constants::WIDTH = Json::Int("win.W");
int Constants::HEIGHT = Json::Int("win.H");
int Constants::W_EDGE = Json::Int("win.edge");

sf::Vector2f Constants::W_CTR = {
    Constants::WIDTH / 2.0f,
    Constants::HEIGHT / 2.0f
};

std::string Constants::MODE = Json::String("setting.mode") + '.';

std::array<sf::Vector2f, 4> Constants::Norms = {
    sf::Vector2f( {0.0f, -1.0f} ),
    sf::Vector2f( {-1.0f, 0.0f} ),
    sf::Vector2f( {0.0f,  1.0f} ),
    sf::Vector2f( {1.0f,  0.0f} )
};