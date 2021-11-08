#include <gtest/gtest.h>

#include <map>

#include "Stat.h"
#include "Item.h"

TEST(Item, Creation)
{
    std::map<DBF::Stat, float> emptyMap;
    DBF::Item item(emptyMap);

    ASSERT_TRUE(true);
}
