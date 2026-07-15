#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Constants.hpp>
#include <tools/Flags.hpp>


bool Dispatcher::handleOutput( Manager& manager, const Action act ) {
    Layer* lastLayer = manager.__stack.back().layer.get();
    switch ( act ) {

        case Action::None:
            break;

        case Action::raiseMain:
            manager.__stack.clear();

            manager.pushLayer( Layer::Type::MainMenu );
            // manager.__stack.back().layer->enter();
            break;

        case Action::raisePause:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Pause, true, true );
            break;

        case Action::raisePlay:
            lastLayer->exit();
            manager.pushLayer( Layer::Type::Play );
            break;

        case Action::raiseSett:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Setting, true, true );
            break;

        case Action::raiseQuit:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::Quit, true );
            break;

        case Action::raiseGameOv:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::GameOver, true, true );
            break;


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
            Flags::musicON = !Flags::musicON; break;

        case Action::toggleSFX:
            Flags::sfxON = !Flags::sfxON; break;

        case Action::dropOverlap: // dropOverLayer
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

    return true;
}
