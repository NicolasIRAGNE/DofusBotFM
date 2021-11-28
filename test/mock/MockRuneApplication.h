#pragma once

#include <gmock/gmock.h>

#include <map>

#include "Stat.h"
#include "Rune.h"
#include "RuneApplicationInterface.h"

class MockRuneApplication : public DBF::RuneApplicationInterface {
public:
    MOCK_METHOD(
        (std::map<DBF::Stat, float>),
        ApplyRune,
        (const DBF::Rune& rune),
        (final));
};
