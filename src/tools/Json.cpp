#include <tools/Json.hpp>

#include <tools/Variables.hpp>

#include <fstream>
#include <cassert>
#include <stdexcept>


void Json::init_() {
    Json::settings_ = json::object();

    for ( int i = 0; i < 3; i++ ) Json::modes_[i] = json::object();
}

void Json::Load() {
    Json::init_();
    Json::load_(Json::Type::SET);
    Json::load_(Json::Type::EASY);
    Json::load_(Json::Type::MED);
    Json::load_(Json::Type::HARD);
};

void Json::load_( const Json::Type ftype ) {
    std::ifstream file;
    json* target = nullptr;
    str file_path = "";
    
    switch (ftype) {
        case Json::Type::SET:
            file_path = "data/settings.json"; target = &Json::settings_;
            break;
        case Json::Type::EASY:
            file_path = "data/modes/easy.json"; target = &Json::modes_[0];
            break;
        case Json::Type::MED:
            file_path = "data/modes/medium.json"; target = &Json::modes_[1];
            break;
        case Json::Type::HARD:
            file_path = "data/modes/hard.json"; target = &Json::modes_[2];
            break;

        default: throw std::runtime_error("Invalid 'Json::Type' given for 'Json::load_'");
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

json Json::value_at_( const Json::Type file, const str& key ) {
    if (Json::invalid_())
        Json::Load();

    str currK = key;
    json curr = json::object();

    switch (file) {
        case Json::Type::SET:  curr = Json::settings_; break;
        case Json::Type::EASY: curr = Json::modes_[0]; break;
        case Json::Type::MED:  curr = Json::modes_[1]; break;
        case Json::Type::HARD: curr = Json::modes_[2]; break;
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

int   Json::Int( const str& key )    { return Json::Int(key, Variables::MODE); }
float Json::Float( const str& key )  { return Json::Float(key, Variables::MODE); }
str   Json::String( const str& key ) { return Json::String(key, Variables::MODE); }
bool  Json::Bool( const str& key )   { return Json::Bool(key, Variables::MODE); }

int Json::Int( const str& key, const Json::Type file ) {
    auto val = Json::value_at_( file, key );

    if (val.is_number())
        return val.get<int>();

    throw std::runtime_error("Invalid Value [T=int] Found for key=" + key);
}

float Json::Float( const str& key, const Json::Type file ) {
    auto val = Json::value_at_( file, key );

    if (val.is_number())
        return val.get<float>();

    throw std::runtime_error("Invalid Value [T=float] Found for key=" + key);
}

bool Json::Bool( const str& key, const Json::Type file ) {
    auto val = Json::value_at_( file, key );

    if (val.is_boolean())
        return val.get<bool>();

    throw std::runtime_error("Invalid Value [T=bool] Found for key=" + key);
}

str Json::String( const str& key, const Json::Type file ) {
    auto val = Json::value_at_( file, key );

    if (val.is_string())
        return val.get<str>();

    throw std::runtime_error("Invalid Value [T=str] Found for key=" + key);
}