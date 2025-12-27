#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>  
#include <fstream>
#include <format>
#include <unordered_map>

#include "json_types.h"   
#include "lexer.h"        
#include "parser.h"       


namespace json {

    inline JsonValue parseJson(const std::string input){
        try{
            Lexer lexer(input);
            auto tokens = lexer.Tokens;
            Parser parser(tokens);
            return parser.parse();

        } catch(const std::exception& e){
            throw std::runtime_error(std::string("Json parsing erro: ") + e.what());
        }
    }

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

}
