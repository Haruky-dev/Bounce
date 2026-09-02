#include <buffing/Generator.hpp>

#include <tools/Math.hpp>
#include <tools/Constants.hpp>


std::unique_ptr<Buff> Generator::yield() {
    // const Buff::Type T = static_cast<Buff::Type>( Math::randi( 0, (int) Buff::Type::_size - 1) );
    const Buff::Type T = Buff::Type::Freeze;

    switch (T) {
        case Buff::Type::Freeze:
            return std::make_unique<Freeze>(
                Generator::randTarget({Buff::Target::P1, Buff::Target::P2}),
                Constants::freezeDuration + Math::randi( 0, Constants::freezeDuration*Constants::offsetPercent, true )
            );

        default:
            throw std::runtime_error("Invalid 'value' given at 'Generator' for 'T'");
    }
}


Buff::Target Generator::randTarget( const std::initializer_list<Buff::Target> applicables ) {
    return *( applicables.begin() + Math::randi(0, applicables.size()-1) );
}
