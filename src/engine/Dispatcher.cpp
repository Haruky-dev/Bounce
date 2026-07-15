#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Tool.hpp>

#include <iostream>

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
            ( Tool::maxScore < 9 )? Tool::maxScore++ : 1;
            break;
        case Action::decMaxScr:
            ( Tool::maxScore > 1 )? Tool::maxScore-- : 9;
            break;

        case Action::incDiff:
            switch ( Tool::MODE.at(0) ) {
                case 'E': Tool::MODE = 'M'; break;
                case 'M': Tool::MODE = 'H'; break;
                case 'H': Tool::MODE = 'E'; break;

                default: throw std::runtime_error("Invalid [Tool::MODE]!");
            }
            Tool::MODE += ".";
            break;

        case Action::decDiff:
            switch ( Tool::MODE.at(0) ) {
                case 'E': Tool::MODE = 'H'; break;
                case 'M': Tool::MODE = 'E'; break;
                case 'H': Tool::MODE = 'M'; break;

                default: throw std::runtime_error("Invalid [Tool::MODE]!");
            }
            Tool::MODE += ".";
            break;

        case Action::toggleMusic:
            Tool::musicON = !Tool::musicON; break;

        case Action::toggleSFX:
            Tool::sfxON = !Tool::sfxON; break;

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
