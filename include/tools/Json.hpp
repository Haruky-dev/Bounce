#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include <tools/json.hpp>

using json = nlohmann::json;
using str  = std::string;


class Json {
    private:
        static json confData;

        static json getVal( const str& key );
        // check if config data has loaded seccussfully

        static bool invalid() {
            return (Json::confData.is_null() ||
                Json::confData.empty());
        }

        static void Load( const str& filePath = "data/conf.json" );

    public:
        static void reLoad();

        // getters
            // Primitive types
        static int   Int( const str& key );
        static float Float( const str& key);
        static bool  Bool( const str& key );
        static str   String( const str& key );
        // json  getArray( const str& key )  const;
};
