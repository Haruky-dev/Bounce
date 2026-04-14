#pragma once

#include <engine/Layer.hpp>
#include <cache/visuals/BaseUI.hpp>
#include <engine/features/Progressive.hpp>

#include <cache/visuals/MenuUI.hpp>
#include <cache/visuals/GameUI.hpp>
#include <cache/visuals/PauseUI.hpp>
#include <cache/visuals/SetUI.hpp>

#include <memory>


class UICache {
    private:
        UICache()  = default;
        ~UICache() = default;

        UICache( UICache& )  = delete;
        UICache( UICache&& ) = delete;

        UICache& operator=( UICache& )  = delete;
        UICache& operator=( UICache&& ) = delete;

        std::array< std::unique_ptr<BaseUI>, static_cast<std::size_t>( Layer::Type::Quit ) > cache;
            // State::Type::Quit == Last state == size (excluding Loading since it won't have a UI)

        template <typename T>
        constexpr int indexof() const {
            if constexpr ( std::is_same_v<T, MenuUI> ) {
                return 0;
            } else if constexpr ( std::is_same_v<T, SetUI>) {
                return 1;
            } else if constexpr ( std::is_same_v<T, GameUI> ) {
                return 2;
            } else if constexpr ( std::is_same_v<T, PauseUI> ) {
                return 3;
            }

            throw std::runtime_error("Invalid given [Type] in UICache!");
        }

    public:
        static UICache& inst() {
            static UICache I = UICache();

            return I;
        }

        template <typename T>
        void build( Progressive& prog ) {
            const int I = this->indexof<T>();

            assert( this->cache[I] == nullptr );

            this->cache[I] = std::make_unique<T>();

            this->cache[I]->configure( prog );
        }

        template <typename T>
        constexpr T& deploy() const {
            const int I = this->indexof<T>();

            return static_cast<T&>( *this->cache[I] );
        }
};