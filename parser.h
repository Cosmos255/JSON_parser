#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
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
            throw std::runtime_error("FIle not found");
        }else{
            Tokenizer();
        }
    }

    void Tokenizer(){
        while(peek() != EOF){
            Token token_t;

            switch (peek()){
            case '{': Tokens.push_back({L_Brace, "{"}); advance(); break;
            case '}': Tokens.push_back({R_Brace, "}"}); advance(); break;
            case '"': Tokens.push_back({STRING, readString()}); break;
            case ':': Tokens.push_back({Colon, ":"}); advance(); break;
            case ',': Tokens.push_back({Comma, ","}); advance(); break;
            case ' ': skipWL(); break;
            case 't': Tokens.push_back({True, "true"}); advance(4); break;
            case 'f': Tokens.push_back({False, "false"}); advance(5); break;
            case '-': Tokens.push_back({NUMBER, readNumber()}); break;
            case '\n': skipWL(); break;
            case '\r': skipWL(); break;
            case '\t': skipWL(); break;
            case '\b': skipWL(); break;
            case '\f': skipWL(); break;
            default:
                if(isdigit(peek())){
                    Tokens.push_back({NUMBER, readNumber()});
                }else{
                    std::cout<<"defaulted";
                    std::cerr<<"\n"<<peek()<<"\t"<<in.peek()<<"\n";
                    throw std::runtime_error("Yea you shouldn be here");
                }
            }
        }
        std::cout<<"We finished";
        for (const auto& t : Tokens) {
            std::cout << "Type: " << t.type
                    << "  Value: [" << t.value << "]\n";
        }
    }

private:
    std::ifstream in;
    int line, col;

    char peek(){
        return in.peek();
    };

    void advance(int n=1){
        while(n){
            in.get(); 
            n--;
            line++;
            std::cout<<"line"<<line<<"\n";
        }
    };

    std::string readString(){
        advance();
        std::string data;
        std::getline(in, data, '"');
        return data;
    }

    std::string readNumber(){
        char c = peek();
        std::string data;
        while(isdigit(c) || c == '-' || c=='E' || c=='e' || c=='.' || c=='+'){
            data +=in.get();
            c = peek();
        }
        return data;
    }

    void skipWL(){
        while(std::isspace(peek())){
            in.get();
        }
    }

};


struct JsonValue;

using JsonArray = std::vector<JsonValue>;
using JsonObject = JsonValue*;

using Value = std::variant<int, double, bool, std::string, JsonArray, JsonObject>;

struct JsonValue{
    Value value;
}


using valkey = union{
    double num;
    bool bol;
    std::string str;
    std::vector<valkey> arr;
}

class Parser {
    public:


    private:


}