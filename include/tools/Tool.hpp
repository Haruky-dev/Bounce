#pragma once

#include <SFML/Graphics.hpp>

#include <array>

#include <engine/Layer.hpp>

class Ball;
class Player;


class Tool {
    public:
        static int P1_SCORE;
        static int P2_SCORE;
        static int CD;
        static int maxCD;
        static int maxScore;
        static bool goalScored;
        static char ballOrient;

        static int WIDTH;
        static int HEIGHT;
        static int W_EDGE;
        static sf::Vector2f W_CTR;

        enum class Sides {
            TOP, LEFT, BOTTOM, RIGHT
        };

        static std::array< sf::Vector2f, 4 > Norms;

        static sf::Rect<int> getBound( const sf::Sprite& spr );
};
