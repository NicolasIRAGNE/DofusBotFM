#include <gtest/gtest.h>

#include "Stat.h"
#include "StatsDensity.h"

TEST(StatsDensity, GetStatDensity_InvalidValue)
{
    try {
        const auto stat = static_cast<DBF::Stat::StatImpl>(1568);
        DBF::GetStatDensity(stat);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(StatsDensity, GetStatDensity_AllValidValues)
{
    auto cb = [](const DBF::Stat& rune) {
        try {
            auto density = DBF::GetStatDensity(rune);
        } catch (...) {
            ASSERT_TRUE(false);
        }
    };
    DBF::Stat::Foreach(cb);

    ASSERT_TRUE(true);
}
