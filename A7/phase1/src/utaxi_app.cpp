#include"utaxi_app.hpp"
#include<vector>
#include<string>
#include<iostream>
using namespace std;


UtaxiApp::UtaxiApp(vector<Location*> _locs)
{
	locations = _locs;
}

UtaxiApp::~UtaxiApp()
{
	free_users();
	free_locations();
	free_trips();
}

void UtaxiApp::add_user(string name, Role role)
{
	if(find_user(name) != -1) throw WrongRequest_EX();

	if(role == driver) users.push_back(new Driver(name));
	else users.push_back(new Passenger(name));
}


int UtaxiApp::add_trip(string user_name, string origin, string destination)
{
	int user_i = find_user(user_name);
	int origin_i = find_location(origin);
	int destination_i = find_location(destination);
	if(user_i == -1 || origin_i == -1 || destination_i == -1) throw Undefined_EX();
	if(!users[user_i]->are_you_passenger()) throw Access_EX();
	if(!users[user_i]->can_start_travel()) throw WrongRequest_EX();

	trips.push_back(new Trip(users[user_i], locations[origin_i], locations[destination_i], (trips.size()+1)));
	users[user_i]->start_travel();

	return trips.size();
}


void UtaxiApp::accept_trip(string driver_name, int trip_id)
{
	int driver_i = find_user(driver_name);
	int trip_i = find_trip(trip_id);
	if(driver_i == -1 || trip_i == -1) throw Undefined_EX();
	if(!users[driver_i]->are_you_driver()) throw Access_EX();
	if(!users[driver_i]->can_start_travel()) throw WrongRequest_EX();
	if(!trips[trip_i]->is_waiting()) throw WrongRequest_EX();

	trips[trip_i]->start_traveling(users[driver_i]);
}


void UtaxiApp::finish_trip(string driver_name, int trip_id)
{
	int driver_i = find_user(driver_name);
	int trip_i = find_trip(trip_id);
	if(driver_i == -1 || trip_i == -1) throw Undefined_EX();
	if(!users[driver_i]->are_you_driver()) throw Access_EX();

	trips[trip_i]->finish();
}


vector<string> UtaxiApp::present_trip(string name, int trip_id)
{
	int user_i = find_user(name);
	int trip_i = find_trip(trip_id);
	if(user_i == -1) throw Undefined_EX();
	if(!users[user_i]->are_you_driver()) throw Access_EX();

	if(trip_i == -1) 
	{
		vector<string> a;
		return a;
	}
	return trips[trip_i]->present_yourself();
}


void UtaxiApp::delete_trip(string name, int trip_id)
{
	int user_i = find_user(name);
	int trip_i = find_trip(trip_id);
	if(user_i == -1 || trip_i == -1) throw Undefined_EX();
	if(!trips[trip_i]->is_passenger_name(name)) throw Access_EX();
	if(!trips[trip_i]->is_waiting()) throw WrongRequest_EX();

	trips[trip_i]->cancel();
}


int UtaxiApp::find_user(string name)
{	
	for(int index=0; index<users.size(); index++)
		if(users[index]->is_name(name)) return index;

	return -1;
}

int UtaxiApp::find_location(string name)
{
	for(int index=0; index<locations.size(); index++)
		if(locations[index]->is_name(name)) return index;

	return -1;
}

int UtaxiApp::find_trip(int id)
{
	for(int index=0; index<trips.size(); index++)
		if(trips[index]->is_id(id)) return index;

	return -1;
}

int UtaxiApp::get_number_of_trips() { return trips.size(); }

void UtaxiApp::free_users()
{
	while(users.size() > 0)
	{
		users.erase(users.begin());
	}
}

void UtaxiApp::free_locations()
{
	while(locations.size() > 0)
	{
		locations.erase(locations.begin());
	}
}

void UtaxiApp::free_trips()
{
	while(trips.size() > 0)
	{
		trips.erase(trips.begin());
	}
}