//Sytem Functions
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <assert.h> 
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <iterator>

#include "System_Functions.h"
#include "User.h"

using namespace std;

//Global Variables Used
User userobj;
map <long long,User> MapUsersVaccTwice;
char VaccTypeAnswer;

bool  VaccDosageInfo(){
    int dosagenumber;
    cout << "Did take the First dose only or both doses for only one press 1 for both press 2 :" << endl;
    cin >> dosagenumber;

    //check For dosage
    switch (dosagenumber)
    {
    case 1:
    userobj.VaccTwice = false;
    break;

    case 2:
    userobj.VaccTwice = true;
    break;

    default:
    cout<< "Choose from the given options" << endl;
    }
    return userobj.VaccTwice;
}


void  getVaccInfo(){
    char VaccInfoAns;

    cout << "Did you get your vaccination press 'y' for YES and 'n' for NO " << endl;
    cin >> VaccInfoAns;
    switch (VaccInfoAns)
    {
    case 'y':
    case 'Y':
    //took both
    if (VaccDosageInfo() == true){
        // WriteIntoVaccTwice();
    }else{
        
        cout << "TEAM MESSAGE!!!!!!!!!! STILL DIDNT DO WriteIntoVaccOnce() FUNC " << endl;
        // WriteIntoVaccOnce();
    }
    break;

    case 'n':
    case 'N':
    cout << "You'll be added in the waiting list, Thank you ! " << endl;
    //put in queue for waiting list
    // WriteIntoWaitingFile();
    break;

    default:
    cout<< "Choose from the given options" << endl;
    break;
    }

}


//retrieve data from user
void Register(){
    
    //enter number if not 13 doesnt insert in the id 
    cout << "Enter ID : " << endl;
    cin >> userobj.userid; 
    try {
        if (checkVaccTwiceId(userobj.userid)==true) {
            throw 505;
    }
    }
    catch (int myNum) {
    cout << myNum << " " << "ID registered before pleasse log in\n";
    //call login function
    login();

    //exit function
    return;
    }    

    //check that it is a 13 digit ID *****BUT STILL NEEDS to be fininshed*****
    try {
    if (to_string(userobj.userid).length()!= 13) {
      throw 505;
    }
    }
    //mynum error number?
    catch (int myNum) {
    cout << myNum << " " << "Denied - ID must be of 13 digits\n";
    Register();
    //exit function
    return;
    }    
    cout << "Enter Full Name : " << endl;
    cin >> userobj.name;
    cout << "Enter password : " << endl;
    cin >> userobj.password; 
     try {
    if (userobj.password.length() < 8) {
      throw 505;
    }
    }
    catch (int myNum) {
    cout << myNum << " " << "Denied - Password must be atleast 8 digits\n";
    Register();
    return;    
    }
    cout << "Enter Gender : " << endl;
    cin >> userobj.gender; 
    cout << "Enter age : " << endl;
    cin >> userobj.age;

    //Make an array of all Egyptian Governorates to check over first
    cout << "Enter Governorate : " << endl;
    cin >> userobj.governorate;
    cout << "Enter p for pfizer , a for Astrazenca , s for Sinopharm " << endl;
    cin >> VaccTypeAnswer;
    userobj.vaccinetype = VaccTypeAnswer;

    // Insert Data into map
    MapUsersVaccTwice[userobj.userid] = userobj;

    //get type to check which vaccination is better
    switch (VaccTypeAnswer)
    {
    case 'p':
    case 'P':
    
    userobj.pfizer++;
    break;

    case 'a':
    case 'A':
    userobj.Astrazenca++;
    break;

    case 's':
    case 'S':
    userobj.Sinopharm++;
    break;

    default:
        break;
    }
    getVaccInfo();
    
}

//login if id registered before
void login(){
    cout << "Enter ID : " << endl;
    cin >> userobj.userid; 
    //check that it is a 13 digit ID *****BUT STILL NEEDS to be fininshed*****
    try {
    if (to_string(userobj.userid).length()!= 13) {
      throw 505;
    }
    }
    //mynum error number?
    catch (int myNum) {
    cout << myNum << " " << "Denied - ID must be of 13 digits\n";
    login();
    //exit function
    return;
    }    
    
    cout << "Enter password : " << endl;
    cin >> userobj.password; 
     try {
    if (userobj.password.length() < 8) {
      throw 505;
    }
    }
    catch (int myNum) {
    cout << myNum << " " << "Denied - Password must be atleast 8 digits\n";
    login();
    return;    
    }
    Main_menu_options();
}

// registered user options "add track your status if waiting"
void Main_menu_options(){
    int registered_user_option;
    cout << "Welcome To Egyptian Vaccine Tracker \n";
    cout << "1/Display Information \n2/Update Information \n3/delete  Account \n" << endl;
	cin >> registered_user_option;
    switch (registered_user_option)
	{
			case 1:
				userobj.Display();
				break;
			case 2:
				userobj.update();
				break;

			case 3:
				userobj.delete_data();
                break;
			default:
				cout << "Invalid input please try again" << endl;
                Main_menu_options();
				break;
			}

		}




