#include <cassert>
#include <tools/Json.hpp>

#include <fstream>
#include <stdexcept>

#include <iostream>

json Json::confData = json::object(); // Init as empty obj

void Json::Load( const str& filePath ) {
    std::ifstream file(filePath);
    assert( !file.fail() );
    assert( file.is_open() );

    try {
        file >> Json::confData;
        assert( !(Json::confData.is_null() ));

    } catch ( const json::exception& e ) {
        throw std::runtime_error(e.what());
    }
}

void Json::reLoad() {
    std::cout << "[Json] R\n";
    Json::Load();
};

json Json::getVal( const str& key ) {
    if (Json::invalid())
        Json::Load();

    try {
        // split key by dots '.' (ai.speed)

        str currK = key;
        json curr = Json::confData; // Json is composed of nested "json's"
                                    // we track/define them by 'curr'

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

int Json::Int( const str& key ) {
    auto val = Json::getVal( key );

    if (val.is_number())
        return val.get<int>();

    throw std::runtime_error("Invalid Value [T=int] Found for key=" + key);
}

float Json::Float( const str& key ) {
    auto val = Json::getVal( key );

    if (val.is_number())
        return val.get<float>();

    throw std::runtime_error("Invalid Value [T=float] Found for key=" + key);
}

bool Json::Bool( const str& key ) {
    auto val = Json::getVal( key );

    if (val.is_boolean())
        return val.get<bool>();

    throw std::runtime_error("Invalid Value [T=bool] Found for key=" + key);
}

str Json::String( const str& key ) {
    auto val = Json::getVal( key );

    if (val.is_string())
        return val.get<str>();

    throw std::runtime_error("Invalid Value [T=str] Found for key=" + key);
}

// json Json::getArray( const str& key ) const {
//     auto val = Json::getVal( key );

//     if (val.is_array()) {
//         return val;
//     }

//     throw std::runtime_error("lsdkfj");
// }