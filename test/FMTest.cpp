#include <gtest/gtest.h>

#include <memory>

#include <nlohmann/json.hpp>

#include "mock/MockRuneApplication.h"

#include "Item.h"
#include "Stat.h"
#include "Rune.h"
#include "RuneProperties.h"
#include "FM.h"

TEST(FM, Constructor_NullRuneApplicationInterface)
{
    DBF::Item item(nm::json::parse(DBF::Item::GetJsonFormatExemple()));
    std::map<DBF::Stat, float> wantedStats;

    try {
        DBF::FM fm(item, wantedStats, nullptr);
        FAIL();
    } catch (...) {
    }
}

TEST(FM, Constructor_Valid)
{
    DBF::Item item(nm::json::parse(DBF::Item::GetJsonFormatExemple()));
    std::map<DBF::Stat, float> wantedStats;
    auto runeApplication = std::make_shared<MockRuneApplication>();

    try {
        DBF::FM fm(item, wantedStats, runeApplication);
    } catch (...) {
        FAIL();
    }
}

TEST(FM, Run_BasicItem)
{
    const auto json =
        R"({
            "stats":
            {
                "Ine":
                {
                    "min": 40,
                    "max": 70,
                    "value": 50
                },
                "Cri":
                {
                    "min": 4,
                    "max": 7,
                    "value": 0
                },
                "DoAir":
                {
                    "min": 10,
                    "max": 15,
                    "value": 20
                }
            }
        })"_json;

    try {
        DBF::Item item(json);
        std::map<DBF::Stat, float> wantedStats = {
            {DBF::Stat::Ine, 70},
            {DBF::Stat::Cri, 7},
            {DBF::Stat::DoAir, 15},
            {DBF::Stat::DoNeutre, 2},
        };

        auto runeApplication = std::make_shared<MockRuneApplication>();
        ON_CALL(*runeApplication, ApplyRune(testing::_))
            .WillByDefault([](const DBF::Rune& rune) {
                const auto& runeProperties = DBF::GetRuneProperties(rune);
                std::map<DBF::Stat, float> stats = {{runeProperties.stat, 1}};
                return stats;
            });

        EXPECT_CALL(*runeApplication, ApplyRune(DBF::Rune(DBF::Rune::Ine)))
            .Times(20);
        EXPECT_CALL(*runeApplication, ApplyRune(DBF::Rune(DBF::Rune::Cri)))
            .Times(7);
        EXPECT_CALL(*runeApplication, ApplyRune(DBF::Rune(DBF::Rune::DoNeutre)))
            .Times(2);

        DBF::FM fm(item, wantedStats, runeApplication);
        fm.Run();

    } catch (...) {
        FAIL();
    }
}
