#include <engine/layers/LoadLayer.hpp>

#include <tools/Json.hpp>
#include <cache/FontCache.hpp>
#include <cache/SoundCache.hpp>
#include <cache/TextureCache.hpp>


LoadLayer::LoadLayer() : Layer(), UI() {
    this->UI.configure( std::nullopt );
}

void LoadLayer::Load() {
    try {
        loader = std::thread([this]() {
            // create OpenGL/SFML context
            sf::Context context;

            Json::reLoad();
            TextureCache::inst().Load( *this );
            SoundCache::Load( *this );
            FontCache::Load( *this );
            
            std::this_thread::sleep_for( std::chrono::seconds( 2 ) );

            this->done.store(true);
        });

    } catch (...) {
        throw std::runtime_error("Loading Thread Failed\n");
    }
}

void LoadLayer::Update(const sf::Time& dt) {
    this->UI.setValue(
        this->progress.load() / static_cast<float>(this->cost.load())
    );
    this->UI.update( dt );
}

void LoadLayer::Render(sf::RenderWindow &win) const {
    win.draw( this->UI.bg );
    win.draw( this->UI.progressText );
}

Action LoadLayer::feature() const {
    if ( this->done.load() )
        return Action::raiseMain;

    return Action::None;
}

Layer::Type LoadLayer::type() const { return Layer::Type::Loading; }

LoadLayer::~LoadLayer() {
    if (loader.joinable())
        loader.join();
}