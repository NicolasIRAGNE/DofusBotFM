#include <gtest/gtest.h>

#include "Rune.h"
#include "RuneProperties.h"

TEST(RuneProperties, ListCheck)
{
    auto cb = [](const DBF::Rune& rune) {
        auto propreties = DBF::GetRuneProperties(rune);
    };
    DBF::Rune::Foreach(cb);

    ASSERT_TRUE(true);
}
