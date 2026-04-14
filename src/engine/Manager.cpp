#include <engine/Manager.hpp>

#include <engine/Layer.hpp>
#include <engine/layers/LoadLayer.hpp>
#include <engine/layers/GameLayer.hpp>
#include <engine/layers/PauseLayer.hpp>
#include <engine/layers/SetLayer.hpp>
#include <engine/layers/MenuLayer.hpp>
#include <engine/layers/EndLayer.hpp>

#include <engine/input/Action.hpp>
#include <engine/input/InputEv.hpp>

#include <engine/features/Animated.hpp>

#include <tools/Tool.hpp>
#include <tools/Json.hpp>
#include <cache/UICache.hpp>
#include <cache/SoundCache.hpp>
#include <cache/TextureCache.hpp>

#include <memory>


// -- CONSTRUCTOR/DEST SECTION
Manager::Manager() : __stack() {
    // register all states
    this->__register[Layer::Type::Loading]  = []() { return std::make_unique<LoadLayer>(); };
    this->__register[Layer::Type::MainMenu] = []() { return std::make_unique<MenuLayer>(); };
    this->__register[Layer::Type::Setting]  = []() { return std::make_unique<SetLayer>(); };
    this->__register[Layer::Type::Play]     = []() { return std::make_unique<GameLayer>(); };
    this->__register[Layer::Type::Pause]    = []() { return std::make_unique<PauseLayer>(); };
    this->__register[Layer::Type::GameOver] = []() { return std::make_unique<EndLayer>(); };

    __stack.push_back( this->__register[Layer::Type::Loading]() );
    __stack.back()->Load();
}

// -- PUBLIC FUNCs SECTION
void Manager::Update( sf::Time& dt, sf::RenderWindow& win ) {
    if ( this->__stack.empty() )
        return;

    this->updateLayers( dt );

    Layer& curr = *(this->__stack.back());
    Input in;

    in.mouse = InputEv::MouseClick( curr.getButtons(), win );
    in.keyb  = InputEv::keybClick( curr.getKeys() );

    this->controlOut(
        curr.Read( in )
    );   
}

void Manager::Render( sf::RenderWindow& win ) const {
    if ( !(this->__stack.empty()) )
        this->renderLayers( win );
}


// -- PRIVATE Func Section
void Manager::pushLayer( Layer::Type T, bool overlapLast ) {
    if ( !(this->__stack.empty()) )
        if ( this->__stack.back()->getType() == T )
            return;

    this->__stack.push_back( this->__register[T]() );
    Layer* lastLayer = this->__stack.back().get();
       
    lastLayer->setOverlap( overlapLast );

    if ( !lastLayer->isLoaded() ) {
        __stack.back()->Load();
        __stack.back()->setLoaded(true);
    }
    
    // this->__stack.back().
}

void Manager::controlOut( const Action out ) {
    if ( this->__stack.empty() ) return;
    
    Layer* lastLayer = this->__stack.back().get();
    
    switch ( out ) {
        case Action::None:
            return; break;
            
        case Action::raiseMain:
            this->__stack.clear();

            this->pushLayer( Layer::Type::MainMenu );            
            this->__stack.back()->enter();
            break;

        case Action::raisePause:
            lastLayer->pause();
            this->pushLayer( Layer::Type::Pause, true );
            break;

        case Action::raisePlay:
            lastLayer->exit();
            this->pushLayer( Layer::Type::Play );
            break;

        case Action::raiseSett:
            lastLayer->pause();
            this->pushLayer( Layer::Type::Setting, true );
            break;

        case Action::raiseQuit:
            // std::cout << "Wanna quit?\n";
            break;

        case Action::raiseGameOv:
            lastLayer->pause();
            this->pushLayer( Layer::Type::GameOver, true );
            break;

        case Action::dropOverlap:
            assert(
                ( this->__stack.back()->isOverlapping() )
                && (this->__stack.size() > 1)
            );

            lastLayer->exit();
            break;
    }
}

void Manager::updateLayers( sf::Time& dt ) {
    // update all (top + overlapping) states in __stack each frame

    int I = static_cast<int>(this->__stack.size()) - 1;

    for ( ; I >= 0; I-- ) {

        this->__stack[ I ]->Update( dt );

        if ( !this->__stack[ I ]->isOverlapping() )
            break;

        // frozen state case !!
    }

    Layer* lastLayer = this->__stack.back().get();

    if ( lastLayer && lastLayer->popable() ) { // you just have to override popable/exit for pause to work,
                                        // and perhaps tweak Transition::speed for slowmotion to work. SEE YA!
                                        // don't forget to clean Animated <3
        this->__stack.pop_back();
        assert( this->__stack.size() > 0 );
        this->__stack.back()->resume();
    }
}

void Manager::renderLayers( sf::RenderWindow& win ) const {
    // render all (top + overlapping) states in __stack starting from the first
    int currIndex = static_cast<int>(this->__stack.size()) - 1;

    // find index of last state that isn't overlaping
        // AKA a main state, that takes up the whole window
    while ( (currIndex > 0) && __stack[currIndex]->isOverlapping() ) {
        currIndex--;
    }

    for (int i = currIndex; i < __stack.size(); i++)
        __stack[i]->Render( win );
}