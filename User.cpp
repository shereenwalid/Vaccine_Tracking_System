#pragma once

#include "User.h"
#include "System_Functions.h"
#include <iostream>
#include <string>
#include <assert.h> 
using namespace std;


void User::Display()
{
	long long key;
	string password;
	cout << "Enter id to display" << endl;
	cin >> key;

    //check over id
    try {
        if (checkVaccTwiceId(key)) 
        {
            cout << "enter your password" << endl;
            cin >> password;
            //check over pass
            try {
                if (checkpass(key,password)) 
                {
                    databyid(key);
                }
                else
                {
                    throw 505;
                }
                }catch (int myNum) 
                {
                    cout << myNum << " " << "Access Denied - Incorrect Password \n";
                }
                }
                else
                {
                    throw 505;
                }
        }catch (int myNum)
        {
            cout << myNum << " " << "Denied - ID not found \n";
        }

}

void User::update(){
	long long key;
	cout << "enter id to Update" << endl;
	cin >> key;

    try {
    if (checkVaccTwiceId(key)) {
        updatevalues(key);
    }
    else{
      throw 505;
    }
  }

  catch (int myNum) {
    cout << myNum << " " << "Denied - ID not found\n";
    }
}


void User::delete_data(){
	long long key;
	cout << "enter id to delete" << endl;
	cin >> key;

    try {
    if (checkVaccTwiceId(key)) {
        removevalues(key);
    }
    else{
      throw 505;
    }
  }

  catch (int myNum) {
    cout << myNum << " " << "Denied - ID not found\n";
    }
}
