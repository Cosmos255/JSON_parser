#pragma once
#include "json_types.h"
#include <string>
#include <stdexcept>


JsonObject& asObject(JsonValue& v) {
    if (auto p = std::get_if<JsonObject>(&v.data)) return *p;
    throw std::runtime_error("JsonValue is not an object");
}

JsonArray& asArray(JsonValue& v) {
    if (auto p = std::get_if<JsonArray>(&v.data)) return *p;
    throw std::runtime_error("JsonValue is not an array");
}

std::string& asString(JsonValue& v) {
    if (auto p = std::get_if<std::string>(&v.data)) return *p;
    throw std::runtime_error("JsonValue is not a string");
}

double asDouble(JsonValue& v) {
    if (auto p = std::get_if<double>(&v.data)) return *p;
    throw std::runtime_error("JsonValue is not a number");
}

int asInt(JsonValue& v) {
    return static_cast<int>(asDouble(v));
}

JsonValue& getKey(JsonObject& obj, const std::string& key) {
    auto it = obj.find(key);
    if (it == obj.end()) throw std::runtime_error("Key \"" + key + "\" not found");
    return it->second;
}
