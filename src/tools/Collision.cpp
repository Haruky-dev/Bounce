#include <tools/Collision.hpp>


bool Collision::wall( const sf::Rect<float>& ballB, Tool::Sides& side ) {
    // only check if ball.y is somewhat near TOP/BOTTOM wall
    // 
    // -------- TOP/BOTTOM wall CASE
    if ( ballB.position.y <= 5.0f ) { // bg edge
    // if ( ballB.position.y <= Tool::W_EDGE ) {
        side = Tool::Sides::TOP;
        return true;
    } else if ( (ballB.position.y + ballB.size.y) >= Tool::HEIGHT - 5.0f ) {
    // } else if ( (ballB.position.y + ballB.size.y) >= (Tool::HEIGHT - Tool::W_EDGE) ) {
        side = Tool::Sides::BOTTOM;
        return true;
    }

    // --------- Goal CASE
    if ( ballB.position.x <= 0 ) { // Computer SIDE
        Tool::goalScored = true;

        ( Tool::P2_SCORE < Tool::maxScore )?
            Tool::P2_SCORE++
          : throw std::runtime_error("Game Over. Invalid Value Reached!");

        Tool::ballOrient = '1';

        return true;

    } else if ( (ballB.position.x + ballB.size.x) >= Tool::WIDTH ) {
        Tool::goalScored = true;

        ( Tool::P1_SCORE < Tool::maxScore )?
            Tool::P1_SCORE++
          : throw std::runtime_error("Game Over. Invalid Value Reached!");
          
        Tool::ballOrient = '2';

        return true;
    }

    return false;
}

bool Collision::player( const sf::Rect<float>& P, const sf::Rect<float>& B, Tool::Sides& side ) {
    if ( B.position.x > (0.80f * Tool::WIDTH) ) // Only check if ball is somewhat near P1
        if ( P.findIntersection( B ).has_value() ) {
            side = Tool::Sides::RIGHT;
            return true;
        }

    return false;
}

bool Collision::computer(const sf::Rect<float>& P, const sf::Rect<float>& B, Tool::Sides& side ) {
    if ( B.position.x < (0.20f * Tool::WIDTH) )
        if ( P.findIntersection( B ).has_value() ) {
            side = Tool::Sides::LEFT;
            return true;
        }

    return false;
}