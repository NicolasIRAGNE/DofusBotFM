#include <gtest/gtest.h>

#include <map>

#include "Stat.h"
#include "Item.h"

TEST(Item, Constructor_MinGreaterThanMax)
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

TEST(Item, Constructor_MinBelowZeroAndMaxAboveZero)
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

TEST(Item, Constructor_StatBelowZeroAndStatBelowMin)
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

TEST(Item, Constructor_StatAboveMaxAndStatAboveMaximumLineDensity)
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

TEST(Item, GetStat_NonExistentStat)
{
    std::map<DBF::Stat, DBF::Item::StatLine> itemStats = {
        {DBF::Stat::Age, {0.f, 10.f, 5.f}},
        {DBF::Stat::Ine, {20.f, 30.f, 10.f}},
        {DBF::Stat::Cri, {0.f, 1.f, 2.f}},
        {DBF::Stat::RetPa, {-5.f, -2.f, -3.f}}};
    try {
        DBF::Item item(itemStats);

        float doAir = item.GetStat(DBF::Stat::DoAir);
        ASSERT_TRUE(doAir == 0.f);

        float gaPa = item.GetStat(DBF::Stat::GaPa);
        ASSERT_TRUE(gaPa == 0.f);

        float reAirPa = item.GetStat(DBF::Stat::ReAir);
        ASSERT_TRUE(reAirPa == 0.f);
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

        float ine = item.GetStat(DBF::Stat::Ine);
        ASSERT_TRUE(ine == 10.f);

        float cri = item.GetStat(DBF::Stat::Cri);
        ASSERT_TRUE(cri == 2.f);

        float retPa = item.GetStat(DBF::Stat::RetPa);
        ASSERT_TRUE(retPa == -3.f);
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
        ASSERT_TRUE(item.GetStat(DBF::Stat::DoAir) == 3.f);

        item.UpdateStat(DBF::Stat::RePerDi, 1.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::RePerDi) == 1.f);

        item.UpdateStat(DBF::Stat::Cha, 101.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cha) == 101.f);
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
        ASSERT_TRUE(item.GetStat(DBF::Stat::Age) == 0.f);

        item.UpdateStat(DBF::Stat::Ine, -50.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Ine) == -80.f);

        item.UpdateStat(DBF::Stat::Cri, 4.f);
        ASSERT_TRUE(item.GetStat(DBF::Stat::Cri) == 10.f);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}
