#ifndef _TRIP_HPP_
#define _TRIP_HPP_

#include"location.hpp"
#include"user.hpp"
#include<string>
#include<vector>

#define WAITING_STATUS "waiting"
#define TRAVELING_STATUS "traveling"
#define FINISHED_STATUS "finished"

enum TravelSituation {waiting, traveling, finished, canceled};

class Trip
{
public:
	Trip(User* _pass, Location* _orig, Location* _dest, int _id);
	bool is_id(int _id);
	bool is_passenger_name(std::string name);
	bool is_waiting();
	void start_traveling(User* _driver);
	void finish();
	void cancel();
	std::vector<std::string> present_yourself();


private:
	int id;
	User* passenger;
	User* driver;
	Location* origin;
	Location* destination;
	TravelSituation situation;

	std::string get_situation();

};



#endif