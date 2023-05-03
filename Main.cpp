#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <string>
// #include <iterator>
// #include <assert.h> 

//include .cpp files
#include "System_Functions.cpp"
#include "User.cpp" 


using namespace std;


int main(){

    User s;

    ReadFromFile();
  
    // Register();

    s.update();

    WriteIntoVaccTwice();
    return 0;
}


