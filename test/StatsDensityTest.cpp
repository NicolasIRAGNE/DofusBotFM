#include <gtest/gtest.h>

#include "Stat.h"
#include "StatsDensity.h"

TEST(StatsDensity, ListCheck)
{
    auto cb = [](const DBF::Stat& rune) {
        auto density = DBF::GetStatDensity(rune);
    };
    DBF::Stat::Foreach(cb);

    ASSERT_TRUE(true);
}
