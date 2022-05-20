#pragma once

#include "Types.hpp"

class Settings{

    public:
        Settings(const u_short, const u_short, const u_short);

        const u_short getHeight() const;
        const u_short getWidth() const;
        const u_short getBombs() const;

        static const Settings EASY_8x8;
        static const Settings EASY_9x9;
        static const Settings EASY_10x10;

        static const Settings INTERMEDIATE_14x14;
        static const Settings INTERMEDIATE_15x15;
        static const Settings INTERMEDIATE_16x16;

        static const Settings EXPERT_20x20;
        static const Settings EXPERT_22x22;
        static const Settings EXPERT_24x24;
    
    private:
        u_short _height, _width, _bombs;

};