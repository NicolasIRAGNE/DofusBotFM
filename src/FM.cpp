#include "FM.h"

#include "Stat.h"
#include "Rune.h"
#include "StatsRunes.h"
#include "RuneApplicationInterface.h"

namespace DBF {

FM::FM(
    const Item& item,
    const std::map<Stat, float>& wantedStats,
    const std::shared_ptr<RuneApplicationInterface>& runeApplicationInterface)
    : m_Item(item)
    , m_WantedStats(wantedStats)
    , m_RuneApplicationInterface(runeApplicationInterface)
{
    if (m_RuneApplicationInterface == nullptr) {
        throw std::invalid_argument("RuneApplicationInterface cannot be null");
    }
}

void FM::Run()
{
    while (true) {
        bool statsOk = true;
        for (const auto& [stat, value] : m_WantedStats) {
            if (m_Item.GetStat(stat).current >= value) {
                continue;
            }

            statsOk = false;

            while (m_Item.GetStat(stat).current < value) {
                const auto& rune = GetStatRunes(stat)[0];
                const auto statsChanges =
                    m_RuneApplicationInterface->ApplyRune(rune);
                m_Item.UpdateStats(statsChanges);
            }
        }

        if (statsOk) {
            break;
        }
    }
}

} // namespace DBF