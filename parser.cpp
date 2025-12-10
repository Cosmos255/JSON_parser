#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "parser.h"


void JsonParser::ReadFile(const std::string &filepath, std::string &output) {
    std::ifstream file(filepath);
    std::string line;

    while(std::getline(file, line)) {
        output.append(line);
    }
}

JsonValue JsonParser::ParsePrimitive(const std::string& text, text_it start, text_it end){

}





int main(){

}
