#pragma once

#include <SFML/System/Time.hpp>


class Motion {
    public:
        explicit Motion();
            
        void forward();
        void backward();
        
        void update( const sf::Time& dt );
        
        float prog() const;
        bool finished() const;
        bool onReverse() const;
        
    private:
        float duration, elapsed;
        int direction;
        bool active;
};