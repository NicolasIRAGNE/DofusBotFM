#pragma once

#include <string_view>

namespace DBF {

constexpr std::string_view kItemJsonFormatExemple =
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
    })";

} // namespace DBF