// Write into file for those who took both dosages
void  WriteIntoVaccTwice(){

    // Start truncate file to insert updated data
    ofstream writeintofile("UserVaccTwice.txt", std::ios::trunc);

    // Check if file is open
    if (!writeintofile.is_open()) {
        cout << "Error opening file" << endl;
    }

    // Check if map is not empty
    assert(!MapUsersVaccTwice.empty());

    // Iterate over the map and retrieve values
    map<long long, User>::iterator it = MapUsersVaccTwice.begin();

    while (it != MapUsersVaccTwice.end()) {
        writeintofile << it->second.userid << " "<< it->second.name << " " << it->second.password << " " << it->second.gender
          << " " << it->second.age
         << " " << it->second.governorate
         << " " << it->second.vaccinetype << endl;
        it++;
    }

    // Close file
    writeintofile.close();
}

// Read from file for those who took both dosages
void  ReadFromFile() {

    // Read from file returns string "line" (ageString,IDString) take input and later convert to int
    string ageString;
    string IDString;

    // Read from file
    string line;
    ifstream readfromfile("UserVaccTwice.txt");

    // Check if file is open or not
    if (!readfromfile.is_open()) {
        cout << "Failed to open file" << endl;
    }

    // Assign to read from the beginning of the file 
    readfromfile.seekg(0, ios::beg);

    // Start reading from file
    while (getline(readfromfile, line)) {

        istringstream iss(line);

        // Puts data from file in the User object placeholder
        iss >> IDString >> userobj.name >> userobj.password >> userobj.gender >> ageString >> userobj.governorate >> userobj.vaccinetype;

        // Converts String to "datatype"
        userobj.userid = stoll(IDString);
        userobj.age = stoi(ageString);

        // Inserts Data into map
        MapUsersVaccTwice[userobj.userid] = userobj;

    }

    // Close file
    readfromfile.close();

}

//Traverse through the map
void IterateOverMap(){
	//checks if empty
	assert(!MapUsersVaccTwice.empty());

	//iterate over the map and retrieve values
	map <long long, User> ::iterator it = MapUsersVaccTwice.begin();

    while(it!=MapUsersVaccTwice.end()){
	cout << it->first << " " << it->second.name << " " << it->second.password << " " << it->second.gender
		<< " " << it->second.age << " " << it->second.governorate << " " << it->second.vaccinetype << endl;
    it++;
    }
        
}


//Traverse through the map for display function
void databyid(long long key) {
	//checks if empty
	assert(!MapUsersVaccTwice.empty());
	//iterate over the map and retrieve values
	map <long long, User> ::iterator it = MapUsersVaccTwice.find(key);
	cout << it->first << " " << it->second.name << " " << it->second.password << " " << it->second.gender
		<< " " << it->second.age << " " << it->second.governorate << " " << it->second.vaccinetype << endl;

}

//make it do while to update if want again
void updatevalues(long long key){
    int option;
    map <long long, User> ::iterator it = MapUsersVaccTwice.find(key);
    cout << "Choose the option you want to update\n" <<"1/First Name\n" <<"2/Password\n" <<"3/Gender\n" <<"4/Age\n" << "5/Governorate\n" 
    <<"6/Vaccine Type\n";
    cin >> option;
    switch (option)
    {
    case 1:
    {
    string fname;
    cout << "Enter updated name : \n";
    cin >> fname;
    it->second.name = fname;
    break;
    }

    case 2:{
    string newpassword;
    cout << "Enter updated password : \n";
    cin >> newpassword;
    it->second.password = newpassword;
    break;
    }
    
    case 3:
    {string ngender;
    cout << "Enter Gender : \n";
    cin >> ngender;
    it->second.gender = ngender;
    break;
    }

    case 4:
    {
    int newage;
    cout << "Enter Age : \n";
    cin >> newage;
    it->second.age = newage;
    break;
    }

    case 5:
    {
    string newGovernorate;
    cout << "Enter Governorate : \n";
    cin >> newGovernorate;
    it->second.governorate = newGovernorate;
    break;
    }

    case 6:
    {
    string newvaccinetype;
    cout << "Enter vaccinetype : \n";
    cin >> newvaccinetype;
    it->second.vaccinetype = newvaccinetype;
    break;
    }

    default:
        cout << "Enter Valid Option \n";
        break;
    }
	
}

//for delete functionality
void removevalues(long long key){
    MapUsersVaccTwice.erase(key);
}


//check if id exists in vacc twice
bool checkVaccTwiceId(long long key){
    bool found;
    // count function return 1 key exist & 0 otherwise
    if(MapUsersVaccTwice.count(key)>0)
      found = true;
    else 
      found = false;
    return found;
}

// check password use encoding for password string::compare checksum data integrity
bool checkpass(long long key,string password){
    bool passfound;
    // count function return 1 key exist & 0 otherwise
    if(MapUsersVaccTwice[key].password == password)
       passfound = true;
    else 
      passfound = false;
    return passfound;
}