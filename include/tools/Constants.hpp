#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <tools/Json.hpp>

#include <array>


namespace Constants {
    inline const int DELAY_t = 200;

    inline const int WIDTH =  Json::Int("win.W", Json::Type::SET);
    inline const int HEIGHT = Json::Int("win.H", Json::Type::SET);
    inline const int W_EDGE = Json::Int("win.edge", Json::Type::SET);
    inline const int maxCD =  Json::Int("setting.maxCD", Json::Type::SET);

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
};