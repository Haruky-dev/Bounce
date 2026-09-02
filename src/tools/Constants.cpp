#include <tools/Constants.hpp>

#include <tools/Json.hpp>


Json::Type Constants::MODE = Constants::_match_mode( Json::String("setting.mode", Json::Type::SET) );

int Constants::CD = 0;
int Constants::maxCD = Json::Int("setting.maxCD", Json::Type::SET);
int Constants::P1_SCORE = 0;
int Constants::P2_SCORE = 0;
int Constants::maxScore = Json::Int("setting.maxScore", Json::Type::SET);
int Constants::DELAY_t = 200;
char Constants::ballOrient = '?';
int Constants::buffingPeriod = Json::Float("settings.buffingPeriod");
float Constants::offsetPercent = Json::Float("settings.offsetPercent" );
float Constants::stretchPercent = Json::Float("settings.stretchPercent" );

int Constants::WIDTH = Json::Int("win.W", Json::Type::SET);
int Constants::HEIGHT = Json::Int("win.H", Json::Type::SET);
int Constants::W_EDGE = Json::Int("win.edge", Json::Type::SET);

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

Json::Type Constants::_match_mode( const std::string_view str ) {
    if ( str=="easy" ) return Json::Type::EASY;
    if ( str=="medium" ) return Json::Type::MED;
    if ( str=="hard" ) return Json::Type::HARD;

    throw std::runtime_error("Invalid 'mode string' given for 'Constants::_match_mode'");
}