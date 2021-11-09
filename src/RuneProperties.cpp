#include "RuneProperties.h"

#include <stdexcept>
#include <unordered_map>

#include "Rune.h"
#include "Stat.h"
#include "StatsDensity.h"

namespace DBF {

// clang-format off
static std::unordered_map<Rune, RuneProperties> kPropertiesMap = {
    {Rune::Fo,          {Stat::Fo,          1.f,   0.f}},
    {Rune::PaFo,        {Stat::Fo,          3.f,   0.f}},
    {Rune::RaFo,        {Stat::Fo,          10.f,  0.f}},
    {Rune::Ine,         {Stat::Ine,         1.f,   0.f}},
    {Rune::PaIne,       {Stat::Ine,         3.f,   0.f}},
    {Rune::RaIne,       {Stat::Ine,         10.f,  0.f}},
    {Rune::Cha,         {Stat::Cha,         1.f,   0.f}},
    {Rune::PaCha,       {Stat::Cha,         3.f,   0.f}},
    {Rune::RaCha,       {Stat::Cha,         10.f,  0.f}},
    {Rune::Age,         {Stat::Age,         1.f,   0.f}},
    {Rune::PaAge,       {Stat::Age,         3.f,   0.f}},
    {Rune::RaAge,       {Stat::Age,         10.f,  0.f}},
    {Rune::Vi,          {Stat::Vi,          5.f,   0.f}},
    {Rune::PaVi,        {Stat::Vi,          15.f,  0.f}},
    {Rune::RaVi,        {Stat::Vi,          50.f,  0.f}},
    {Rune::Ini,         {Stat::Ini,         10.f,  0.f}},
    {Rune::PaIni,       {Stat::Ini,         30.f,  0.f}},
    {Rune::RaIni,       {Stat::Ini,         100.f, 0.f}},
    {Rune::Sa,          {Stat::Sa,          1.f,   0.f}},
    {Rune::PaSa,        {Stat::Sa,          3.f,   0.f}},
    {Rune::RaSa,        {Stat::Sa,          10.f,  0.f}},
    {Rune::Prospe,      {Stat::Prospe,      1.f,   0.f}},
    {Rune::PaProspe,    {Stat::Prospe,      3.f,   0.f}},
    {Rune::Pui,         {Stat::Pui,         1.f,   0.f}},
    {Rune::PaPui,       {Stat::Pui,         3.f,   0.f}},
    {Rune::RaPui,       {Stat::Pui,         10.f,  0.f}},
    {Rune::ReTerre,     {Stat::ReTerre,     1.f,   0.f}},
    {Rune::PaReTerre,   {Stat::ReTerre,     3.f,   0.f}},
    {Rune::ReFeu,       {Stat::ReFeu,       1.f,   0.f}},
    {Rune::PaReFeu,     {Stat::ReFeu,       3.f,   0.f}},
    {Rune::ReEau,       {Stat::ReEau,       1.f,   0.f}},
    {Rune::PaReEau,     {Stat::ReEau,       3.f,   0.f}},
    {Rune::ReAir,       {Stat::ReAir,       1.f,   0.f}},
    {Rune::PaReAir,     {Stat::ReAir,       3.f,   0.f}},
    {Rune::ReNeutre,    {Stat::ReNeutre,    1.f,   0.f}},
    {Rune::PaReNeutre,  {Stat::ReNeutre,    3.f,   0.f}},
    {Rune::RePerTerre,  {Stat::RePerTerre,  1.f,   0.f}},
    {Rune::RePerFeu,    {Stat::RePerFeu,    1.f,   0.f}},
    {Rune::RePerEau,    {Stat::RePerEau,    1.f,   0.f}},
    {Rune::RePerAir,    {Stat::RePerAir,    1.f,   0.f}},
    {Rune::RePerNeutre, {Stat::RePerNeutre, 1.f,   0.f}},
    {Rune::RePou,       {Stat::RePou,       1.f,   0.f}},
    {Rune::PaRePou,     {Stat::RePou,       3.f,   0.f}},
    {Rune::ReCri,       {Stat::ReCri,       1.f,   0.f}},
    {Rune::PaReCri,     {Stat::ReCri,       3.f,   0.f}},
    {Rune::RePa,        {Stat::RePa,        1.f,   0.f}},
    {Rune::PaRePa,      {Stat::RePa,        3.f,   0.f}},
    {Rune::RePm,        {Stat::RePm,        1.f,   0.f}},
    {Rune::PaRePm,      {Stat::RePm,        3.f,   0.f}},
    {Rune::RetPa,       {Stat::RetPa,       1.f,   0.f}},
    {Rune::PaRetPa,     {Stat::RetPa,       3.f,   0.f}},
    {Rune::RetPm,       {Stat::RetPm,       1.f,   0.f}},
    {Rune::PaRetPm,     {Stat::RetPm,       3.f,   0.f}},
    {Rune::Pod,         {Stat::Pod,         10.f,  0.f}},
    {Rune::PaPod,       {Stat::Pod,         30.f,  0.f}},
    {Rune::RaPod,       {Stat::Pod,         100.f, 0.f}},
    {Rune::Tac,         {Stat::Tac,         1.f,   0.f}},
    {Rune::PaTac,       {Stat::Tac,         3.f,   0.f}},
    {Rune::Fui,         {Stat::Fui,         1.f,   0.f}},
    {Rune::PaFui,       {Stat::Fui,         3.f,   0.f}},
    {Rune::Do,          {Stat::Do,          1.f,   0.f}},
    {Rune::DoTerre,     {Stat::DoTerre,     1.f,   0.f}},
    {Rune::PaDoTerre,   {Stat::DoTerre,     3.f,   0.f}},
    {Rune::DoNeutre,    {Stat::DoNeutre,    1.f,   0.f}},
    {Rune::PaDoNeutre,  {Stat::DoNeutre,    3.f,   0.f}},
    {Rune::DoFeu,       {Stat::DoFeu,       1.f,   0.f}},
    {Rune::PaDoFeu,     {Stat::DoFeu,       3.f,   0.f}},
    {Rune::DoAir,       {Stat::DoAir,       1.f,   0.f}},
    {Rune::PaDoAir,     {Stat::DoAir,       3.f,   0.f}},
    {Rune::DoEau,       {Stat::DoEau,       1.f,   0.f}},
    {Rune::PaDoEau,     {Stat::DoEau,       3.f,   0.f}},
    {Rune::DoPou,       {Stat::DoPou,       1.f,   0.f}},
    {Rune::PaDoPou,     {Stat::DoPou,       3.f,   0.f}},
    {Rune::DoCri,       {Stat::DoCri,       1.f,   0.f}},
    {Rune::PaDoCri,     {Stat::DoCri,       3.f,   0.f}},
    {Rune::Pi,          {Stat::Pi,          1.f,   0.f}},
    {Rune::PaPi,        {Stat::Pi,          3.f,   0.f}},
    {Rune::DoPerDi,     {Stat::DoPerDi,     1.f,   0.f}},
    {Rune::DoPerAr,     {Stat::DoPerAr,     1.f,   0.f}},
    {Rune::DoPerSo,     {Stat::DoPerSo,     1.f,   0.f}},
    {Rune::DoPerMe,     {Stat::DoPerMe,     1.f,   0.f}},
    {Rune::RePerMe,     {Stat::RePerMe,     1.f,   0.f}},
    {Rune::RePerDi,     {Stat::RePerDi,     1.f,   0.f}},
    {Rune::PiPer,       {Stat::PiPer,       1.f,   0.f}},
    {Rune::PaPiPer,     {Stat::PiPer,       3.f,   0.f}},
    {Rune::RaPiPer,     {Stat::PiPer,       10.f,  0.f}},
    {Rune::So,          {Stat::So,          1.f,   0.f}},
    {Rune::PaSo,        {Stat::So,          3.f,   0.f}},
    {Rune::Cri,         {Stat::Cri,         1.f,   0.f}},
    {Rune::DoRen,       {Stat::DoRen,       1.f,   0.f}},
    {Rune::Invo,        {Stat::Invo,        1.f,   0.f}},
    {Rune::Po,          {Stat::Po,          1.f,   0.f}},
    {Rune::GaPm,        {Stat::GaPm,        1.f,   0.f}},
    {Rune::GaPa,        {Stat::GaPa,        1.f,   0.f}},
};
// clang-format on

static const std::unordered_map<Rune, RuneProperties>& SetupRunesDensity()
{
    for (auto& pair : kPropertiesMap) {
        auto& properties = pair.second;
        const auto& stat = properties.stat;
        const auto& factor = properties.factor;
        auto& density = properties.density;

        density = GetStatDensity(stat) * factor;
    }

    return kPropertiesMap;
}

const RuneProperties& GetRuneProperties(const Rune& rune)
{
    static auto propertiesMap = SetupRunesDensity();

    auto it = propertiesMap.find(rune);
    if (it == propertiesMap.end()) {
        throw std::invalid_argument("Unknown rune");
    }

    const auto& properties = it->second;

    return properties;
}

} // namespace DBF
