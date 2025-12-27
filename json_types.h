#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <format>
#include <unordered_map>


#define NULL 0

enum type_t
{
    L_Brace,
    R_Brace,
    L_Bracket,
    R_Bracket,
    Colon,
    Comma,
    NUMBER,
    STRING,
    NULLT,
    True,
    False,
};

struct Token
{
    type_t type;
    std::string value;

};

struct JsonValue;
using JsonArray = std::vector<JsonValue>;
using JsonObject = std::unordered_map<std::string, JsonValue>;


struct JsonValue{
    using Value = std::variant<int, double, bool, std::string, JsonArray, JsonObject>;
	Value data;

    JsonValue &at(const std::string &key);
    template <typename T>
    T &as();

};

template <typename T>
T &JsonValue::as(){
    if (auto* p = std::get_if<T>(&data))
        return *p;
    throw std::runtime_error("wrong type");
}


JsonValue& JsonValue::at(const std::string &key){
    auto obj = std::get<JsonObject>(data);
    auto it = obj.find(key); // find returns a pointer 
    if(it==obj.end()) throw std::runtime_error("Key " + key + "not found");
    return it->second;
}



JsonValue root;




