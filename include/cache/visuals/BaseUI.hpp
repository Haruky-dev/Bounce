#pragma once

#include <engine/features/Progressive.hpp>

class BaseUI {
    public:
    
        virtual void configure( Progressive& prog ) = 0;
        virtual ~BaseUI() = default;
};