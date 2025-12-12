#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

struct File{
    std::ifstream in;

    File(){
        std::cerr<<"Error no input file";
    };
    File(const std::string &input_f){
        in.open(input_f);
        if(!in){
            std::cerr << "Error could not open file";
        }
    }
    
};



using type_t = enum
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

    Token getNextToken(){
        //File IN >>value;
    };
};

std::vector<Token> Tokens;


class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0){}
    Token getNextToken();
private:
    std::string input;
    size_t pos;

};

