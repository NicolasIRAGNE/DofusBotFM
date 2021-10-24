#include <gtest/gtest.h>

#include "StatsList.h"
#include "StatsDensity.h"

TEST(StatsDensity, ListCheck)
{
    int nbStats = static_cast<int>(DBF::Stat::GaPa) + 1;
    for (int i = 0; i < nbStats; i++) {
        auto stat = static_cast<DBF::Stat>(i);
        auto density = DBF::GetStatDensity(stat);
    }

    ASSERT_TRUE(true);
}
