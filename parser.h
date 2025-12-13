#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>


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

};

std::vector<Token> Tokens;


class Lexer {
public:
    Lexer(const std::string& filename): in(filename),line(1),col(1){
        if(!in){
            std::cerr<<"No existing files found";
        }
    }

    void Tokenizer(){
        Token token_t;

        switch (peek()){
        case '{': Tokens.push_back({L_Brace, "{"}); break;
        case '}': Tokens.push_back({R_Brace, "}"}); break;
        case '"': Tokens.push_back({STRING, readString()}); break;
        case ':': Tokens.push_back({Colon, ":"}); break;
        case ',': Tokens.push_back({Comma, ","}); break;
        case ' ': skipWL(); break;
        case 't': Tokens.push_back({True, "true"}); break;
        case 'f': Tokens.push_back({False, "false"}); break;
        case '-': Tokens.push_back({NUMBER, readNumber()}); break;
        default:
            Tokens.push_back({NUMBER, readNumber()});
        }

        



        if(!in.eof()) Tokenizer;
    }




private:
    std::ifstream in;
    int line, col;

    char peek(){
        char c;
        c=in.peek();
        return c;
    };

    char advance(){
        
    };

    std::string readString(){
        in.get();
        std::string data;
        std::getline(in, data, '"');
        return data;
    }

    std::string readNumber(){
        char n = peek();
        if(isdigit(n) || n == '-' || n=='E' || n=='e' || n=='.' || n=='+'){
            
        }
    }

    void skipWL(){
        if(peek()==' '){
            in.get();
        }
    }

};

