#pragma once

#include "StatsList.h"

namespace DBF {

enum class Rune;

struct RuneProperties {
    Stat stat;
    float factor;
};

RuneProperties GetRuneProperties(const Rune& rune);

} // namespace DBF
