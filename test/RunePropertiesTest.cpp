#include <gtest/gtest.h>

#include "RunesList.h"
#include "RuneProperties.h"

TEST(RuneProperties, ListCheck)
{
    int nbRunes = static_cast<int>(DBF::Rune::GaPa) + 1;
    for (int i = 0; i < nbRunes; i++) {
        auto rune = static_cast<DBF::Rune>(i);
        auto propreties = DBF::GetRuneProperties(rune);
    }

    ASSERT_TRUE(true);
}
