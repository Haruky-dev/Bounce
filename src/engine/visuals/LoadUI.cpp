#include <engine/visuals/LoadUI.hpp>

#include <cache/FontCache.hpp>
#include <tools/Tool.hpp>


LoadUI::LoadUI() :
    BaseUI(), __font("assets/fonts/RasterForge.ttf"),
    progressText(__font, "")
    {}

void LoadUI::configure( const std::optional<Progressive*>& prog ) {
    if ( prog.has_value() ) (*prog)->add_to_total( 10 );

    this->progressText.setString("[ 0 % ]");
    this->progressText.setOrigin( this->progressText.getGlobalBounds().getCenter() );
    this->progressText.setPosition( Tool::W_CTR );
    this->progressText.setFillColor( sf::Color::White );
    // this->progressText.setScale( {3.0f, 3.0f} );

    this->bg.setSize( Tool::W_CTR );
    this->bg.setFillColor( sf::Color::Black );

    if ( prog.has_value() ) (*prog)->increment_by( 10 );
}

void LoadUI::update( const sf::Time& dt ) {
    progressText.setString(
          "[ "
        + std::to_string( static_cast<int>( this->v * 100.0f ) )
        + " % ]"
    );

    progressText.setOrigin( this->progressText.getLocalBounds().getCenter() );
    progressText.setPosition( Tool::W_CTR );
}