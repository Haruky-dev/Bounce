#include <engine/layers/HoldLayer.hpp>

#include <tools/Tool.hpp>

#include <print>


HoldLayer::HoldLayer() : Layer(), UI()
    {
        this->UI.configure( std::nullopt );
}

void HoldLayer::Load() {
    try {
        std::println("[Holding] ..");

        this->loader = std::thread( [this]() {

            sf::Context context;

            std::this_thread::sleep_for( std::chrono::seconds(2) );

            this->done.store( true );

            std::println("[Holding] Done!");
        } );

    } catch (...) {
        throw std::runtime_error("Thread Failure..");
    }    
}

void HoldLayer::Update( const sf::Time& dt ) {}

Action HoldLayer::feature() const {
    if ( this->done.load() ) {
        std::println("requested");

        return Action::dropOverlap;
    }

    return Action::None;
}

void HoldLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );
}

Layer::Type HoldLayer::type() const {
    return Layer::Type::Holding;
}

HoldLayer::~HoldLayer() {
    if ( this->loader.joinable() ) {
        this->loader.join();
    }
}