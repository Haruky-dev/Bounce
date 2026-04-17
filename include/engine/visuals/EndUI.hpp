#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <engine/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>


class EndUI : public BaseUI {
    friend class EndLayer;
    
    private:
        sf::Sprite bg;
    
    public:
        EndUI();
        ~EndUI() = default;
        
        void configure( Progressive& );
};