#pragma once

#include <map>

namespace DBF {

class Stat;

class Item {
public:
    Item(const std::map<Stat, float>& stats);

private:
    std::map<Stat, float> m_Stats;
};

} // namespace DBF
