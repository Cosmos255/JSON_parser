#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ostream>
#include "parser.h"


int main(int argc, char *argv[]){
    if(argc < 2){
        std::cerr<<"Please input a second argument for the input ifle";
    }else{
        std::string output = argv[1];
        File(output);
    }
}

