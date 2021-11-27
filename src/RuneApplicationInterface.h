#pragma once

#include <map>

namespace DBF {

class Stat;
class Rune;

class RuneApplicationInterface
{
public:
    virtual ~RuneApplicationInterface() = default;

    virtual std::map<Stat, float> ApplyRune(const Rune& rune) = 0;
};

} // namespace DBF
