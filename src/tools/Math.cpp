#include <tools/Math.hpp>

#include <math.h>


int Math::randi( int min, int max, bool rand_sign ) {
    std::uniform_int_distribution<int> dist( min, max );
    int val = dist(Math::__rengine);

    if ( !rand_sign ) return val;

    std::uniform_int_distribution<int> sign_dist( 0, 1 );

    return val * ( sign_dist(Math::__rengine)? 1 : -1  );
}
float Math::randf( float min, float max, bool rand_sign ) {
    std::uniform_real_distribution<float> dist( min, max );
    float val = dist(Math::__rengine);

    if ( !rand_sign ) return val;

    std::uniform_real_distribution<float> sign_dist( 0, 1 );

    return val * ( sign_dist(Math::__rengine)? 1 : -1  );
}

sf::Vector2f Math::Normalize( const sf::Vector2f& A ) {
    const double M = std::sqrt( (A.x * A.x  +   A.y * A.y) ); // Magnitude

    if (M <= 0.00f) return sf::Vector2f( 0.f, 0.f );

    sf::Vector2f UnitVect(A.x / M, A.y / M);

    return UnitVect;
}

// Probably unnecessary, review it asap
sf::Rect<int> Math::getBound(const sf::Sprite &spr) {
    return sf::IntRect(
        static_cast<sf::Vector2<int>>(spr.getGlobalBounds().position),
        static_cast<sf::Vector2<int>>(spr.getGlobalBounds().size)
    );
}

const double Math::Dot( const sf::Vector2f& A, const sf::Vector2f& B ) {
    return static_cast<double>( A.x * B.x  +  A.y * B.y );
}

double Math::Lerp( double A, double B, double t ) {
    return ( A + (B - A) * t );
}

sf::Vector2f Math::Lerp( const sf::Vector2f& A, const sf::Vector2f& B, double t ) {
    return sf::Vector2f(
        A.x + (B.x - A.x) * t,
        A.y + (B.y - A.y) * t
    );
}


// © https://easings.net
double Math::easeIn( double x ) {
    return x * x * x;
}
double Math::easeOut( double x ) {
    return 1 - (1-x)*(1-x)*(1-x);
}
double Math::easeInOut( double x ) {
    return (x < 0.5f)? 4.f * x * x * x :
        1 - ( (-2.f * x + 2)*(-2.f * x + 2)*(-2.f * x + 2) ) /2.f;
}
double Math::easeElastic( double x ) {
    const double A = (2 * 3.14159265f) / 3;

    return ( x == 0 )?
        0 : ( x == 1 )?
        1
        : std::pow( 2, -10*x ) * std::sin( (x*10 - 0.75f) * A ) + 1;
}