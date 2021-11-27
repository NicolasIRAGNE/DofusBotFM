#include <gtest/gtest.h>

#include <map>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Stat.h"
#include "Item.h"

TEST(Item, StatsLineMapConstructor_MinGreaterThanMax)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {15.f, 10.f, 5.f}},
    };
    try {
        DBF::Item item(itemStats);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, StatsLineMapConstructor_MinBelowZeroAndMaxAboveZero)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {-15.f, 10.f, 5.f}},
    };
    try {
        DBF::Item item(itemStats);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, StatsLineMapConstructor_StatBelowZeroAndStatBelowMin)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {-2.f, -1.f, -5.f}},
    };
    try {
        DBF::Item item(itemStats);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, StatsLineMapConstructor_StatAboveMaxAndStatAboveMaximumLineDensity)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {20.f, 80.f, 102.f}},
    };
    try {
        DBF::Item item(itemStats);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, StatsLineMapConstructor_ValidStatLinesMap)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {15.f, 20.f, 5.f}},
        {DBF::Stat::Ine, {15.f, 20.f, 17.f}},
        {DBF::Stat::DoPerDi, {1.f, 2.f, 0.f}},
        {DBF::Stat::ReAir, {10.f, 15.f, 20.f}},
    };
    try {
        DBF::Item item(itemStats);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).current == 5.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).current == 17.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).min == 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).max == 2.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).min == 10.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).max == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).current == 20.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, JsonConstructor_StatsNotAnObject)
{
    const auto json = R"(
    {
        "stats": 5
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_StatNameDoNotExist)
{
    const auto json = R"(
    {
        "stats": {
            "toto": {
                "min": 15,
                "max": 20,
                "value": 5
            }
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_StatNameIsNotAnObject)
{
    const auto json = R"(
    {
        "stats": {
            "Age": 5
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_StatLineMinNotANumber)
{
    const auto json = R"(
    {
        "stats": {
            "ine": {
                "min": "toto",
                "max": 0,
                "value": 0
            }
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_StatLineMaxNotANumber)
{
    const auto json = R"(
    {
        "stats": {
            "Age": {
                "min": 15,
                "max": "toto",
                "value": 0
            }
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_StatLineValueNotANumber)
{
    const auto json = R"(
    {
        "stats": {
            "Age": {
                "min": 0,
                "max": 0,
                "value": "toto"
            }
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonConstructor_ValidJson)
{
    const auto json = R"(
    {
        "stats":
        {
            "Age": {"min" : 15, "max" : 20, "value" : 5},
            "Ine": {"min" : 15, "max" : 20, "value" : 17},
            "DoPerDi": {"min" : 1, "max" : 2, "value" : 0},
            "ReAir": {"min" : 10, "max" : 15, "value" : 20}
        }
    })"_json;
    try {
        DBF::Item item(json);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).current == 5.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).current == 17.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).min == 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).max == 2.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).min == 10.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).max == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).current == 20.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, JsonFileConstructor_FileNotFound)
{
    const std::string jsonFile = "toto";
    try {
        DBF::Item item(jsonFile);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, JsonFileConstructor_ValidFile)
{
    const auto json = R"(
    {
        "stats":
        {
            "Age": {"min" : 15, "max" : 20, "value" : 5},
            "Ine": {"min" : 15, "max" : 20, "value" : 17},
            "DoPerDi": {"min" : 1, "max" : 2, "value" : 0},
            "ReAir": {"min" : 10, "max" : 15, "value" : 20}
        }
    })"_json;

    {
        std::ofstream file("test.json");
        file << json;
    }

    const std::string jsonFile = "test.json";
    try {
        DBF::Item item(jsonFile);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).current == 5.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).min == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).max == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).current == 17.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).min == 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).max == 2.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).min == 10.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).max == 15.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).current == 20.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, GetStat_NonExistentStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {0.f, 10.f, 5.f}},
        {DBF::Stat::Ine, {20.f, 30.f, 10.f}},
        {DBF::Stat::Cri, {0.f, 1.f, 2.f}},
        {DBF::Stat::RetPa, {-5.f, -2.f, -3.f}}};

    try {
        DBF::Item item(itemStats);

        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).max == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoPerDi).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).max == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::ReAir).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::GaPa).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::GaPa).max == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::GaPa).current == 0.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::RePa).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RePa).max == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RePa).current == 0.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, GetStat_ExistentStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {0.f, 10.f, 5.f}},
        {DBF::Stat::Ine, {20.f, 30.f, 10.f}},
        {DBF::Stat::Cri, {0.f, 1.f, 2.f}},
        {DBF::Stat::RetPa, {-5.f, -2.f, -3.f}}};
    try {
        DBF::Item item(itemStats);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).max == 10.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).current == 5.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).min == 20.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).max == 30.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).current == 10.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::Cri).min == 0.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cri).max == 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cri).current == 2.f);

        ASSERT_TRUE(item.GetStat(DBF::Stat::RetPa).min == -5.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RetPa).max == -2.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RetPa).current == -3.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, UpdateStat_NonExistentAndInvalidStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {20.f, 80.f, 60.f}},
    };

    try {
        DBF::Item item(itemStats);
    } catch (...) {
        ASSERT_TRUE(false);
    }

    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::Ine, -1.f);
        ASSERT_TRUE(false);
    } catch (...) {
    }

    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::Ine, 102.f);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, UpdateStat_ExistentAndInvalidStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {20.f, 80.f, 60.f}},
    };
    try {
        DBF::Item item(itemStats);
    } catch (...) {
        ASSERT_TRUE(false);
    }

    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::Age, -61.f);
        ASSERT_TRUE(false);
    } catch (...) {
    }

    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::Age, 42.f);
        ASSERT_TRUE(false);
    } catch (...) {
    }
}

TEST(Item, UpdateStat_NonExistentAndValidStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {20.f, 80.f, 60.f}},
        {DBF::Stat::Ine, {-80.f, -20.f, -30.f}},
        {DBF::Stat::Cri, {2.f, 8.f, 6.f}},
    };
    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::DoAir, 3.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoAir).current == 3.f);

        item.UpdateStat(DBF::Stat::RePerDi, 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RePerDi).current == 1.f);

        item.UpdateStat(DBF::Stat::Cha, 101.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cha).current == 101.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, UpdateStat_ExistentAndValidStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {20.f, 80.f, 60.f}},
        {DBF::Stat::Ine, {-80.f, -20.f, -30.f}},
        {DBF::Stat::Cri, {2.f, 8.f, 6.f}},
    };
    try {
        DBF::Item item(itemStats);

        item.UpdateStat(DBF::Stat::Age, -60.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age).current == 0.f);

        item.UpdateStat(DBF::Stat::Ine, -50.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine).current == -80.f);

        item.UpdateStat(DBF::Stat::Cri, 4.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cri).current == 10.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST(Item, ToJson_Valid)
{
    const auto jsonString = DBF::Item::GetJsonFormatExemple();
    const auto json = nlohmann::json::parse(jsonString);

    try {
        DBF::Item item(json);

        const auto jsonFromItem = item.ToJson();
        ASSERT_TRUE(jsonFromItem == json);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}
