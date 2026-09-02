#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <tools/Json.hpp>

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
        static int buffingPeriod;
        static int freezeDuration;
        static float offsetPercent;
        static float stretchPercent;

        static int WIDTH;
        static int HEIGHT;
        static int W_EDGE;
        static sf::Vector2f W_CTR;
        static Json::Type MODE;

        enum class Sides {
            TOP, LEFT, BOTTOM, RIGHT
        };

        static std::array< sf::Vector2f, 4 > Norms;

    private:
        static Json::Type _match_mode( const std::string_view );
};