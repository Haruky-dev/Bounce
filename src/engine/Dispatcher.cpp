#include <engine/Dispatcher.hpp>

#include <engine/Layer.hpp>
#include <tools/Tool.hpp>


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
            // std::cout << "Wanna quit?\n";
            break;

        case Action::raiseGameOv:
            lastLayer->pause();
            manager.pushLayer( Layer::Type::GameOver, true, true );
            break;

        case Action::raiseHold:
            manager.pushLayer( Layer::Type::Holding, true );
            break;

        case Action::incMaxScr:
            ( Tool::maxScore < 9 )? Tool::maxScore++ : 1;
            break;
        case Action::decMaxScr:
            ( Tool::maxScore > 1 )? Tool::maxScore-- : 9;
            break;

        case Action::incDiff:
            Tool::MODE = ( Tool::MODE == "hard" )? "easy"
                : (Tool::MODE == "easy")? "even"
                : (Tool::MODE == "even")? "hard" : "easy";

            Tool::MODE += ".";
            break;

        case Action::decDiff:
            Tool::MODE = (Tool::MODE == "hard")? "even"
                : (Tool::MODE == "even")? "easy"
                : (Tool::MODE == "easy")? "hard" : "easy";

            Tool::MODE += ".";            
            break;

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