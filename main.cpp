#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "json.h"

int main(){
   
   auto root = json::parseJson("test.json");
   auto pc = root;
   
   auto cpu = pc.at("specs").at("cpu").as<std::string>();
   auto cpu = pc["specs"]["cpu"].as<std::string>();

   std::cout<<"the cpu is"<<cpu;

   return 0;
}



