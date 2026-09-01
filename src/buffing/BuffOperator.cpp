#include <buffing/BuffOperator.hpp>

#include <tools/Constants.hpp>
#include <buffing/Generator.hpp>


BuffOperator& BuffOperator::inst() {
    static BuffOperator inst;

    return inst;
}

BuffOperator::BuffOperator() :
    period(Constants::buffingPeriod),
    elapsed(sf::Time::Zero),
    lastFire(sf::Time::Zero)
    {}

void BuffOperator::update( const sf::Time& dt ) {
    if ( this->elapsed.asSeconds() >= this->period ) {
        this->elapsed = sf::Time::Zero;
        this->__list.push_front( Generator::yield() );
        this->__list.front()->apply();
        std::cout << "buff [pushed]\n";

    } else this->elapsed+=dt;

    if ( this->__list.empty() ) return;

    std::forward_list<std::unique_ptr<Buff>>::iterator curr = this->__list.begin();
    std::forward_list<std::unique_ptr<Buff>>::iterator prev = this->__list.before_begin();

    while ( curr != this->__list.end() ) {
        (*curr)->update( dt );

        if ( (*curr)->status == Buff::Status::OFF ) {
            (*curr)->revert();
            curr = this->__list.erase_after(prev);
            std::cout << "buff [removed]\n";

        } else {
            prev = curr;
            ++curr;
        }
    }
}