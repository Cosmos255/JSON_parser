#pragma once
#include "json_types.h"
#include <string>
#include <stdexcept>


template <typename T>
T& get(JsonValue& v) {
    if (auto* p = std::get_if<T>(&v.data))
        return *p;
    throw std::runtime_error("wrong type");
}


JsonValue& getKey(JsonObject& obj, const std::string& key) {
    auto value = obj.find(key);
    if(value==obj.end()) throw std::runtime_error("Key " + key + "not found");
    return value->second;
}