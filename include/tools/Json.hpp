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
        static inline json settings_;
        static inline json modes_[3];

    private:
        static void init_();
        static void load_( const Json::Type );
        static json value_at_( const Json::Type, const str& );
        static bool invalid_() {
            if ( Json::settings_.is_null() || Json::settings_.empty() ) return true;

            for ( int i = 0; i < 3; i++ )
                if ( Json::modes_[i].is_null() || Json::modes_[i].empty() ) return true;

            return false;
        }
};
