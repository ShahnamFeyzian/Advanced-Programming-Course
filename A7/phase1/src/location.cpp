#include"location.hpp"
#include<string>
#include<iostream>
using namespace std;


Location::Location(string _name, float _lat, float _long)
{
	name = _name;
	latitude = _lat;
	longitude = _long;
}

bool Location::is_name(string _name)
{
	if(name == _name) return true;
	else return false;
}

string Location::get_name() { return name; }