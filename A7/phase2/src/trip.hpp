#ifndef _TRIP_HPP_
#define _TRIP_HPP_

#include"location.hpp"
#include"user.hpp"
#include<string>
#include<vector>
#include<math.h>

#define WAITING_STATUS "waiting"
#define TRAVELING_STATUS "traveling"
#define FINISHED_STATUS "finished"

const int fixed_coefficient = 10000;
const float hurry_coefficient = 1.2;

enum TravelSituation {waiting, traveling, finished, canceled};

class Trip
{
public:
	Trip(User* _pass, Location* _orig, Location* _dest, int _id, bool hurry);
	bool is_id(int _id);
	bool is_passenger_name(std::string name);
	bool is_waiting();
	void start_traveling(User* _driver);
	void finish();
	void cancel();
	std::vector<std::string> present_yourself();
	float get_price();
	int get_id();


private:
	int id;
	float price;
	User* passenger;
	User* driver;
	Location* origin;
	Location* destination;
	TravelSituation situation;

	std::string get_situation();
	float calc_dist();
	void calc_price(bool hurry);

};



#endif