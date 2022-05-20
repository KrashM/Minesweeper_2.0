#include "../headers/Settings.hpp"

#define EASY_BOMBS 10
#define INTERMEDIATE_BOMBS 40
#define EXPERT_BOMBS 99

enum EASY_DIMS{ EIGHT = 8, NINE, TEN };
enum INTERMEDIATE_DIMS{ FOURTEEN = 14, FIFTEEN, SIXTEEN };
enum EXPERT_DIMS{ TWENTY = 20, TWENTY_TWO = 22, TWENTY_FOUR = 24 };

const Settings Settings::EASY_8x8(EASY_DIMS::EIGHT, EASY_DIMS::EIGHT, EASY_BOMBS);
const Settings Settings::EASY_9x9(EASY_DIMS::NINE, EASY_DIMS::NINE, EASY_BOMBS);
const Settings Settings::EASY_10x10(EASY_DIMS::TEN, EASY_DIMS::TEN, EASY_BOMBS);
const Settings Settings::INTERMEDIATE_14x14(INTERMEDIATE_DIMS::FOURTEEN, INTERMEDIATE_DIMS::FOURTEEN, INTERMEDIATE_BOMBS);
const Settings Settings::INTERMEDIATE_15x15(INTERMEDIATE_DIMS::FIFTEEN, INTERMEDIATE_DIMS::FIFTEEN, INTERMEDIATE_BOMBS);
const Settings Settings::INTERMEDIATE_16x16(INTERMEDIATE_DIMS::SIXTEEN, INTERMEDIATE_DIMS::SIXTEEN, INTERMEDIATE_BOMBS);
const Settings Settings::EXPERT_20x20(EXPERT_DIMS::TWENTY, EXPERT_DIMS::TWENTY, EXPERT_BOMBS);
const Settings Settings::EXPERT_22x22(EXPERT_DIMS::TWENTY_TWO, EXPERT_DIMS::TWENTY_TWO, EXPERT_BOMBS);
const Settings Settings::EXPERT_24x24(EXPERT_DIMS::TWENTY_FOUR, EXPERT_DIMS::TWENTY_FOUR, EXPERT_BOMBS);

Settings::Settings(const u_short height, const u_short width, const u_short bombs): _height(height), _width(width), _bombs(bombs){}

const u_short Settings::getHeight() const{ return this -> _height; }
const u_short Settings::getWidth() const{ return this -> _width; }
const u_short Settings::getBombs() const{ return this -> _bombs; }