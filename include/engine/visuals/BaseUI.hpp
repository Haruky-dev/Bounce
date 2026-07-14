#pragma once

#include <engine/features/Progressive.hpp>
#include <tools/Tool.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <optional>


class BaseUI {
    public:
        virtual void update( const sf::Time& ) = 0;
        virtual void configure( const std::optional<Progressive*>& ) = 0;

        virtual ~BaseUI() = default;

    protected:
        template <typename T>
        sf::Vector2<T> __normalize( const sf::Rect<int>& bounds, const sf::Vector2<T>& pos ) {
            const T X = Tool::W_CTR.x - bounds.size.x / 2.0f;
            const T Y = Tool::W_CTR.y - bounds.size.y / 2.0f;

            return sf::Vector2<T>(
                X + pos.x,
                Y + pos.y
            );
        }
};
