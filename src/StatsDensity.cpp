#include "StatsDensity.h"

#include <assert.h>
#include <unordered_map>

#include "StatsList.h"

namespace DBF {

static const std::unordered_map<Stat, float> densityMap = {
    {Stat::Fo, 1.f},          {Stat::Ine, 1.f},      {Stat::Cha, 1.f},
    {Stat::Age, 1.f},         {Stat::Vi, 0.2f},      {Stat::Ini, 0.1f},
    {Stat::Sa, 3.f},          {Stat::Prospe, 3.f},   {Stat::Pui, 2.f},
    {Stat::ReTerre, 2.f},     {Stat::ReFeu, 2.f},    {Stat::ReEau, 2.f},
    {Stat::ReAir, 2.f},       {Stat::ReNeutre, 2.f}, {Stat::RePerTerre, 6.f},
    {Stat::RePerFeu, 6.f},    {Stat::RePerEau, 6.f}, {Stat::RePerAir, 6.f},
    {Stat::RePerNeutre, 6.f}, {Stat::RePou, 2.f},    {Stat::ReCri, 2.f},
    {Stat::RePa, 7.f},        {Stat::RePm, 7.f},     {Stat::RetPa, 7.f},
    {Stat::RetPm, 7.f},       {Stat::Pod, 0.25f},    {Stat::Tac, 4.f},
    {Stat::Fui, 4.f},         {Stat::Do, 20.f},      {Stat::DoTerre, 5.f},
    {Stat::DoNeutre, 5.f},    {Stat::DoFeu, 5.f},    {Stat::DoAir, 5.f},
    {Stat::DoEau, 5.f},       {Stat::DoPou, 5.f},    {Stat::DoCri, 5.f},
    {Stat::Pi, 5.f},          {Stat::DoPerDi, 15.f}, {Stat::DoPerAr, 15.f},
    {Stat::DoPerSo, 15.f},    {Stat::DoPerMe, 15.f}, {Stat::RePerMe, 15.f},
    {Stat::RePerDi, 15.f},    {Stat::PiPer, 2.f},    {Stat::So, 10.f},
    {Stat::Cri, 10.f},        {Stat::DoRen, 10.f},   {Stat::Invo, 30.f},
    {Stat::Po, 51.f},         {Stat::GaPm, 90.f},    {Stat::GaPa, 100.f},
};

float GetStatDensity(Stat stat)
{
    auto it = densityMap.find(stat);
    assert(it != densityMap.end());

    const auto& density = it->second;

    return density;
}

} // namespace DBF
