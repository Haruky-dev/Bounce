#include <buffing/BuffOperator.hpp>

#include <tools/Variables.hpp>
#include <buffing/Generator.hpp>


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
        std::cout << "buff [pushed]\n";

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