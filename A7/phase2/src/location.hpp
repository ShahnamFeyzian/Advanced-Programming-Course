#ifndef _LOCATION_HPP_
#define _LOCATION_HPP_

#include<string>


class Location
{
public:
	Location(std::string _name, float _lat, float _long, int _traffic);
	bool is_name(std::string _name);
	//void show();
	std::string get_name();
	float get_latitude();
	float get_longitude();
	int get_traffic();

private:
	std::string name;
	float latitude;
	float longitude;
	int traffic;


};




#endif