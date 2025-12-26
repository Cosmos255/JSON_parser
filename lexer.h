#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <format>
#include "json_types.h"

class Lexer {
public:
    std::vector<Token> Tokens;
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
					//std::string error = std::format("The token couldnt be detected Line:{} Col{} Token{}",line,col,peek());
                    //throw std::runtime_error(error);
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
            if(peek() == '\n'){
                line++; 
				col=0;
            }
            in.get();
        }
    }
};