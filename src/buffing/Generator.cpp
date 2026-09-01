#include <buffing/Generator.hpp>

#include <tools/Math.hpp>


std::unique_ptr<Buff> Generator::yield() {
    // const Buff::Type T = static_cast<Buff::Type>( Math::randi( 0, (int) Buff::Type::_size ) );
    const Buff::Type T = Buff::Type::Freeze;

    switch (T) {
        case Buff::Type::Freeze:
            return std::make_unique<Freeze>(Buff::Target::P1 );

        default:
            throw std::runtime_error("Invalid 'value' given at 'Generator' for 'T'");
    }
    // return Freeze(Buff::Target::P1, Buff::Status::ON, 200);
}
