#include <engine/Manager.hpp>

#include <engine/Layer.hpp>
#include <engine/layers/LoadLayer.hpp>
#include <engine/layers/HoldLayer.hpp>
#include <engine/layers/GameLayer.hpp>
#include <engine/layers/PauseLayer.hpp>
#include <engine/layers/SetLayer.hpp>
#include <engine/layers/MenuLayer.hpp>
#include <engine/layers/EndLayer.hpp>

#include <engine/input/Action.hpp>
#include <engine/input/InputEv.hpp>


#include <tools/Tool.hpp>
#include <tools/Json.hpp>

#include <print>


// -- CONSTRUCTOR/DEST SECTION
Manager::Manager() : __stack() {
    // register all states
    this->__register[Layer::Type::Loading]  = []() { return std::make_unique<LoadLayer>(); };
    this->__register[Layer::Type::Holding]  = []() { return std::make_unique<HoldLayer>(); };
    this->__register[Layer::Type::MainMenu] = []() { return std::make_unique<MenuLayer>(); };
    this->__register[Layer::Type::Setting]  = []() { return std::make_unique<SetLayer>(); };
    this->__register[Layer::Type::Play]     = []() { return std::make_unique<GameLayer>(); };
    this->__register[Layer::Type::Pause]    = []() { return std::make_unique<PauseLayer>(); };
    this->__register[Layer::Type::GameOver] = []() { return std::make_unique<EndLayer>(); };

    __stack.push_back( {this->__register[Layer::Type::Loading]()} );
    __stack.back().layer->Load();
    this->__stack.back().Loaded = true;
}

// -- PUBLIC FUNCs SECTION
void Manager::Update( sf::Time& dt, sf::RenderWindow& win ) {
    if ( this->__stack.empty() )
        return;

    this->updateLayers( dt );

    Layer& curr = *(this->__stack.back().layer);
    Input in;

    in.mouse = InputEv::MouseClick( curr.buttons(), win );
    in.keyb  = InputEv::keybClick( curr.keys() );

    this->controlOut( curr.Read( in ) );
}

void Manager::Render( sf::RenderWindow& win ) const {
    if ( !(this->__stack.empty()) )
        this->renderLayers( win );
}


// -- PRIVATE Func Section
void Manager::pushLayer( Layer::Type T, bool overlapping, bool freezeLast ) {
    if ( !(this->__stack.empty()) )
        if ( this->__stack.back().layer->type() == T )
            return;

    if ( freezeLast )
        this->__stack.back().onFreeze = true;

    this->__stack.push_back( {this->__register[T](), overlapping} );

    if ( !(this->__stack.back().Loaded) ) {
        this->__stack.back().layer->Load();
        this->__stack.back().Loaded = true;
    }

    this->__stack.back().layer->enter();
}

void Manager::controlOut( const Action out ) {
    Layer* lastLayer = this->__stack.back().layer.get();

    switch ( out ) {
        case Action::None:
            return; break;

        case Action::raiseMain:
            this->__stack.clear();

            this->pushLayer( Layer::Type::MainMenu );            
            // this->__stack.back().layer->enter();
            break;

        case Action::raisePause:
            lastLayer->pause();
            this->pushLayer( Layer::Type::Pause, true, true );
            break;

        case Action::raisePlay:
            lastLayer->exit();
            this->pushLayer( Layer::Type::Play );
            break;

        case Action::raiseSett:
            lastLayer->pause();
            this->pushLayer( Layer::Type::Setting, true, true );
            break;

        case Action::raiseQuit:
            // std::cout << "Wanna quit?\n";
            break;

        case Action::raiseGameOv:
            lastLayer->pause();
            this->pushLayer( Layer::Type::GameOver, true, true );
            break;

        case Action::raiseHold:
            this->pushLayer( Layer::Type::Holding, true );
            break;

        case Action::dropOverlap: // dropOverLayer
            assert(
                this->__stack.back().onOverlap
             && (this->__stack.size() > 1)
            );

            lastLayer->exit();
            this->__stack.back().onExit = true;
    }
}

void Manager::updateLayers( sf::Time& dt ) {
    int I = static_cast<int>(this->__stack.size()) - 1;

    for ( ; I >= 0; I-- ) {
        if ( !(this->__stack.at( I ).onFreeze) )
            this->__stack.at( I ).layer->Update( dt );

        if ( !(this->__stack.at( I ).onOverlap) ) break;
    }

    State& state = this->__stack.back();

    // An on-exit + animated, layer has finished its exit animation
    const bool flag = state.layer                // non-nullptr
                   && state.layer->animated()    //
                   && state.onExit               // Manager requested an exit animation
                   && state.layer->popable(); // animation done

    if ( flag ) {
        this->__stack.pop_back();
        assert( !(this->__stack.empty()) );

        this->__stack.back().onFreeze = false;
        this->__stack.back().layer->resume(); // optional, might delete later on
    }
}

void Manager::renderLayers( sf::RenderWindow& win ) const {
    // render all (top + overlapping) states in __stack starting from the first
    int currIndex = static_cast<int>(this->__stack.size()) - 1;

    // find index of last state that isn't overlaping
        // AKA a main state, that takes up the whole window
    while ( (currIndex > 0) && __stack.at( currIndex).onOverlap ) {
        currIndex--;
    }

    for (int i = currIndex; i < __stack.size(); i++)
        __stack.at( i ).layer->Render( win );
}