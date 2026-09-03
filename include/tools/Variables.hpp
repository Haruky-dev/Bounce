#pragma once

#include <tools/Json.hpp>


namespace Variables {
    inline Json::Type MODE = []( std::string_view mode ) -> Json::Type {
        if ( mode=="easy" ) return Json::Type::EASY;
        if ( mode=="medium" ) return Json::Type::MED;
        if ( mode=="hard" ) return Json::Type::HARD;

        throw std::runtime_error("Invalid 'mode string' given from 'Json::String'");

    }(Json::String("setting.mode", Json::Type::SET));

    inline int P1_SCORE = 0;
    inline int P2_SCORE = 0;
    inline int CD = 0;
    inline int maxScore = Json::Int("setting.maxScore", Json::Type::SET);
    inline char ballOrient = '?';
    inline int buffingPeriod = Json::Int("setting.buffingPeriod");
    inline int freezeDuration = Json::Int("buff.freeze.durPivot");
    inline float offsetPercent = Json::Float("setting.offsetPercent");
    inline float stretchPercent = Json::Float("setting.stretchPercent");
};