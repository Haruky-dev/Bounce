#include <engine/layers/LoadLayer.hpp>

#include <tools/Json.hpp>

#include <cache/FontCache.hpp>
#include <cache/SoundCache.hpp>
#include <cache/TextureCache.hpp>

#include <engine/Layer.hpp>

using namespace std::literals::chrono_literals;
class MenuUI; class GameUI; class SetUI; class PauseUI;


LoadLayer::LoadLayer() : Layer(), fnt(), txt(fnt), progTxt(fnt) {
    if (!(fnt.openFromFile("assets/fonts/RasterForge.ttf")))
        throw std::runtime_error("UNABLE TO LOAD [FONT] in Loading State!");

    txt.setFont(fnt);
    progTxt.setFont(fnt);
    txt.setString("Loading..");
    txt.setOrigin(
        txt.getGlobalBounds().size / 2.f
    );
    txt.setPosition({360.f, 200.f});
    txt.setFillColor(sf::Color::White);

    progTxt.setFont(fnt);
    progTxt.setString("0 %");
    progTxt.setOrigin(
        progTxt.getGlobalBounds().size / 2.f
    );
    progTxt.setPosition({360.f, 240});
    progTxt.setFillColor(sf::Color::White);

    bg.setSize(sf::Vector2f(720.f, 480.f));
    bg.setFillColor(sf::Color::Black);
}

void LoadLayer::Load() {
    try {
        loader = std::thread([this]() {
            
            // create OpenGL/SFML context
            sf::Context ctx;

            Json::reLoad();
            TextureCache::inst().Load( *this );
            SoundCache::Load( *this );
            FontCache::Load( *this );

            loadDone.store(true);
        });
    } catch (...) {
        throw std::runtime_error("Loading Thread Failed\n");   
    }
}

void LoadLayer::Update(sf::Time &dt) {
    progTxt.setString(
        std::to_string(
            static_cast<int>( (currUnit.load() / static_cast<float>(loadCost.load()) ) * 100.0f )
        )
        + " %"
    );

    progTxt.setOrigin(
        progTxt.getGlobalBounds().size / 2.f
    );

    progTxt.setPosition({360.f, 240});
}

void LoadLayer::Render(sf::RenderWindow &win) const {
    win.draw(bg);
    win.draw(txt);
    win.draw(progTxt);
}

Action LoadLayer::feature() const {
    if ( this->loadDone.load() )
        return Action::raiseMain;
    
    return Action::None;
}

Layer::Type LoadLayer::getType() const { return Layer::Type::Loading; }

LoadLayer::~LoadLayer() {
    if (loader.joinable())
        loader.join();
}