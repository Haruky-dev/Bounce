#pragma once

#include <SFML/Graphics.hpp>

#include <random>


namespace Math {
    int randi( int min=0, int max=0, bool rand_sign=false );
    float randf( float min=0.0f, float max=1.0f, bool rand_sign=false );
    sf::Vector2f Normalize( const sf::Vector2f& A );
    sf::Rect<int> getBound( const sf::Sprite& spr );
    const double Dot( const sf::Vector2f& A, const sf::Vector2f& B );
    double Lerp( double A, double B, double t );
    sf::Vector2f Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t );
    double easeIn( double x );
    double easeOut( double x );
    double easeInOut( double x );
    double easeElastic( double x );

    inline std::mt19937 __rengine(std::random_device{}());
};