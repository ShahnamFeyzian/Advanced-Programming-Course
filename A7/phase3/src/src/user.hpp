#ifndef _USER_HPP_
#define _USER_HPP_

#include<string>


class User
{
public:
	User(std::string _name);
	bool is_name(std::string _name);
	void start_travel();
	void finish_travel();
	bool can_start_travel();
	virtual bool are_you_passenger();
	virtual bool are_you_driver();
	std::string get_name();

protected:
	std::string name;
	bool in_travel;

};

class Passenger : public User
{
public:
	Passenger(std::string _name);
	virtual bool are_you_passenger();


private:


};

class Driver : public User
{
public:
	Driver(std::string _name);
	virtual bool are_you_driver();


private:


};




#endif