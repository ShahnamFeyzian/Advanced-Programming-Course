#ifndef _LOCATION_HPP_
#define _LOCATION_HPP_

#include<string>


class Location
{
public:
	Location(std::string _name, float _lat, float _long);
	bool is_name(std::string _name);
	std::string get_name();



private:
	std::string name;
	float latitude;
	float longitude;


};




#endif