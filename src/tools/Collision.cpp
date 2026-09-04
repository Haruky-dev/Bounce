#include <tools/Collision.hpp>

#include <tools/Flags.hpp>
#include <tools/Variables.hpp>


namespace Collision {
    bool wall( const sf::Rect<float>& ballB, Constants::Sides& side ) {
        // -------- TOP/BOTTOM wall CASE
        if ( ballB.position.y <= 5.0f ) { // bg edge
        // if ( ballB.position.y <= Constants::W_EDGE ) {
            side = Constants::Sides::TOP;
            return true;
        } else if ( (ballB.position.y + ballB.size.y) >= Constants::HEIGHT - 5.0f ) {
            side = Constants::Sides::BOTTOM;
            return true;
        }
    
        // --------- Goal CASE
        if ( ballB.position.x <= 0 ) { // Computer SIDE
            Flags::goalScored = true;
            side = Constants::Sides::LEFT;
    
            ( Variables::P2_SCORE < Variables::maxScore )?
                Variables::P2_SCORE++
            : throw std::runtime_error("Game Over. Invalid Value Reached!");
    
            Variables::ballOrient = '1';
    
            return true;
    
        } else if ( (ballB.position.x + ballB.size.x) >= Constants::WIDTH ) {
            Flags::goalScored = true;
            side = Constants::Sides::RIGHT;
    
            ( Variables::P1_SCORE < Variables::maxScore )?
                Variables::P1_SCORE++
            : throw std::runtime_error("Game Over. Invalid Value Reached!");
            
            Variables::ballOrient = '2';
    
            return true;
        }
    
        return false;
    }

    bool player( const sf::Rect<float>& P, const sf::Rect<float>& B, Constants::Sides& side ) {
        if ( B.position.x > (0.80f * Constants::WIDTH) ) // Only check if ball is somewhat near P1
            if ( P.findIntersection( B ).has_value() ) {
                side = Constants::Sides::RIGHT;
                return true;
            }
    
        return false;
    }
    
    bool computer(const sf::Rect<float>& P, const sf::Rect<float>& B, Constants::Sides& side ) {
        if ( B.position.x < (0.20f * Constants::WIDTH) )
            if ( P.findIntersection( B ).has_value() ) {
                side = Constants::Sides::LEFT;
                return true;
            }
    
        return false;
    }
}