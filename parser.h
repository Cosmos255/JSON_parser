#include <iostream>
#include <string>
#include <fstream>
#include <map>

union JsonValue {
    int i;
    double d;
    std::map<std::string, JsonValue>* json;

};

class JsonParser {
    public:
        using text_it = std::string::const_iterator;

        void ReadFile(const std::string &filepath, std::string &output);
        JsonValue ParsePrimitive(const std::string &text, text_it start, text_it end);
};
