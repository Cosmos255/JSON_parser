#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <stack>
#include <unordered_map>

#define NULL 0

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
    
    ~Lexer(){
        in.close();
    }

    void Tokenizer(){
        while(peek() != EOF){
            //Token token_t;

            switch (peek()){
            case '{': Tokens.push_back({L_Brace, "{"}); advance(); break;
            case '}': Tokens.push_back({R_Brace, "}"}); advance(); break;
            case '[': Tokens.push_back({L_Bracket, "["}); advance(); break;
            case ']': Tokens.push_back({R_Bracket, "]"}); advance(); break;
            case '"': Tokens.push_back({STRING, readString()}); break;
            case ':': Tokens.push_back({Colon, ":"}); advance(); break;
            case ',': Tokens.push_back({Comma, ","}); advance(); break;
            case ' ': skipWL(); break;
            case 't': Tokens.push_back({True, "true"}); advance(4); break;
            case 'f': Tokens.push_back({False, "false"}); advance(5); break;
            case 'n': Tokens.push_back({NULLT, "0"}); advance(5); break;
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
    }

    void advance(int n=1){
        while(n){
            in.get(); 
            n--;
            col++;
            std::cout<<"line"<<col<<"\n";
        }
    }

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
            if(peek() == '\n') line++; col=0;
            in.get();
        }
    }

};


struct JsonValue;
using JsonArray = std::vector<JsonValue>;
using JsonObject = std::unordered_map<std::string, JsonValue>;
using JsonValue = std::variant<int, double, bool, std::string, JsonArray, JsonObject>;


class Parser {
    public:
        JsonValue JsonRoot;
        Parser(){
            JsonRoot = Parse();
        }

        JsonValue Parse(){
            if(pos >= Tokens.size()){
            }
            switch (checkNext().type){
            case L_Brace: return parseObject();
            case L_Bracket: return parseArray();
            case STRING: return parseString();
            case NUMBER: return parseNumber();
            case True: return parseBool();
            case False: return parseBool();
            case NULLT: return parseNull();
            default:
                throw std::runtime_error("Parser couldnt find the specific token");
                break;
            }
        }
        

    private:
        int pos=0;
        bool EndOFStructure = false;
        std::stack<type_t>openBraces;

        Token nextToken(){
            return  Tokens.at(pos++);
        }
        
        void consume(type_t t){
            if(nextToken().type != t){
                throw std::runtime_error("Expected type wasnt found");
            }else{
                pos++;
            }
        }

        Token checkNext(){
            return Tokens.at(pos);
        }

        void stackCheck(type_t type){
        
        }

        JsonArray parseArray(){

        }

        JsonObject parseObject(){
            JsonObject obj;
            if(checkNext().type == L_Brace){
                nextToken();
            }
            while(checkNext().type != R_Brace){
                Token t=nextToken();
                std::string name = parseString();
                consume(Colon);
                JsonValue value = Parse();

                obj[name] = "hello";
            }
            consume(R_Brace);
            return obj;
        }

        std::string parseString(){

        }

        JsonValue parseNumber(){

        }

        int parseNull(){
            return NULL;
        }


        bool parseBool(){

        }

};