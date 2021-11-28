#pragma once

#include <vector>

namespace DBF {

class Stat;
class Rune;

const std::vector<Rune>& GetStatRunes(const Stat& stats);

} // namespace DBF
