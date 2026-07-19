#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Constants.hpp>
#include <tools/Flags.hpp>

#include <cache/SFX.hpp>


bool Dispatcher::handleOutput( Manager& manager, const Process& P ) {
    Layer* lastLayer = manager.__stack.back().layer.get();
    switch ( P.act() ) {

        case Process::Action::NONE:
            break;

        case Process::Action::raiseMain:
            manager.__stack.clear();

            manager.pushLayer( Layer::Type::MainMenu );
            // manager.__stack.back().layer->enter();
            break;

        case Process::Action::raisePause:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Pause, true, true );
            break;

        case Process::Action::raisePlay:
            lastLayer->exit();
            manager.pushLayer( Layer::Type::Play );
            break;

        case Process::Action::raiseSett:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Setting, true );
            break;

        case Process::Action::raiseQuit:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Quit, true );
            break;

        case Process::Action::raiseGameOv:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::GameOver, true, true );
            break;

        case Process::Action::incMaxScr:
            ( Constants::maxScore < 9 )? Constants::maxScore++ : 1; break;

        case Process::Action::decMaxScr:
            ( Constants::maxScore > 1 )? Constants::maxScore-- : 9;break;

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

        case Process::Action::dropOverlap: // dropOverLayer
            assert(
                manager.__stack.back().onOverlap
                && (manager.__stack.size() > 1)
            );

            lastLayer->exit();
            manager.__stack.back().onExit = true;
            break;

        default:
            return false;
    }

    SFX::inst().play( P.sfx() );

    return true;
}