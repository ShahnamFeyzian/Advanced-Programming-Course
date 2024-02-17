#include"location.hpp"
#include<string>
#include<iostream>
using namespace std;


Location::Location(string _name, float _lat, float _long, int _traffic)
{
	name = _name;
	latitude = _lat;
	longitude = _long;
	traffic = _traffic;
}

bool Location::is_name(string _name)
{
	if(name == _name) return true;
	else return false;
}

// void Location::show()
// {
// 	cout << name << " " << latitude << " " << longitude << " " << trafic << endl;
// }

string Location::get_name() { return name; }
float Location::get_latitude() { return latitude; }
float Location::get_longitude() { return longitude; }
int Location::get_traffic() { return traffic; }