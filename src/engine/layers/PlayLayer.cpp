#include <engine/layers/PlayLayer.hpp>

#include <SFML/Graphics.hpp>

#include <tools/Flags.hpp>
#include <tools/Math.hpp>
#include <tools/Collision.hpp>
#include <cache/SFX.hpp>


PlayLayer::PlayLayer() :
    Layer(),
    P1(this->UI.pad, 0),
    P2(this->UI.pad, 1),
    ball(this->UI.ball) {
        this->UI.configure();

        char orients[2] = {'1', '2'};
        // Constants::ballOrient = '1';
        Constants::ballOrient = orients[ Math::randi(0, 1) ];
    }

PlayLayer::~PlayLayer() = default;

void PlayLayer::Load() {
    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Toejam_and_Earl.ogg" )))
        throw std::runtime_error("Failure");

    this->music->setLooping( true );

    this->form_request();
}

void PlayLayer::Update( const sf::Time& dt ) {
    if ( this->music->getStatus() != sf::Music::Status::Playing || !(Flags::musicON) )
        this->music->play();

    this->updateEntities( dt );
    this->UI.update( dt );
    this->P1.update( dt );
    this->P2.update( dt, ball );
    this->FR.update( dt );
}

void PlayLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );
    win.draw( this->FR );

    if ( Constants::CD != -1 )
        win.draw( this->UI.countD );

    win.draw( this->UI.score_1 ); // score 0
    win.draw( this->UI.score_2 ); // score 1

    win.draw( this->P1 );
    win.draw( this->P2 );
    win.draw( this->ball );

    if ( (Constants::CD!=-1) && !this->P1.ready() )
        win.draw( this->UI.banner );
}

void PlayLayer::resume() { this->UI.sync(); }

void PlayLayer::exit() {
    this->music.reset();
    Constants::P1_SCORE = Constants::P2_SCORE = Constants::CD = 0;
}
Layer::Type PlayLayer::type() const { return Layer::Type::Play; }


Action PlayLayer::feature() const {
    if ( Constants::P1_SCORE >= Constants::maxScore ) {
        SFX::inst().play(SFX::Type::LOSE);
        return Action::raiseGameOv;

    } else if ( Constants::P2_SCORE >= Constants::maxScore ) {
        SFX::inst().play(SFX::Type::WIN);
        return Action::raiseGameOv;
    }

    return Action::NONE;
}

void PlayLayer::form_request() {
    // Keyboard request
    this->__requests.emplace_back( sf::Keyboard::Key::Escape, Action::raiseMain );
    this->__requests.emplace_back( sf::Keyboard::Key::Space, Action::raisePause );

    this->__requests.emplace_back( sf::Mouse::Button::Left, Action::raiseMain
        ).require( Constraint::bounds( this->UI.bounds.at(PlayUI::BTNS::MENU) ) );
}

void PlayLayer::moveBall( const sf::Time& dt ) {
    if ( !(this->ball.onMove) && this->ball.onStart ) {
        if ( Constants::CD >= Constants::maxCD ) {
            this->ball.launch();
            this->ball.onStart = false;
        } else if ( Constants::CD == 0 )
            this->UI.set_players_ready( this->P1.ready(), this->P2.ready() );

    } else if ( this->ball.onMove ) {
        this->ball.rotate( dt );
        this->ball.spr.move(
            this->ball.speed * dt.asSeconds() * this->ball.unitDirec
        );
    }
}

void PlayLayer::updateEntities( const sf::Time& dt ) {
    this->moveBall( dt );

    const bool ballCollided = Collision::wall( this->ball.bounds(), this->norme )
                           || Collision::player( this->P1.bounds(), this->ball.bounds(), this->norme )
                           || Collision::computer( this->P2.bounds(), this->ball.bounds(), this->norme );

    if ( Flags::goalScored ) {
        assert( Constants::ballOrient == '1' || Constants::ballOrient == '2' );

        switch (this->norme) {
            
            case Constants::Sides::RIGHT:
                this->P1.refresh(); break;
            case Constants::Sides::LEFT:
                this->P2.refresh(); break;
            default: {}
        }

        this->ball.reset();
        return;
    }

    if ( ballCollided ) {
        this->refinePlayers();
        this->refineBall();
    }
}

void PlayLayer::refinePlayers() {
    if ( this->norme == Constants::Sides::RIGHT ) {
        this->P1.refresh();
        this->ball.refresh(this->P1.direction);
        SFX::inst().play(SFX::Type::PAD);

    } else if ( this->norme == Constants::Sides::LEFT ) {
        this->P2.refresh();
        this->ball.refresh(this->P2.direction);
        SFX::inst().play(SFX::Type::PAD);
    }
}

void PlayLayer::refineBall() {
    if ( this->norme==Constants::Sides::TOP || this->norme==Constants::Sides::BOTTOM )
        SFX::inst().play(SFX::Type::WALL);


    this->ball.reflect(this->norme);
    this->ball.adjust(
        this->norme,
        (this->norme==Constants::Sides::RIGHT)? P1.bounds()
        : (this->norme==Constants::Sides::LEFT)? P2.bounds()
        : sf::Rect<float>()
    );
}