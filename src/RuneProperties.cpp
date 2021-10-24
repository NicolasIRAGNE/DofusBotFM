#include "RuneProperties.h"

#include <assert.h>
#include <unordered_map>

#include "RunesList.h"

namespace DBF {

static const std::unordered_map<Rune, RuneProperties> propertiesMap = {
    {Rune::Fo, {Stat::Fo, 1.f}},
    {Rune::PaFo, {Stat::Fo, 3.f}},
    {Rune::RaFo, {Stat::Fo, 10.f}},
    {Rune::Ine, {Stat::Ine, 1.f}},
    {Rune::PaIne, {Stat::Ine, 3.f}},
    {Rune::RaIne, {Stat::Ine, 10.f}},
    {Rune::Cha, {Stat::Cha, 1.f}},
    {Rune::PaCha, {Stat::Cha, 3.f}},
    {Rune::RaCha, {Stat::Cha, 10.f}},
    {Rune::Age, {Stat::Age, 1.f}},
    {Rune::PaAge, {Stat::Age, 3.f}},
    {Rune::RaAge, {Stat::Age, 10.f}},
    {Rune::Vi, {Stat::Vi, 5.f}},
    {Rune::PaVi, {Stat::Vi, 15.f}},
    {Rune::RaVi, {Stat::Vi, 50.f}},
    {Rune::Ini, {Stat::Ini, 10.f}},
    {Rune::PaIni, {Stat::Ini, 30.f}},
    {Rune::RaIni, {Stat::Ini, 100.f}},
    {Rune::Sa, {Stat::Sa, 1.f}},
    {Rune::PaSa, {Stat::Sa, 3.f}},
    {Rune::RaSa, {Stat::Sa, 10.f}},
    {Rune::Prospe, {Stat::Prospe, 1.f}},
    {Rune::PaProspe, {Stat::Prospe, 3.f}},
    {Rune::Pui, {Stat::Pui, 1.f}},
    {Rune::PaPui, {Stat::Pui, 3.f}},
    {Rune::RaPui, {Stat::Pui, 10.f}},
    {Rune::ReTerre, {Stat::ReTerre, 1.f}},
    {Rune::PaReTerre, {Stat::ReTerre, 3.f}},
    {Rune::ReFeu, {Stat::ReFeu, 1.f}},
    {Rune::PaReFeu, {Stat::ReFeu, 3.f}},
    {Rune::ReEau, {Stat::ReEau, 1.f}},
    {Rune::PaReEau, {Stat::ReEau, 3.f}},
    {Rune::ReAir, {Stat::ReAir, 1.f}},
    {Rune::PaReAir, {Stat::ReAir, 3.f}},
    {Rune::ReNeutre, {Stat::ReNeutre, 1.f}},
    {Rune::PaReNeutre, {Stat::ReNeutre, 3.f}},
    {Rune::RePerTerre, {Stat::RePerTerre, 1.f}},
    {Rune::RePerFeu, {Stat::RePerFeu, 1.f}},
    {Rune::RePerEau, {Stat::RePerEau, 1.f}},
    {Rune::RePerAir, {Stat::RePerAir, 1.f}},
    {Rune::RePerNeutre, {Stat::RePerNeutre, 1.f}},
    {Rune::RePou, {Stat::RePou, 1.f}},
    {Rune::PaRePou, {Stat::RePou, 3.f}},
    {Rune::ReCri, {Stat::ReCri, 1.f}},
    {Rune::PaReCri, {Stat::ReCri, 3.f}},
    {Rune::RePa, {Stat::RePa, 1.f}},
    {Rune::PaRePa, {Stat::RePa, 3.f}},
    {Rune::RePm, {Stat::RePm, 1.f}},
    {Rune::PaRePm, {Stat::RePm, 3.f}},
    {Rune::RetPa, {Stat::RetPa, 1.f}},
    {Rune::PaRetPa, {Stat::RetPa, 3.f}},
    {Rune::RetPm, {Stat::RetPm, 1.f}},
    {Rune::PaRetPm, {Stat::RetPm, 3.f}},
    {Rune::Pod, {Stat::Pod, 10.f}},
    {Rune::PaPod, {Stat::Pod, 30.f}},
    {Rune::RaPod, {Stat::Pod, 100.f}},
    {Rune::Tac, {Stat::Tac, 1.f}},
    {Rune::PaTac, {Stat::Tac, 3.f}},
    {Rune::Fui, {Stat::Fui, 1.f}},
    {Rune::PaFui, {Stat::Fui, 3.f}},
    {Rune::Do, {Stat::Do, 1.f}},
    {Rune::DoTerre, {Stat::DoTerre, 1.f}},
    {Rune::PaDoTerre, {Stat::DoTerre, 3.f}},
    {Rune::DoNeutre, {Stat::DoNeutre, 1.f}},
    {Rune::PaDoNeutre, {Stat::DoNeutre, 3.f}},
    {Rune::DoFeu, {Stat::DoFeu, 1.f}},
    {Rune::PaDoFeu, {Stat::DoFeu, 3.f}},
    {Rune::DoAir, {Stat::DoAir, 1.f}},
    {Rune::PaDoAir, {Stat::DoAir, 3.f}},
    {Rune::DoEau, {Stat::DoEau, 1.f}},
    {Rune::PaDoEau, {Stat::DoEau, 3.f}},
    {Rune::DoPou, {Stat::DoPou, 1.f}},
    {Rune::PaDoPou, {Stat::DoPou, 3.f}},
    {Rune::DoCri, {Stat::DoCri, 1.f}},
    {Rune::PaDoCri, {Stat::DoCri, 3.f}},
    {Rune::Pi, {Stat::Pi, 1.f}},
    {Rune::PaPi, {Stat::Pi, 3.f}},
    {Rune::DoPerDi, {Stat::DoPerDi, 1.f}},
    {Rune::DoPerAr, {Stat::DoPerAr, 1.f}},
    {Rune::DoPerSo, {Stat::DoPerSo, 1.f}},
    {Rune::DoPerMe, {Stat::DoPerMe, 1.f}},
    {Rune::RePerMe, {Stat::RePerMe, 1.f}},
    {Rune::RePerDi, {Stat::RePerDi, 1.f}},
    {Rune::PiPer, {Stat::PiPer, 1.f}},
    {Rune::PaPiPer, {Stat::PiPer, 3.f}},
    {Rune::RaPiPer, {Stat::PiPer, 10.f}},
    {Rune::So, {Stat::So, 1.f}},
    {Rune::PaSo, {Stat::So, 3.f}},
    {Rune::Cri, {Stat::Cri, 1.f}},
    {Rune::DoRen, {Stat::DoRen, 1.f}},
    {Rune::Invo, {Stat::Invo, 1.f}},
    {Rune::Po, {Stat::Po, 1.f}},
    {Rune::GaPm, {Stat::GaPm, 1.f}},
    {Rune::GaPa, {Stat::GaPa, 1.f}},
};

RuneProperties GetRuneProperties(const Rune& rune)
{
    auto it = propertiesMap.find(rune);
    assert(it != propertiesMap.end());

    const auto& properties = it->second;

    return properties;
}

} // namespace DBF
