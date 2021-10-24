#pragma once

#include <map>

#include "StatsList.h"

namespace DBF {

class Item {
public:
    Item(const std::map<Stat, float>& stats);

private:
    std::map<Stat, float> m_Stats;
};

} // namespace DBF
