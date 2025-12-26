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

	//JsonValue() = default;

	//template <typename T>
	//JsonValue(T&& v): data(std::forward<T(v)) {}

};

JsonValue root;