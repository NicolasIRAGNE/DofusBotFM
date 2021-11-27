#pragma once

#include <map>
#include <string_view>
#include <string>

#include <nlohmann/json_fwd.hpp>
#include <Stat.h>

#include "ItemJsonFormatExemple.h"

namespace nm = nlohmann;

namespace DBF {

class Stat;

class Item {
public:
    struct StatLine {
        float min;
        float max;
        float current;

        auto operator<=>(const StatLine& statLine) const = default;
    };

public:
    Item(const std::map<Stat, StatLine>& stats);
    Item(const nm::json& json);
    Item(const std::string& jsonFile);

    const StatLine& GetStat(Stat stat) const;
    void UpdateStat(Stat stat, float value);
    void UpdateStats(const std::map<Stat, float>& stats);
    nm::json ToJson() const;

    auto operator<=>(const Item& item) const = default;

    constexpr static const std::string_view GetJsonFormatExemple()
    {
        return kItemJsonFormatExemple;
    }

private:
    std::map<Stat, StatLine> m_Stats;
};

} // namespace DBF
