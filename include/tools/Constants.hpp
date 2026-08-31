#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <array>


class Constants {
    public:
        static int P1_SCORE;
        static int P2_SCORE;
        static int CD;
        static int maxCD;
        static int maxScore;
        static int DELAY_t;
        static int ballAccel;
        static char ballOrient;
        static float offsetPercent;
        static float stretchPercent;

        static int WIDTH;
        static int HEIGHT;
        static int W_EDGE;
        static sf::Vector2f W_CTR;
        static std::string MODE;

        enum class Sides {
            TOP, LEFT, BOTTOM, RIGHT
        };

        static std::array< sf::Vector2f, 4 > Norms;
};