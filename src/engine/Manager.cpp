#include <engine/Manager.hpp>

#include <SFML/Window/Event.hpp>

#include <engine/Layer.hpp>
#include <engine/layers/LoadLayer.hpp>
#include <engine/layers/PlayLayer.hpp>
#include <engine/layers/PauseLayer.hpp>
#include <engine/layers/SetLayer.hpp>
#include <engine/layers/MenuLayer.hpp>
#include <engine/layers/EndLayer.hpp>
#include <engine/layers/QuitLayer.hpp>

#include <engine/io/Action.hpp>
#include <engine/io/Input.hpp>

#include <engine/Dispatcher.hpp>

#include <tools/Constants.hpp>
#include <tools/Json.hpp>

#include <algorithm>


// -- CONSTRUCTOR/DEST SECTION
Manager::Manager() : stack_() {
    // register all states
    this->register_[Layer::Type::Loading]  = []() { return std::make_unique<LoadLayer>(); };
    this->register_[Layer::Type::MainMenu] = []() { return std::make_unique<MenuLayer>(); };
    this->register_[Layer::Type::Setting]  = []() { return std::make_unique<SetLayer>(); };
    this->register_[Layer::Type::Play]     = []() { return std::make_unique<PlayLayer>(); };
    this->register_[Layer::Type::Pause]    = []() { return std::make_unique<PauseLayer>(); };
    this->register_[Layer::Type::GameOver] = []() { return std::make_unique<EndLayer>(); };
    this->register_[Layer::Type::Quit]     = []() { return std::make_unique<QuitLayer>(); };

    stack_.push_back( {this->register_[Layer::Type::Loading]()} );
    stack_.back().layer->Load();
    this->stack_.back().Loaded = true;

    this->quit_flag = false;
}

// -- PUBLIC FUNCs SECTION
void Manager::Update( const sf::Time& dt, std::span<const sf::Event> events ) {
    if ( this->stack_.empty() )
        return;

    this->updateLayers_( dt );

    Layer& curr = *(this->stack_.back().layer);

    this->controlExit_( events );

    this->controlAction_(
        curr.Read({
            std::chrono::steady_clock::now(),
            Input(
                Input::validateButtons( curr.buttons(), events ),
                Input::validateKeys( curr.keys(), events )
            )
        }) );
}

void Manager::Render( sf::RenderWindow& win ) const {
    if ( !(this->stack_.empty()) )
        this->renderLayers_( win );
}


// -- PRIVATE Func Section
void Manager::pushLayer_( Layer::Type T, bool overlapping, bool freezeLast ) {
    if ( !(this->stack_.empty()) )
        if ( this->stack_.back().layer->type() == T )
            return;

    if ( freezeLast )
        this->stack_.back().onFreeze = true;

    this->stack_.push_back( {this->register_[T](), overlapping} );

    if ( !(this->stack_.back().Loaded) ) {
        this->stack_.back().layer->Load();
        this->stack_.back().Loaded = true;
    }

    this->stack_.back().layer->enter();
}

void Manager::controlAction_( const Action A ) {
    if ( A == Action::Quit )
        this->quit_flag = true;
    else
        Dispatcher::inst().handle( *this, A );
}

void Manager::controlExit_( std::span<const sf::Event> events ) {
    const bool exit_requested = std::ranges::find_if(
        events.begin(), events.end(),
        [] ( const sf::Event& E ) { return E.is<sf::Event::Closed>(); }
    ) != events.end();

    if ( exit_requested ) {
        if ( this->stack_.back().layer->type() != Layer::Type::MainMenu )
            this->quit_flag = true;

        this->stack_.back().layer->pause();
        this->pushLayer_(Layer::Type::Quit, true);
    }
}

void Manager::updateLayers_( const sf::Time& dt ) {
    int I = static_cast<int>(this->stack_.size()) - 1;

    for ( ; I >= 0; I-- ) {
        if ( !(this->stack_.at( I ).onFreeze) )
            this->stack_.at( I ).layer->Update( dt );

        if ( !(this->stack_.at( I ).onOverlap) ) break;
    }

    State& state = this->stack_.back();

    // An on-exit + animated, layer has finished its exit animation
    const bool flag = state.layer                // non-nullptr
                   && state.layer->animated()    //
                   && state.onExit               // Dispatcher requested an exit animation
                   && state.layer->popable(); // animation done

    if ( flag ) {
        this->stack_.pop_back();
        assert( !(this->stack_.empty()) );

        this->stack_.back().onFreeze = false;
        this->stack_.back().layer->resume(); // optional, might delete later on
    }
}

void Manager::renderLayers_( sf::RenderWindow& win ) const {
    // render all (top + overlapping) states in stack_ starting from the first
    int currIndex = static_cast<int>(this->stack_.size()) - 1;

    // find index of last state that isn't overlaping
        // AKA a main state, that takes up the whole window
    while ( (currIndex > 0) && stack_.at( currIndex).onOverlap ) {
        currIndex--;
    }

    for (int i = currIndex; i < stack_.size(); i++)
        stack_.at( i ).layer->Render( win );
}