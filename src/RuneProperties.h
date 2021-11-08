#pragma once

#include "Stat.h"

namespace DBF {

class Rune;

struct RuneProperties {
    Stat stat;
    float factor;
};

RuneProperties GetRuneProperties(const Rune& rune);

} // namespace DBF
