#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <string>

#include <engine/features/Progressive.hpp>


class TextureCache {
    private:

        TextureCache() = default;
        TextureCache( const TextureCache& ) = delete;

        TextureCache& operator=( const TextureCache& ) = delete;
        TextureCache& operator=( const TextureCache&& ) = delete;

        struct Asset {
            std::string path;
            std::string id;
            int weight;
        };

    private:
        std::unordered_map< std::string, std::unique_ptr<sf::Texture> > __cache;

    public:
        static TextureCache& inst();

        void Load( Progressive& );

        const sf::Texture& get( const std::string& id ) const;
};