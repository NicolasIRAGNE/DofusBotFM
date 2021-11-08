#include "Item.h"

#include "Stat.h"

namespace DBF {

Item::Item(const std::map<Stat, float>& stats) : m_Stats(stats)
{
}

} // namespace DBF
