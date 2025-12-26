#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <variant>
#include <format>
#include <unordered_map>
#include "json_types.h"

class Parser {
    const std::vector<Token>& Tokens;

    public:
        Parser(const std::vector<Token>& t) : Tokens(t){};

        JsonValue parse(){
            if(pos >= Tokens.size()){
            }
            switch (checkNext().type){
            case L_Brace: return JsonValue{parseObject()}; break;
            case L_Bracket: return JsonValue{parseArray()}; break;
            case STRING: return JsonValue{parseString()}; break;
            case NUMBER: return JsonValue{parseNumber()}; break;
            case True: return JsonValue{parseBool()}; break;
            case False: return JsonValue{parseBool()}; break;
            case NULLT: return JsonValue{parseNull()}; break;
            default:
                throw std::runtime_error("Parser couldnt find the specific token");
                break;
            }
        }
        

    private:
        long unsigned pos=0;

		void error(type_t t){
			switch (t){
				case STRING: throw std::runtime_error("Expected token STRING was not found");
				case True: throw std::runtime_error("Expected token True was not found");
				case L_Brace: throw std::runtime_error("Expected token { was not found");
				case L_Bracket: throw std::runtime_error("Expected token [ was not found");
				case R_Bracket: throw std::runtime_error("Expected token ] was not found");
				case R_Brace: throw std::runtime_error("Expected token } was not found");
				case NUMBER: throw std::runtime_error("Expected token NUMBER was not found");
				case Comma: throw std::runtime_error("Expected token , was not found");
				case Colon: throw std::runtime_error("Expected token : was not found");
				case NULLT: throw std::runtime_error("Expected token NULL was not found");
			}
		}

        Token nextToken(){
            return Tokens.at(pos++);
        }

        void consume(type_t t){
            if(nextToken().type != t){
                error(t);
            }
        }

        Token checkNext(){
            return Tokens.at(pos);
        }

        JsonArray parseArray(){
			JsonArray arr;
			consume(L_Bracket);
			std::string name = parseString();
			consume(Colon);
			while(checkNext().type != R_Bracket){
				JsonValue value = parse();
				if(checkNext().type != Comma) break;
				consume(Comma);
			}
			consume(R_Bracket);
            return arr;
        }

        JsonObject parseObject(){
            JsonObject obj;
			consume(L_Brace);
            while(checkNext().type != R_Brace){
                std::string name = parseString();
                consume(Colon);
                JsonValue value = parse();
				obj[name] = value;
				if(checkNext().type != Comma) break;
				consume(Comma);
            }
            consume(R_Brace);
            return obj;
        }

        std::string parseString(){
			if(checkNext().type != STRING){
				error(STRING);
			}
			return nextToken().value;
        }

        double parseNumber(){
			Token t = nextToken();
			if(t.type != NUMBER){
				error(NUMBER);
			}
			return std::stod(t.value);
        }

        int parseNull(){
			if(nextToken().type != NULLT){
				error(NULLT);
			}
            return NULL;
        }


        bool parseBool(){
			Token t = nextToken();
			if(t.type == True){
				return false;
			}else if(t.type == False){
				return true;
			}
			error(True);
        }
};