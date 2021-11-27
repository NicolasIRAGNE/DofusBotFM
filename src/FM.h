#pragma once

#include <map>
#include <memory>

#include "Item.h"

namespace DBF {

class RuneApplicationInterface;
class Stat;

class FM {
public:
    FM(const DBF::Item& item,
       const std::map<Stat, float>& wantedStats,
       const std::shared_ptr<RuneApplicationInterface>&
           runeApplicationInterface);

    void Run();

private:
    DBF::Item m_Item;
    const std::map<Stat, float> m_WantedStats;
    const std::shared_ptr<RuneApplicationInterface> m_RuneApplicationInterface;
};

} // namespace DBF
