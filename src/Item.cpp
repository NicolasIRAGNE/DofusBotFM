#include "Item.h"

#include <stdexcept>
#include <format>

#include "Stat.h"
#include "StatsDensity.h"

namespace {

void TestStatLineValidity(DBF::Stat stat, float min, float max, float current)
{
    if (min > max) {
        throw std::invalid_argument(
            std::format("Error for {} : min ({}) >  max ({})", stat, min, max));
    }

    if (min < 0 && max >= 0) {
        throw std::invalid_argument(std::format(
            "Error for {} : min ({}) < 0 and max ({}) >= 0", stat, min, max));
    }

    if (current < 0 && current < min) {
        throw std::invalid_argument(std::format(
            "Error for {} : current ({}) < 0 and current ({}) < min ({})",
            stat,
            min,
            max));
    }

    const auto lineDensity = GetStatDensity(stat) * current;
    constexpr float maxLineDensity = 101.f;
    if (current > max && lineDensity > maxLineDensity) {
        throw std::invalid_argument(std::format(
            "Error for {} : current ({}) > max and lineDensity ({}) > maxLineDensity ({})",
            stat,
            lineDensity,
            maxLineDensity));
    }
}

} // namespace

namespace DBF {

Item::Item(const std::map<Stat, StatLine>& stats) : m_Stats(stats)
{
    for (const auto& pair : m_Stats) {
        const auto& stat = pair.first;
        const auto& statLine = pair.second;
        const auto& min = statLine.min;
        const auto& max = statLine.max;
        const auto& current = statLine.current;

        ::TestStatLineValidity(stat, min, max, current);
    }
}

float Item::GetStat(Stat stat)
{
    const auto it = m_Stats.find(stat);
    if (it == m_Stats.end()) {
        return 0.f;
    }

    const auto& statLine = it->second;

    return statLine.current;
}

void Item::UpdateStat(Stat stat, float value)
{
    const auto it = m_Stats.find(stat);
    if (it == m_Stats.end()) {
        ::TestStatLineValidity(stat, 0.f, 0.f, value);
        m_Stats.emplace(
            stat, StatLine {.min = 0.f, .max = 0.f, .current = value});
        return;
    }

    auto& statLine = it->second;
    const auto& min = statLine.min;
    const auto& max = statLine.max;
    auto& current = statLine.current;

    ::TestStatLineValidity(stat, min, max, current + value);
    current += value;
}

} // namespace DBF
