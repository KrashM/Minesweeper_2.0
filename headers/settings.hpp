#pragma once

#include "debug.hpp"
#include "out_of_bounds.hpp"
#include <cstdint>

typedef unsigned char u_char;

enum class difficulty{

    EASY,
    MEDIUM,
    HARD

};

class settings{

public:
    settings(settings const &) = delete;
    settings(settings &&) = delete;

    settings &operator =(settings const &) = delete;
    settings &operator =(settings &&) = delete;

    static settings &get_instance();

    void set_difficulty(difficulty const);

    uint16_t const get_height() const;
    uint16_t const get_width() const;
    uint16_t const get_bombs() const;

public:
    static constexpr uint16_t _cell_size = 16;
    static constexpr uint16_t _frame_duration = 16667;

private:
    settings() = default;

private:
    uint16_t _height, _width, _bombs;

};

#ifdef DEBUG

TEST_CASE("Testing singleton property"){

    CHECK_EQ(&settings::get_instance(), &settings::get_instance());

}

TEST_SUITE("Testing different difficulties"){

    TEST_CASE("Testing easy difficulty"){

        settings &instance = settings::get_instance();
        instance.set_difficulty(difficulty::EASY);

        CHECK_EQ(instance.get_width(), 9);
        CHECK_EQ(instance.get_height(), 9);
        CHECK_EQ(instance.get_bombs(), 10);

    }

    TEST_CASE("Testing medium defficulty"){
        
        settings &instance = settings::get_instance();
        instance.set_difficulty(difficulty::MEDIUM);

        CHECK_EQ(instance.get_width(), 16);
        CHECK_EQ(instance.get_height(), 16);
        CHECK_EQ(instance.get_bombs(), 40);

    }

    TEST_CASE("Testing hard difficulty"){

        settings &instance = settings::get_instance();
        instance.set_difficulty(difficulty::HARD);

        CHECK_EQ(instance.get_width(), 30);
        CHECK_EQ(instance.get_height(), 16);
        CHECK_EQ(instance.get_bombs(), 99);

    }

}

TEST_CASE("Testing cell size getter"){

    CHECK_EQ(settings::get_instance().get_cell_size(), 16);

}

#endif