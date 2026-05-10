#pragma once

#include <SFML/Graphics/Font.hpp>

class Progressive;


class FontCache {
    private:
        friend class LoadLayer;

        static void Load( Progressive& );
      
    public:
        static sf::Font ARIAL;
        static sf::Font RASTER;
        static sf::Font KA;
        static sf::Font MineCraf;
};