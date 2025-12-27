#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "json.h"

int main(){
   
   auto root = json::parseJson("test.json");
   auto pc = root.as<JsonObject>();
   
   auto cpu = pc.at("specs").as<JsonObject>().at("cpu").as<std::string>();

   std::cout<<"the cpu is"<<cpu;

   return 0;
}



