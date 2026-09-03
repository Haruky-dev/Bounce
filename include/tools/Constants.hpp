#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <tools/Json.hpp>

#include <array>


namespace Constants {
    inline Json::Type MODE = []( std::string_view mode ) -> Json::Type {
        if ( mode=="easy" ) return Json::Type::EASY;
        if ( mode=="medium" ) return Json::Type::MED;
        if ( mode=="hard" ) return Json::Type::HARD;

        throw std::runtime_error("Invalid 'mode string' given for 'Constants::_match_mode'");

    }(Json::String("setting.mode", Json::Type::SET));

    inline const int DELAY_t = 200;

    inline const int maxCD =  Json::Int("setting.maxCD", Json::Type::SET);
    inline const int WIDTH =  Json::Int("win.W", Json::Type::SET);
    inline const int HEIGHT = Json::Int("win.H", Json::Type::SET);
    inline const int W_EDGE = Json::Int("win.edge", Json::Type::SET);

    inline const sf::Vector2f W_CTR = {
        Constants::WIDTH / 2.0f,
        Constants::HEIGHT / 2.0f
    };

    inline const  std::array< const sf::Vector2f, 4 > Norms = {
        sf::Vector2f( {0.0f, -1.0f} ),
        sf::Vector2f( {-1.0f, 0.0f} ),
        sf::Vector2f( {0.0f,  1.0f} ),
        sf::Vector2f( {1.0f,  0.0f} )
    };

    enum class Sides {
        TOP, LEFT, BOTTOM, RIGHT
    };


    inline int P1_SCORE = 0;
    inline int P2_SCORE = 0;
    inline int CD = 0;
    inline int maxScore = Json::Int("setting.maxScore", Json::Type::SET);
    inline char ballOrient = '?';
    inline int buffingPeriod = Json::Int("setting.buffingPeriod");
    inline int freezeDuration = Json::Int("buff.freeze.durPivot");
    inline float offsetPercent = Json::Float("setting.offsetPercent");
    inline float stretchPercent = Json::Float("setting.stretchPercent");
};