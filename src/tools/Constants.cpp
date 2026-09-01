#include <tools/Constants.hpp>

#include <tools/Json.hpp>


std::string Constants::MODE = Json::String("setting.mode") + '.';

int Constants::CD = 0;
int Constants::maxCD = Json::Int("setting.maxCD");
int Constants::P1_SCORE = 0;
int Constants::P2_SCORE = 0;
int Constants::maxScore = Json::Int("setting.maxScore");
int Constants::DELAY_t = 200;
char Constants::ballOrient = '?';
int Constants::buffingPeriod = Json::Float("modes." + Constants::MODE + "settings.buffingPeriod");
float Constants::offsetPercent = Json::Float("modes." + Constants::MODE + "settings.offsetPercent" );
float Constants::stretchPercent = Json::Float("modes." + Constants::MODE + "settings.stretchPercent" );

int Constants::WIDTH = Json::Int("win.W");
int Constants::HEIGHT = Json::Int("win.H");
int Constants::W_EDGE = Json::Int("win.edge");

sf::Vector2f Constants::W_CTR = {
    Constants::WIDTH / 2.0f,
    Constants::HEIGHT / 2.0f
};

std::array<sf::Vector2f, 4> Constants::Norms = {
    sf::Vector2f( {0.0f, -1.0f} ),
    sf::Vector2f( {-1.0f, 0.0f} ),
    sf::Vector2f( {0.0f,  1.0f} ),
    sf::Vector2f( {1.0f,  0.0f} )
};