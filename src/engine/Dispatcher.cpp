#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Constants.hpp>
#include <tools/Flags.hpp>

#include <cache/SFX.hpp>


void Dispatcher::handle( Manager& manager, const Process& P ) {
    Layer* lastLayer = manager.__stack.back().layer.get();
    switch ( P.act() ) {

        case Process::Action::NONE:
            break;

        case Process::Action::raiseMain:
        case Process::Action::raisePause:
        case Process::Action::raisePlay:
        case Process::Action::raiseSett:
        case Process::Action::raiseQuit:
        case Process::Action::raiseGameOv:
        case Process::Action::dropOverlap:
            this->__process_layers( P.act(),  manager );
            break;

        case Process::Action::incMaxScr:
        case Process::Action::decMaxScr:
        case Process::Action::incDiff:
        case Process::Action::decDiff:
        case Process::Action::toggleMusic:
        case Process::Action::toggleSFX:
            __process_settings( P.act() );
            break;

        default: return;
    }

    SFX::inst().play( P.sfx() );
}


void Dispatcher::__process_settings( const Process::Action A ) {
    switch ( A ) {
        case Process::Action::incMaxScr:
            ( Constants::maxScore < 9 )? Constants::maxScore++ : 1;
            break;

        case Process::Action::decMaxScr:
            ( Constants::maxScore > 1 )? Constants::maxScore-- : 9;
            break;

        case Process::Action::incDiff:
            switch ( Constants::MODE.at(0) ) {
                case 'E': Constants::MODE = 'M'; break;
                case 'M': Constants::MODE = 'H'; break;
                case 'H': Constants::MODE = 'E'; break;

                default: throw std::runtime_error("Invalid [Constants::MODE]!");
            }
            Constants::MODE += ".";
            break;

        case Process::Action::decDiff:
            switch ( Constants::MODE.at(0) ) {
                case 'E': Constants::MODE = 'H'; break;
                case 'M': Constants::MODE = 'E'; break;
                case 'H': Constants::MODE = 'M'; break;

                default: throw std::runtime_error("Invalid [Constants::MODE]!");
            }
            Constants::MODE += ".";
            break;

        case Process::Action::toggleMusic:
            Flags::musicON = !Flags::musicON;
            break;

        case Process::Action::toggleSFX:
            Flags::sfxON = !Flags::sfxON;
            break;

        default: return;
    }
}

void Dispatcher::__process_layers( const Process::Action A, Manager& M ) {
    Layer* lastLayer = M.__stack.back().layer.get();

    switch ( A ) {
        case Process::Action::raiseMain:
            M.__stack.clear();
            M.pushLayer( Layer::Type::MainMenu );
            break;

        case Process::Action::raisePause:
            lastLayer->pause();
            M.pushLayer( Layer::Type::Pause, true, true );
            break;

        case Process::Action::raisePlay:
            lastLayer->exit();
            M.pushLayer( Layer::Type::Play );
            break;

        case Process::Action::raiseSett:
            lastLayer->pause();
            M.pushLayer( Layer::Type::Setting, true );
            break;

        case Process::Action::raiseQuit:
            lastLayer->pause();
            M.pushLayer( Layer::Type::Quit, true );
            break;

        case Process::Action::raiseGameOv:
            lastLayer->pause();
            M.pushLayer( Layer::Type::GameOver, true, true );
            break;

        case Process::Action::dropOverlap: // dropOverLayer
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