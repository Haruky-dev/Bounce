#include <engine/visuals/LoadUI.hpp>

#include <cache/FontCache.hpp>
#include <tools/Constants.hpp>


LoadUI::LoadUI() :
    BaseUI(), font("assets/fonts/RasterForge.ttf"),
    progressText(font, "")
    {}

void LoadUI::configure() {
    this->progressText.setString("[ 0 % ]");
    this->progressText.setOrigin( this->progressText.getGlobalBounds().getCenter() );
    this->progressText.setPosition( Constants::W_CTR );
    this->progressText.setFillColor( sf::Color::White );

    this->bg.setSize( Constants::W_CTR );
    this->bg.setFillColor( sf::Color::Black );
}

void LoadUI::update( const sf::Time& dt ) {
    progressText.setString(
          "[ "
        + std::to_string( static_cast<int>( this->v * 100.0f ) )
        + " % ]"
    );

    progressText.setOrigin( this->progressText.getLocalBounds().getCenter() );
    progressText.setPosition( Constants::W_CTR );
}