#include <gtest/gtest.h>

#include "Rune.h"
#include "RuneProperties.h"
#include "StatsDensity.h"

TEST(RuneProperties, GetRuneProperties_InvalidValue)
{
    try {
        const auto rune = static_cast<DBF::Rune::RuneImpl>(1568);
        DBF::GetRuneProperties(rune);
        FAIL();
    } catch (...) {
    }
}

TEST(RuneProperties, GetRuneProperties_AllValidValues)
{
    auto cb = [](const DBF::Rune& rune) {
        try {
            const auto& properties = DBF::GetRuneProperties(rune);
            const auto& stat = properties.stat;
            const auto& factor = properties.factor;
            const auto& density = properties.density;
            const auto statDensity = DBF::GetStatDensity(stat);

            ASSERT_TRUE(density == statDensity * factor);
        } catch (...) {
            FAIL();
        }
    };
    DBF::Rune::Foreach(cb);
}
