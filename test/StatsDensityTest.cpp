#include <gtest/gtest.h>

#include "Stat.h"
#include "StatsDensity.h"

TEST(StatsDensity, GetStatDensity_InvalidValue)
{
    try {
        const auto stat = static_cast<DBF::Stat::StatImpl>(1568);
        DBF::GetStatDensity(stat);
        FAIL();
    } catch (...) {
    }
}

TEST(StatsDensity, GetStatDensity_AllValidValues)
{
    auto cb = [](const DBF::Stat& rune) {
        try {
            DBF::GetStatDensity(rune);
        } catch (...) {
            FAIL();
        }
    };
    DBF::Stat::Foreach(cb);
}
