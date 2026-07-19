#include <engine/io/Process.hpp>


Process::Process() :
__p(Process::Action::NONE, SFX::Type::NONE) {}

Process::Process( const Process::Action A, const SFX::Type S )
: __p(A, S) {}


Process::Action Process::act() const { return this->__p.first; }
SFX::Type       Process::sfx() const { return this->__p.second; }