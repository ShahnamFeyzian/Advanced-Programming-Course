#include"trip.hpp"
#include<string>
#include<math.h>
using namespace std;


Trip::Trip(User* _pass, Location* _orig, Location* _dest, int _id, bool hurry)
{
	passenger = _pass;
	origin = _orig;
	destination = _dest;
	id = _id;
	situation = waiting;
	calc_price(hurry);
}

void Trip::calc_price(bool hurry)
{
	float hurry_c;
	if(hurry) hurry_c = hurry_coefficient;
	else hurry_c = 1;

	int traffic = origin->get_traffic() + destination->get_traffic();
	price = calc_dist() * traffic * fixed_coefficient * hurry_c; 
}

float Trip::calc_dist()
{
	float delta_lat = origin->get_latitude() - destination->get_latitude();
	float delta_long = origin->get_longitude() - destination->get_longitude();

	delta_lat = pow(delta_lat, 2);
	delta_long = pow(delta_long, 2);

	float dist = sqrt(delta_long + delta_lat);

	return dist * 110.5;
}

bool Trip::is_id(int _id)
{
	if(situation == canceled) return false;
	if(id == _id) return true;
	else return false;
}

bool Trip::is_waiting()
{
	if(situation == waiting) return true;
	else return false;
}

bool Trip::is_passenger_name(string name)
{
	return passenger->is_name(name);
}

void Trip::start_traveling(User* _driver)
{
	situation = traveling;
	driver = _driver;
	driver->start_travel();
}

void Trip::finish()
{
	situation = finished;
	passenger->finish_travel();
	driver->finish_travel();
}

void Trip::cancel()
{
	situation = canceled;
	passenger->finish_travel();
}

vector<string> Trip::present_yourself()
{
	vector<string> presentation;

	if(situation == canceled) return presentation; 

	presentation.push_back(to_string(id));
	presentation.push_back(passenger->get_name());
	presentation.push_back(origin->get_name());
	presentation.push_back(destination->get_name());
	presentation.push_back(to_string(price));
	presentation.push_back(get_situation());

	return presentation;
}

string Trip::get_situation()
{
	if(situation == waiting) return WAITING_STATUS;
	else if(situation == traveling) return TRAVELING_STATUS;
	else if(situation == finished) return FINISHED_STATUS;
	else return "";
}

int Trip::get_id() { return id; }
float Trip::get_price() { return price; }