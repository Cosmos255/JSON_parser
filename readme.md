A C++ JSON parser which works good enough.

Main Features:
Its quite slow like really slow:(
Type safety is optional(no yes option included)
It might leak memory i hope not but it is what it is
Its a bit janky but it works


USAGE:

include the  "json.h" header then create a auto variable named root then use the 
function json::parseJson(input) input must be a file then you can access members using .at(name) and .as for types also you must have included <vetor>, <string> and <unordered_map>;

example:

{
  "product": "Laptop",
  "id": "LAP123",
  "specs": {
    "cpu": "Intel i7",
    "ram_gb": 16,
    "storage": {
      "type": "SSD",
      "size_gb": 512
    }
  }
}


#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "json.h"

int main(){
   
   auto root = json::parseJson("test.json");
   auto pc = root;
   
   auto cpu = pc.at("specs").at("cpu").as<std::string>();

  or you might prefer this, both work

  cpu = pc["specs"]["cpu"].as<std::string>();



   std::cout<<"the cpu is"<<cpu;

   return 0;
}

Have fun!!!