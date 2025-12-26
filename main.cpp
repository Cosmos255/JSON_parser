#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "json.h"
#include "jsonhelp.h"

int main(){

   JsonValue root = json::parseJson("test.json");
   JsonObject& student = asObject(root); 

   std::string name = asString(getKey(student, "name"));
   int age = std::stoi(asString(getKey(student, "age")));
   bool active = std::get<bool>(getKey(student, "active").data);


   std::cout << "Name: " << name << "\n";
   std::cout << "Age: " << age << "\n";
   std::cout << "Active: " << active << "\n";

   /*
   Finished the lexer/parse it worjs but accesing is a pain
   so to do:
   Understand how it works.
   Read the manual about std::variant.
   Create a getValue template to esasilt acces elements and not via whats above
   Clean the code
   Finish the read me
   Last commit and start smth else like rust or a compression tool or maybe some random walk
   */


   return 0;
}



