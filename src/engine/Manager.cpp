#include <engine/Manager.hpp>

#include <engine/Layer.hpp>
#include <engine/layers/LoadLayer.hpp>
#include <engine/layers/GameLayer.hpp>
#include <engine/layers/PauseLayer.hpp>
#include <engine/layers/SetLayer.hpp>
#include <engine/layers/MenuLayer.hpp>
#include <engine/layers/EndLayer.hpp>
#include <engine/layers/QuitLayer.hpp>

#include <engine/io/Process.hpp>
#include <engine/io/Input.hpp>

#include <engine/Dispatcher.hpp>

#include <tools/Constants.hpp>
#include <tools/Json.hpp>


// -- CONSTRUCTOR/DEST SECTION
Manager::Manager() : __stack() {
    // register all states
    this->__register[Layer::Type::Loading]  = []() { return std::make_unique<LoadLayer>(); };
    this->__register[Layer::Type::MainMenu] = []() { return std::make_unique<MenuLayer>(); };
    this->__register[Layer::Type::Setting]  = []() { return std::make_unique<SetLayer>(); };
    this->__register[Layer::Type::Play]     = []() { return std::make_unique<GameLayer>(); };
    this->__register[Layer::Type::Pause]    = []() { return std::make_unique<PauseLayer>(); };
    this->__register[Layer::Type::GameOver] = []() { return std::make_unique<EndLayer>(); };
    this->__register[Layer::Type::Quit]     = []() { return std::make_unique<QuitLayer>(); };

    __stack.push_back( {this->__register[Layer::Type::Loading]()} );
    __stack.back().layer->Load();
    this->__stack.back().Loaded = true;

    this->quit_flag = false;
}

// -- PUBLIC FUNCs SECTION
void Manager::Update( const sf::Time& dt, sf::RenderWindow& win ) {
    if ( this->__stack.empty() )
        return;

    this->updateLayers( dt );

    Layer& curr = *(this->__stack.back().layer);

    this->controlProcess(
        curr.Read({
            std::chrono::steady_clock::now(),
            Input(
                Input::validateButtons( curr.buttons(),win ),
                Input::validateKeys( curr.keys() )
            )
        }) );
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

void Manager::controlProcess( const Process& P ) {
    if ( P.act() == Process::Action::QUIT )
        this->quit_flag = true;
    else
        Dispatcher::handleOutput( *this, P );
}

void Manager::updateLayers( const sf::Time& dt ) {
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