#include"user.hpp"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


User::User(string _name)
{
	name = _name;
	in_travel = false;
} 

bool User::is_name(string _name)
{
	if(_name == name) return true;
	else return false;
}

void User::start_travel()
{
	in_travel = true;
}

void User::finish_travel()
{
	in_travel = false;
}

bool User::can_start_travel()
{
	return !in_travel;
}

bool User::are_you_passenger() { return false; }
bool User::are_you_driver() { return false; }

string User::get_name() { return name; }


Passenger::Passenger(string _name) : User(_name) {}

bool Passenger::are_you_passenger() { return true; }



Driver::Driver(string _name) : User(_name) {}

bool Driver::are_you_driver() { return true; }