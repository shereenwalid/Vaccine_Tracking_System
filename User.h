//user header file
#pragma once
using namespace std;
class User{
    public:

    // attributes
    //long long ID must be 13 digits
    long long userid;
    string name;
    string password;
    string gender;
    int age;
    string governorate;
    string vaccinetype;

    //counters made to get which vaccination is better
    int pfizer;
    int Astrazenca;
    int Sinopharm;
    
    //specify dosages 
    bool VaccTwice;   
    
    //functionalities
    void Display();
    void update();
    void delete_data();



};