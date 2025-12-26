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

}
