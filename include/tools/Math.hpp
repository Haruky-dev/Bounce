#pragma once

#include <SFML/Graphics.hpp>
#include <tools/Tool.hpp>

#include <random>


class Math {
    public:
        static int randi( const int min=0, const int max=0 );
        static float randf( const float min=0.0f, const float max=1.0f );
        static sf::Vector2f Normalize( const sf::Vector2f& A );
        static const double Dot( const sf::Vector2f& A, const sf::Vector2f& B );
        static double Lerp( const double A, const double B, const double t );
        static sf::Vector2f Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t );
        static double easeIn( const double x );
        static double easeOut( const double x );
        static double easeInOut( const double x );
        static double easeElastic( const double x );

    private:
        static std::mt19937& randEngine();
};