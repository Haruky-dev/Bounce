#include <buffing/Generator.hpp>

#include <tools/Math.hpp>
#include <tools/Variables.hpp>


std::unique_ptr<Buff> Generator::yield() {

    switch (Generator::randType({Buff::Type::Freeze, Buff::Type::Invert})) {
        case Buff::Type::Freeze:
            return std::make_unique<Freeze>(
                Generator::randTarget({Buff::Target::P1, Buff::Target::P2}),
                Variables::freezeDuration + Math::randi( 0, Variables::freezeDuration*Variables::offsetPercent, true )
            );

        case Buff::Type::Invert:
            return std::make_unique<Invert>(
                Generator::randTarget({Buff::Target::P1, Buff::Target::P2}),
                // Buff::Target::P1,
                Variables::invertDuration + Math::randi( 0, Variables::invertDuration*Variables::offsetPercent, true )
            );

        default:
            throw std::runtime_error("Invalid 'value' given at 'Generator' for 'T'");
    }
}


Buff::Target Generator::randTarget( const std::initializer_list<Buff::Target> applicables ) {
    return *( applicables.begin() + Math::randi(0, applicables.size()-1) );
}
Buff::Type Generator::randType( const std::initializer_list<Buff::Type> applicables ) {
    return *( applicables.begin() + Math::randi(0, applicables.size()-1) );
}
