#include <tools/Json.hpp>

#include <tools/Constants.hpp>

#include <fstream>
#include <cassert>
#include <stdexcept>

#include <print>


void Json::_init() {
    Json::__settings = json::object();

    for ( int i = 0; i < 3; i++ ) Json::__modes[i] = json::object();
}

void Json::Load() {
    Json::_init();
    Json::_load(Json::Type::SET);
    Json::_load(Json::Type::EASY);
    Json::_load(Json::Type::MED);
    Json::_load(Json::Type::HARD);
};

void Json::_load( const Json::Type ftype ) {
    std::ifstream file;
    json* target = nullptr;
    str file_path = "";
    
    switch (ftype) {
        case Json::Type::SET:
            file_path = "data/settings.json"; target = &Json::__settings;
            break;
        case Json::Type::EASY:
            file_path = "data/modes/easy.json"; target = &Json::__modes[0];
            break;
        case Json::Type::MED:
            file_path = "data/modes/medium.json"; target = &Json::__modes[1];
            break;
        case Json::Type::HARD:
            file_path = "data/modes/hard.json"; target = &Json::__modes[2];
            break;

        default: throw std::runtime_error("Invalid 'Json::Type' given for 'Json::_load'");
    }

    file.open(file_path);

    assert( target );
    assert( !file.fail() );
    assert( file.is_open() );

    try {
        file >> *target;
        assert( !(target->is_null() ));

    } catch ( const json::exception& e ) {
        throw std::runtime_error(e.what());
    }
}

json Json::_value_at( const Json::Type file, const str& key ) {
    if (Json::_invalid()) {
        std::println("called");
        Json::Load();
    }

    str currK = key;
    json curr = json::object();

    switch (file) {
        case Json::Type::SET:  curr = Json::__settings; break;
        case Json::Type::EASY: curr = Json::__modes[0]; break;
        case Json::Type::MED:  curr = Json::__modes[1]; break;
        case Json::Type::HARD: curr = Json::__modes[2]; break;
    }

    try {
        // split key by dots '.' (ai.speed)

        size_t dotPos; // curr index of char '.' in the given key
        while ((dotPos=currK.find('.')) != str::npos) {
            str part = currK.substr(0, dotPos);

            if (!curr.contains(part)) // not found currK in curr json
                throw std::runtime_error("Not found [KEY] part: '" + part + "' in key path: " + key);  

            curr  = curr[part]; // nested json
            currK = currK.substr( dotPos+1 ); // move to the next key/part
        }

        if (!(curr.contains(currK)))
            throw std::runtime_error("Not found [KEY] part: '" + currK + "' in key path: " + key);

        return curr[currK];

    } catch (const json::exception& e) {
        throw std::runtime_error(e.what());
    }
}

int   Json::Int( const str& key )    { return Json::Int(key, Constants::MODE); }
float Json::Float( const str& key )  { return Json::Float(key, Constants::MODE); }
str   Json::String( const str& key ) { return Json::String(key, Constants::MODE); }
bool  Json::Bool( const str& key )   { return Json::Bool(key, Constants::MODE); }

int Json::Int( const str& key, const Json::Type file ) {
    auto val = Json::_value_at( file, key );

    if (val.is_number())
        return val.get<int>();

    throw std::runtime_error("Invalid Value [T=int] Found for key=" + key);
}

float Json::Float( const str& key, const Json::Type file ) {
    auto val = Json::_value_at( file, key );

    if (val.is_number())
        return val.get<float>();

    throw std::runtime_error("Invalid Value [T=float] Found for key=" + key);
}

bool Json::Bool( const str& key, const Json::Type file ) {
    auto val = Json::_value_at( file, key );

    if (val.is_boolean())
        return val.get<bool>();

    throw std::runtime_error("Invalid Value [T=bool] Found for key=" + key);
}

str Json::String( const str& key, const Json::Type file ) {
    auto val = Json::_value_at( file, key );

    if (val.is_string())
        return val.get<str>();

    throw std::runtime_error("Invalid Value [T=str] Found for key=" + key);
}