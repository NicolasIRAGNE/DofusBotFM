#include "Item.h"

#include <stdexcept>
#include <format>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Stat.h"
#include "StatsDensity.h"

namespace {

void TestStatLineValidity(DBF::Stat stat, float min, float max, float current)
{
    if (min > max) {
        throw std::invalid_argument(
            std::format("Error for {} : min ({}) >  max ({})", stat, min, max));
    }

    if (min < 0 && max >= 0) {
        throw std::invalid_argument(std::format(
            "Error for {} : min ({}) < 0 and max ({}) >= 0", stat, min, max));
    }

    if (current < 0 && current < min) {
        throw std::invalid_argument(std::format(
            "Error for {} : current ({}) < 0 and current ({}) < min ({})",
            stat,
            min,
            max));
    }

    const auto lineDensity = GetStatDensity(stat) * current;
    constexpr float maxLineDensity = 101.f;
    if (current > max && lineDensity > maxLineDensity) {
        throw std::invalid_argument(std::format(
            "Error for {} : current ({}) > max and lineDensity ({}) > maxLineDensity ({})",
            stat,
            lineDensity,
            maxLineDensity));
    }
}

std::map<DBF::Stat, DBF::Item::StatLine> JsonToStatLineMap(const nm::json& json)
{
    const auto statsIt = json.find("stats");
    if (statsIt == json.end() || !statsIt->is_object()) {
        throw std::invalid_argument(
            "Invalid json : \"stats\" is not an object");
    }

    std::map<DBF::Stat, DBF::Item::StatLine> statLineMap;
    const auto& stats = *statsIt;
    for (const auto& [key, statLine] : stats.items()) {
        if (!statLine.is_object()) {
            throw std::invalid_argument(
                "Invalid json : \"stats\" is not an object");
        }

        const auto minIt = statLine.find("min");
        if (minIt == statLine.end() || !minIt->is_number()) {
            throw std::invalid_argument(
                "Invalid json : \"min\" is not a number");
        }

        const auto maxIt = statLine.find("max");
        if (maxIt == statLine.end() || !maxIt->is_number()) {
            throw std::invalid_argument(
                "Invalid json : \"max\" is not a number");
        }

        const auto valueIt = statLine.find("value");
        if (valueIt == statLine.end() || !valueIt->is_number()) {
            throw std::invalid_argument(
                "Invalid json : \"value\" is not a number");
        }

        const DBF::Stat stat = key;
        DBF::Item::StatLine line;
        line.min = minIt->get<float>();
        line.max = maxIt->get<float>();
        line.current = valueIt->get<float>();

        statLineMap.emplace(stat, line);
    }

    return statLineMap;
}

nm::json StatLineMapToJson(std::map<DBF::Stat, DBF::Item::StatLine> stats)
{
    nm::json values;
    for (const auto& [stat, statLine] : stats) {
        nm::json statJson;
        statJson["min"] = statLine.min;
        statJson["max"] = statLine.max;
        statJson["value"] = statLine.current;
        values[std::string(stat.ToString())] = std::move(statJson);
    }

    nm::json json;
    json["stats"] = std::move(values);

    return json;
}

const nm::json FileToJson(const std::string& jsonFile)
{
    std::ifstream fileStream(jsonFile);
    nm::json json = nm::json::parse(fileStream);

    return json;
}

} // namespace

namespace DBF {

Item::Item(const std::map<Stat, StatLine>& stats) : m_Stats(stats)
{
    for (const auto& pair : m_Stats) {
        const auto& stat = pair.first;
        const auto& statLine = pair.second;
        const auto& min = statLine.min;
        const auto& max = statLine.max;
        const auto& current = statLine.current;

        ::TestStatLineValidity(stat, min, max, current);
    }
}

Item::Item(const nm::json& json) : Item(JsonToStatLineMap(json))
{
}

Item::Item(const std::string& jsonFile) : Item(FileToJson(jsonFile))
{
}

const Item::StatLine& Item::GetStat(Stat stat) const
{
    const auto it = m_Stats.find(stat);
    if (it == m_Stats.end()) {
        static const StatLine emptyStatLine {0.f, 0.f, 0.f};
        return emptyStatLine;
    }

    const auto& statLine = it->second;

    return statLine;
}

void Item::UpdateStat(Stat stat, float value)
{
    const auto it = m_Stats.find(stat);
    if (it == m_Stats.end()) {
        ::TestStatLineValidity(stat, 0.f, 0.f, value);
        m_Stats.emplace(
            stat, StatLine {.min = 0.f, .max = 0.f, .current = value});
        return;
    }

    auto& statLine = it->second;
    const auto& min = statLine.min;
    const auto& max = statLine.max;
    auto& current = statLine.current;

    ::TestStatLineValidity(stat, min, max, current + value);
    current += value;
}

nm::json Item::ToJson() const
{
    return StatLineMapToJson(m_Stats);
}

} // namespace DBF
