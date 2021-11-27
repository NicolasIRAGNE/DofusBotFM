#include "StatsRunes.h"

#include <map>
#include <vector>

#include "Stat.h"
#include "Rune.h"
#include "RuneProperties.h"

namespace DBF {

static std::map<Stat, std::vector<Rune>> kStatsRunes;

static const std::map<Stat, std::vector<Rune>>& SetupStatsRunes()
{
    Rune::Foreach([](const Rune& rune)
    {
        const auto& runeProperties = GetRuneProperties(rune);
        kStatsRunes[runeProperties.stat].push_back(rune);
    });

    return kStatsRunes;
}

const std::vector<Rune>& GetStatRunes(const Stat& stat)
{
    static auto statsRunes = SetupStatsRunes();

    auto it = statsRunes.find(stat);
    if (it == statsRunes.end()) {
        throw std::invalid_argument("Unknown stat");
    }

    const auto& runes = it->second;
    return runes;
}

} // namespace DBF
