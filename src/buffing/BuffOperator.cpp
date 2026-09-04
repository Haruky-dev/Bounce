#include <buffing/BuffOperator.hpp>

#include <tools/Variables.hpp>
#include <buffing/Generator.hpp>

#include <print>


BuffOperator& BuffOperator::inst() {
    static BuffOperator inst;

    return inst;
}

BuffOperator::BuffOperator() :
    period_(Variables::buffingPeriod),
    elapsed_(sf::Time::Zero),
    lastFire_(sf::Time::Zero)
    {}

void BuffOperator::update( const sf::Time& dt ) {
    if ( this->elapsed_.asSeconds() >= this->period_ ) {
        this->elapsed_ = sf::Time::Zero;
        this->list_.push_front( Generator::yield() );
        this->list_.front()->apply();

        // DEBUG INFOS
        const Buff* head = this->list_.front().get();
        std::cout << "buff [pushed]; ";
        std::cout << "Target=";
        std::cout << ( (head->target==Buff::Target::P1)? "[Human]" : (head->target==Buff::Target::P2)? "[Computer]" : "[Ball]" );
        std::cout << '\n';

    } else this->elapsed_+=dt;

    if ( this->list_.empty() ) return;

    std::forward_list<std::unique_ptr<Buff>>::iterator curr = this->list_.begin();
    std::forward_list<std::unique_ptr<Buff>>::iterator prev = this->list_.before_begin();

    while ( curr != this->list_.end() ) {
        (*curr)->update( dt );

        if ( (*curr)->status == Buff::Status::OFF ) {
            (*curr)->revert();
            curr = this->list_.erase_after(prev);
            std::cout << "buff [removed]\n";

        } else {
            prev = curr;
            ++curr;
        }
    }
}

void BuffOperator::reset() { this->list_.clear(); }