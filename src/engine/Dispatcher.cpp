#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Constants.hpp>
#include <tools/Flags.hpp>

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
            ( Constants::maxScore < 9 )? Constants::maxScore++ : 1;
            break;

        case Action::decMaxScr:
            ( Constants::maxScore > 1 )? Constants::maxScore-- : 9;
            break;

        case Action::incDiff:
            switch ( Constants::MODE.at(0) ) {
                case 'E': Constants::MODE = 'M'; break;
                case 'M': Constants::MODE = 'H'; break;
                case 'H': Constants::MODE = 'E'; break;

                default: throw std::runtime_error("Invalid [Constants::MODE]!");
            }
            Constants::MODE += ".";
            break;

        case Action::decDiff:
            switch ( Constants::MODE.at(0) ) {
                case 'E': Constants::MODE = 'H'; break;
                case 'M': Constants::MODE = 'E'; break;
                case 'H': Constants::MODE = 'M'; break;

                default: throw std::runtime_error("Invalid [Constants::MODE]!");
            }
            Constants::MODE += ".";
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