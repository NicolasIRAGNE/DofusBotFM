#include <gtest/gtest.h>

#include "stat.h"
#include "Rune.h"
#include "StatsRunes.h"

TEST(StatsRunes, GetStatRunes_InvalidValue)
{
    try {
        const auto stat = static_cast<DBF::Stat::StatImpl>(1568);
        DBF::GetStatRunes(stat);
        FAIL();
    } catch (...) {
    }
}

TEST(StatsRunes, GetStatRunes_AllValidValues)
{
    auto cb = [](const DBF::Stat& stat) {
        try {
            const auto& runes = DBF::GetStatRunes(stat);
            ASSERT_TRUE(runes.size() > 0);
        } catch (...) {
            FAIL();
        }
    };
    DBF::Stat::Foreach(cb);
}
