#include <tools/Math.hpp>

#include <math.h>

int Math::randi( const int min, const int max ) {
    std::uniform_int_distribution<int> dist( min, max );
    
    return dist( Math::randEngine() );
}
float Math::randf( const float min, const float max ) {
    std::uniform_real_distribution<float> dist( min, max );
    
    return dist( Math::randEngine() );
}

sf::Vector2f Math::Normalize( const sf::Vector2f& A ) {
    const double M = std::sqrt( (A.x * A.x  +   A.y * A.y) ); // Magnitude

    if (M <= 0.00f) return sf::Vector2f( 0.f, 0.f );

    sf::Vector2f UnitVect(A.x / M, A.y / M);

    return UnitVect;
}

const double Math::Dot( const sf::Vector2f& A, const sf::Vector2f& B ) {
    return static_cast<double>( A.x * B.x  +  A.y * B.y );
}

double Math::Lerp( const double A, const double B, const double t ) {
    return ( A + (B - A) * t );
}

sf::Vector2f Math::Lerp( const sf::Vector2f& A, const sf::Vector2f& B, const double t ) {
    return sf::Vector2f(
        A.x + (B.x - A.x) * t,
        A.y + (B.y - A.y) * t
    );
}


// © https://easings.net
double Math::easeIn( const double x ) {
    return x * x * x;
}
double Math::easeOut( const double x ) {
    return 1 - (1-x)*(1-x)*(1-x);
}
double Math::easeInOut( const double x ) {
    return (x < 0.5f)? 4.f * x * x * x :
        1 - ( (-2.f * x + 2)*(-2.f * x + 2)*(-2.f * x + 2) ) /2.f;
}
double Math::easeElastic( const double x ) {
    const double A = (2 * 3.14159265f) / 3;

    return ( x == 0 )?
        0 : ( x == 1 )?
        1
        : std::pow( 2, -10*x ) * std::sin( (x*10 - 0.75f) * A ) + 1;
}

std::mt19937& Math::randEngine() {
    static std::mt19937 eng(std::random_device{}());

    return eng;
}