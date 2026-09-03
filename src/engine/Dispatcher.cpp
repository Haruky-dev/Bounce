#include <engine/Dispatcher.hpp>

#include <tools/Flags.hpp>
#include <engine/Layer.hpp>
#include <tools/Variables.hpp>

#include <cache/SFX.hpp>


void Dispatcher::handle( Manager& manager, const Action A ) {
    switch ( A ) {

        case Action::NONE:
            break;

        case Action::raiseMain:
        case Action::raisePause:
        case Action::raisePlay:
        case Action::raiseSett:
        case Action::raiseQuit:
        case Action::raiseGameOv:
        case Action::dropOverlap:
            this->__process_layers( A,  manager );
            break;

        case Action::incMaxScr:
        case Action::decMaxScr:
        case Action::incDiff:
        case Action::decDiff:
        case Action::toggleMusic:
        case Action::toggleSFX:
            __process_settings( A );
            break;

        default: return;
    }

    // SFX::inst().play( P.sfx() );
}


void Dispatcher::__process_settings( const Action A ) {
    switch ( A ) {
        case Action::incMaxScr:
            ( Variables::maxScore < 9 )? Variables::maxScore++ : 1;
            break;

        case Action::decMaxScr:
            ( Variables::maxScore > 1 )? Variables::maxScore-- : 9;
            break;

        case Action::incDiff:
            switch ( Variables::MODE ) {
                case Json::Type::EASY: Variables::MODE = Json::Type::MED; break;
                case Json::Type::MED:  Variables::MODE = Json::Type::HARD; break;
                case Json::Type::HARD: Variables::MODE = Json::Type::EASY; break;

                default: throw std::runtime_error("Invalid [Variables::MODE]!");
            }
            break;

        case Action::decDiff:
            switch ( Variables::MODE ) {
                case Json::Type::EASY: Variables::MODE = Json::Type::HARD; break;
                case Json::Type::MED:  Variables::MODE = Json::Type::EASY; break;
                case Json::Type::HARD: Variables::MODE = Json::Type::MED; break;

                default: throw std::runtime_error("Invalid [Variables::MODE]!");
            }
            break;

        case Action::toggleMusic:
            Flags::musicON = !Flags::musicON;
            break;

        case Action::toggleSFX:
            Flags::sfxON = !Flags::sfxON;
            break;

        default: return;
    }
}

void Dispatcher::__process_layers( const Action A, Manager& M ) {
    Layer* lastLayer = M.__stack.back().layer.get();

    switch ( A ) {
        case Action::raiseMain:
            M.__stack.clear();
            M._pushLayer( Layer::Type::MainMenu );
            break;

        case Action::raisePause:
            lastLayer->pause();
            M._pushLayer( Layer::Type::Pause, true, true );
            break;

        case Action::raisePlay:
            lastLayer->exit();
            M._pushLayer( Layer::Type::Play );
            break;

        case Action::raiseSett:
            lastLayer->pause();
            M._pushLayer( Layer::Type::Setting, true );
            break;

        case Action::raiseQuit:
            lastLayer->pause();
            M._pushLayer( Layer::Type::Quit, true );
            break;

        case Action::raiseGameOv:
            lastLayer->pause();
            M._pushLayer( Layer::Type::GameOver, true, true );
            break;

        case Action::dropOverlap: // dropOverLayer
            assert(
                M.__stack.back().onOverlap
                && (M.__stack.size() > 1)
            );

            lastLayer->exit();
            M.__stack.back().onExit = true;
            break;

        default: return;
    }
}