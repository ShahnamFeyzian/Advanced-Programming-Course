#ifndef _APP_HPP_
#define _APP_HPP_

#include"location.hpp"
#include"user.hpp"
#include"trip.hpp"
#include"exception.hpp"
#include<vector>


enum Role {driver, passenger};

class UtaxiApp
{
public:
	UtaxiApp(std::vector<Location*> _locs);
	~UtaxiApp();
	void add_user(std::string name, Role role);
	int add_trip(std::string user_name, std::string origin, std::string destination, bool hurry);
	float get_cost(std::string user_name, std::string origin, std::string destination, bool hurry);
	void accept_trip(std::string driver_name, int trip_id);
	void finish_trip(std::string driver_name, int trip_id);
	std::vector<std::string> present_trip(std::string name, int trip_id);
	std::vector<std::vector<std::string>> present_all_trips(std::string name, bool cost_sort);
	void delete_trip(std::string name, int trip_id);
	int get_number_of_trips();


private:
	std::vector<User*> users;
	std::vector<Location*> locations;
	std::vector<Trip*> trips;

	void sort_by_cost(std::vector<Trip*> &init_trips);
	int find_location(std::string name);
	int find_user(std::string name);
	int find_trip(int id);
	void free_users();
	void free_locations();
	void free_trips();

};


#endif