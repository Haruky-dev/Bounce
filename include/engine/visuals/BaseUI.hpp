#pragma once

#include <tools/Constants.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>


class BaseUI {
    public:
        virtual void update( const sf::Time& ) = 0;
        virtual void configure() = 0;

        virtual ~BaseUI() = default;

    protected:
        template <typename T>
        sf::Vector2<T> normalize_( const sf::Rect<int>& bounds, const sf::Vector2<T>& pos ) {
            const T X = Constants::W_CTR.x - bounds.size.x / 2.0f;
            const T Y = Constants::W_CTR.y - bounds.size.y / 2.0f;

            return sf::Vector2<T>(
                X + pos.x,
                Y + pos.y
            );
        }
};
