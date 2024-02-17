#ifndef _CLI_APP_RUNER_
#define _CLI_APP_RUNER_

#include"utaxi_app.hpp"
#include"location.hpp"
#include"user.hpp"
#include"trip.hpp"
#include"exception.hpp"
#include<vector>
#include<string>

#define POST "POST"
#define POST_SIGNUP "signup ?"
#define POST_TRIPS "trips ?"
#define POST_ACCEPT "accept ?"
#define POST_FINISH "finish ?"

#define GET "GET"
#define GET_TRIPS "trips ?"
#define GET_COST "cost ?"

#define DELETE "DELETE"
#define DELETE_TRIPS "trips ?"

#define USERNAME_ARG "username"
#define ROLE_ARG "role"
#define ORIGIN_ARG "origin"
#define DESTINATION_ARG "destination"
#define ID_ARG "id"
#define HURRY_ARG "in_hurry"
#define SORT_BY_COST_ARG "sort_by_cost"
#define YES_ARG "yes"
#define NO_ARG "no"

#define DRIVER_ROLE "driver"
#define PASSENGER_ROLE "passenger"

#define CSV_DELIMITER ","
#define CMD_DELIMITER "?"


class CLI_AppRuner
{
public:
	CLI_AppRuner(std::string file_address);
	~CLI_AppRuner();
	void run();


private:
	UtaxiApp* app;

	void processing(std::string cmd);
	
	void post_cmds(std::string cmd);
	void post_signup(std::string cmd);
	void post_trips(std::string cmd);
	void post_accept(std::string cmd);
	void post_finish(std::string cmd);

	void get_cmds(std::string cmd);
	void get_cost(std::string cmd);
	void get_trips(std::string cmd);
	void get_single_trip(std::vector<std::string> args);
	void get_trips_list(std::vector<std::string> args);
	void print_trip_presentation(std::vector<std::string> p);
	
	void delete_cmds(std::string cmd);
	void delete_trips(std::string cmd);

	std::vector<std::string> extract(std::string line);
	std::vector<Location*> read_input_file(std::string file_address);
	Location* read_line(std::string line);

};


#endif