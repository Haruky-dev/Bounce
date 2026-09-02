#pragma once

#include <SFML/Graphics.hpp>
#include <tools/json.hpp>

#include <string>

using json = nlohmann::json;
using str  = std::string;


class Json {
    public:
        enum class Type { SET, EASY, MED, HARD };

    public:
        static void Load();

        static int   Int( const str& );
        static float Float( const str& );
        static bool  Bool( const str& );
        static str   String( const str& );

        static int   Int( const str&, const Json::Type file );
        static float Float( const str&, const Json::Type file );
        static bool  Bool( const str&, const Json::Type file );
        static str   String( const str&, const Json::Type file );


    private:
        static inline json __settings;
        static inline json __modes[3];

    private:
        static void _init();
        static void _load( const Json::Type );
        static json _value_at( const Json::Type, const str& );
        static bool _invalid() {
            if ( Json::__settings.is_null() || Json::__settings.empty() ) return true;

            for ( int i = 0; i < 3; i++ )
                if ( Json::__modes[i].is_null() || Json::__modes[i].empty() ) return true;

            return false;
        }
};
