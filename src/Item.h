#pragma once

#include <map>

namespace DBF {

class Stat;

class Item {
public:
    struct StatLine {
        float min;
        float max;
        float current;
    };

public:
    Item(const std::map<Stat, StatLine>& stats);

    float GetStat(Stat stat);
    void UpdateStat(Stat stat, float value);

private:
    std::map<Stat, StatLine> m_Stats;
};

} // namespace DBF
