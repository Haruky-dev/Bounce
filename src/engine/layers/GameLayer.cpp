#include <engine/layers/GameLayer.hpp>
    
#include <SFML/Graphics.hpp>

#include <tools/Flags.hpp>
#include <tools/Math.hpp>
#include <tools/Collision.hpp>
#include <cache/SFX.hpp>


GameLayer::GameLayer() :
    Layer(),
    P1(this->UI.pad, 0),
    P2(this->UI.pad, 1),
    ball(this->UI.ball) {
        this->UI.configure();

        char orients[2] = {'1', '2'};
        Constants::ballOrient = '1';
        // Constants::ballOrient = orients[ Math::randi(0, 1) ];
    }

GameLayer::~GameLayer() = default;

void GameLayer::Load() {
    this->music = std::make_unique<sf::Music>();
    if (!(this->music->openFromFile( "assets/musics/Toejam_and_Earl.ogg" )))
        throw std::runtime_error("Failure");

    this->music->setLooping( true );

    this->form_request();
}

void GameLayer::Update( const sf::Time& dt ) {
    if ( this->music->getStatus() != sf::Music::Status::Playing || !(Flags::musicON) )
        this->music->play();

    this->updateBall( dt );
    this->UI.update( dt );
    this->P1.update( dt );
    this->P2.update( dt, ball );
    this->FR.update( dt );
}

void GameLayer::Render( sf::RenderWindow& win ) const {
    win.draw( this->UI.bg );
    win.draw( this->FR );

    if ( Constants::CD != -1 )
        win.draw( this->UI.countD );

    win.draw( this->UI.score_1 ); // score 0
    win.draw( this->UI.score_2 ); // score 1

    win.draw( this->P1 );
    win.draw( this->P2 );
    win.draw( this->ball );
}

void GameLayer::resume() { this->UI.sync(); }

void GameLayer::exit() {
    this->music.reset();
    Constants::P1_SCORE = Constants::P2_SCORE = Constants::CD = 0;
}
void GameLayer::pause() {
    // this->initT();
    // this->music->setVolume( 10 );
}
Layer::Type GameLayer::type() const { return Layer::Type::Play; }


Action GameLayer::feature() const {
    if (
        ( Constants::P1_SCORE >= Constants::maxScore ) 
        || ( Constants::P2_SCORE >= Constants::maxScore )
    )
        return Action::raiseGameOv;
    
    return Action::None;
}

void GameLayer::form_request() {
    // Keyboard request
    this->requests.emplace_back( sf::Keyboard::Key::Escape, Action::raiseMain );
    this->requests.emplace_back( sf::Keyboard::Key::Space, Action::raisePause );
}

void GameLayer::updateBall( const sf::Time& dt ) {
    if ( !(this->ball.onMove) && this->ball.onStart ) {
        if ( Constants::CD >= Constants::maxCD ) {
            this->ball.launch();
            this->ball.onStart = false;
        } else if ( Constants::CD == 0 ) {
            this->UI.set_players_ready(
                this->P1.ready(), this->P2.ready()
            );
        }
    } else if ( this->ball.onMove ) {
        this->ball.rotate( dt );
        this->ball.spr.move(
            this->ball.speed * dt.asSeconds() * this->ball.unitDirec
        );
    }

    if (
        Collision::wall( this->ball.bounds(), this->norme )
     || Collision::player( this->P1.bounds(), this->ball.bounds(), this->norme )
     || Collision::computer( this->P2.bounds(), this->ball.bounds(), this->norme )
    ) {
            if ( Flags::goalScored ) {
                assert( Constants::ballOrient == '1' || Constants::ballOrient == '2' );
    
                this->ball.reset();
                return;
            }

        this->refresh_entities();            
        this->ball.reflect( this->norme );

        sf::Rect<float> padBounds = (this->norme == Constants::Sides::RIGHT)?
                                    P1.bounds()
                                    : (this->norme == Constants::Sides::LEFT)?
                                    P2.bounds() : sf::Rect<float>();

        this->ball.adjust( this->norme, padBounds );
    }
}

void GameLayer::refresh_entities() {
    switch ( this->norme ) {
        case Constants::Sides::RIGHT: {
            SFX::inst().play(SFX::Type::PAD);
            this->P1.refresh();
            const int factor = this->guide_direcion(this->P1.id);
            if ( factor ) {
                const int unit = this->P1.bounce_acceleration() * factor;

                this->ball.speed += unit;
            }
        }
            break;

        case Constants::Sides::LEFT: {
            SFX::inst().play(SFX::Type::PAD);
            this->P2.refresh();
            const int factor = this->guide_direcion(this->P2.id);
            if ( factor ) {
                const int unit = this->P2.bounce_acceleration() * factor;
                this->ball.speed += unit;
            }
            
        }
            break;

        default:
            SFX::inst().play(SFX::Type::WALL);
    }
}

const int GameLayer::guide_direcion( const int id ) const {
    switch ( id ) {
        case 0:
            if ( this->P1.direction ) {
                return
                    ( this->P1.direction == this->ball.direction )? 1 : -1;
            } else return 0;

        case 1:
            if ( this->P2.direction ) {
                return
                    ( this->P2.direction == this->ball.direction )? 1 : -1;
            } else return 0;
            break;
        
        default:
            throw std::runtime_error("Invalid given [ID] in 'GameLayer::guide_direction'.\
                            'id==" + std::to_string(id) + "' !");
    }
}