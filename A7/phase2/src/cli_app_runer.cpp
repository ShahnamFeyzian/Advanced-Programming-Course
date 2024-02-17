#include"cli_app_runer.hpp"
#include<fstream>
#include<string>
#include<vector>
#include<iostream>
#include <iomanip>
using namespace std;



CLI_AppRuner::CLI_AppRuner(string file_address)
{
	app = new UtaxiApp(read_input_file(file_address));

}

CLI_AppRuner::~CLI_AppRuner()
{
	delete app;
}


void CLI_AppRuner::run()
{
	string command;

	while(getline(cin, command))
	{
		try
		{
			processing(command);
		}
		catch(Exception ex)
		{
			cerr << ex.show_message() << endl;
		}
	}
}


void CLI_AppRuner::processing(string cmd)
{
	int pose = cmd.find(" ");
	if(pose == -1) throw WrongRequest_EX();

	string type = cmd.substr(0, pose);

	if(type == POST) post_cmds(cmd.substr(pose+1));
	else if(type == GET) get_cmds(cmd.substr(pose+1));
	else if(type == DELETE) delete_cmds(cmd.substr(pose+1));
	else throw WrongRequest_EX();

}


void CLI_AppRuner::post_cmds(string cmd)
{
	int pose = cmd.find(CMD_DELIMITER);
	if(pose == -1) throw WrongRequest_EX();
	string base_command = cmd.substr(0, pose+1);
	cmd = cmd.substr(pose+2);

	if(base_command == POST_SIGNUP) post_signup(cmd);
	else if (base_command == POST_TRIPS) post_trips(cmd);
	else if (base_command == POST_ACCEPT) post_accept(cmd);
	else if (base_command == POST_FINISH) post_finish(cmd);
	else throw WrongRequest_EX();
}

void CLI_AppRuner::post_signup(string cmd)
{
	string name, role;
	vector<string> args = extract(cmd);
	if(args.size() != 4) throw WrongRequest_EX();

	if(args[0] == USERNAME_ARG && args[2] == ROLE_ARG) 
	{
		name = args[1];
		role = args[3];
	}
	else if(args[0] == ROLE_ARG && args[2] == USERNAME_ARG)
	{
		role = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	if(role == DRIVER_ROLE) app->add_user(name, driver);
	else if(role == PASSENGER_ROLE) app->add_user(name, passenger);
	else throw WrongRequest_EX();

	cout << SUCCESS_MESSAGE << endl;
}

void CLI_AppRuner::post_trips(string cmd)
{
	string name, origin, destination, s_hurry;
	bool hurry;
	vector<string> args = extract(cmd);
	if(args.size() != 8) throw WrongRequest_EX();

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == USERNAME_ARG) name = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == ORIGIN_ARG) origin = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == DESTINATION_ARG) destination = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == HURRY_ARG) s_hurry = args[i+1];
	}

	if(name == "" || origin == "" || destination == "") throw WrongRequest_EX();
	if(s_hurry =="" || (s_hurry != YES_ARG && s_hurry != NO_ARG)) throw WrongRequest_EX();

	if(s_hurry == YES_ARG) hurry = true;
	else hurry = false;

	cout << app->add_trip(name, origin, destination, hurry) << endl;
}

void CLI_AppRuner::post_accept(string cmd)
{
	string name, id;
	vector<string> args = extract(cmd);
	if(args.size() != 4) throw WrongRequest_EX();

	if(args[0] == USERNAME_ARG && args[2] == ID_ARG) 
	{
		name = args[1];
		id = args[3];
	}
	else if(args[0] == ID_ARG && args[2] == USERNAME_ARG)
	{
		id = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	app->accept_trip(name, stoi(id));

	cout << SUCCESS_MESSAGE << endl;
}

void CLI_AppRuner::post_finish(string cmd)
{
	string name, id;
	vector<string> args = extract(cmd);
	if(args.size() != 4) throw WrongRequest_EX();

	if(args[0] == USERNAME_ARG && args[2] == ID_ARG) 
	{
		name = args[1];
		id = args[3];
	}
	else if(args[0] == ID_ARG && args[2] == USERNAME_ARG)
	{
		id = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	app->finish_trip(name, stoi(id));

	cout << SUCCESS_MESSAGE << endl;
}


void CLI_AppRuner::get_cmds(string cmd)
{
	int pose = cmd.find(CMD_DELIMITER);
	if(pose == -1) throw WrongRequest_EX();
	string base_command = cmd.substr(0, pose+1);
	cmd = cmd.substr(pose+2);

	if(base_command == GET_TRIPS) get_trips(cmd);
	else if(base_command == GET_COST) get_cost(cmd);
	else throw WrongRequest_EX();
}

void CLI_AppRuner::get_cost(string cmd)
{
	string name, origin, destination, s_hurry;
	bool hurry;
	vector<string> args = extract(cmd);
	if(args.size() != 8) throw WrongRequest_EX();

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == USERNAME_ARG) name = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == ORIGIN_ARG) origin = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == DESTINATION_ARG) destination = args[i+1];
	}

	for(int i=0; i<8; i+=2)
	{
		if(args[i] == HURRY_ARG) s_hurry = args[i+1];
	}

	if(name == "" || origin == "" || destination == "") throw WrongRequest_EX();
	if(s_hurry =="" || (s_hurry != YES_ARG && s_hurry != NO_ARG)) throw WrongRequest_EX();

	if(s_hurry == YES_ARG) hurry = true;
	else hurry = false;

	cout << setprecision(2) << fixed <<app->get_cost(name, origin, destination, hurry) << endl;

}

void CLI_AppRuner::get_trips(string cmd)
{
	vector<string> args = extract(cmd);

	if(args.size() != 4) throw WrongRequest_EX();

	if(args[0] == ID_ARG || args[2] == ID_ARG) get_single_trip(args);
	else get_trips_list(args);
}

void CLI_AppRuner::get_single_trip(vector<string> args)
{
	string name, id;

	if(args[0] == USERNAME_ARG && args[2] == ID_ARG) 
	{
		name = args[1];
		id = args[3];
	}
	else if(args[0] == ID_ARG && args[2] == USERNAME_ARG)
	{
		id = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	vector<string> presentation = app->present_trip(name, stoi(id));
	if(presentation.size() == 0) throw Undefined_EX();

	print_trip_presentation(presentation);
}

void CLI_AppRuner::get_trips_list(vector<string> args)
{
	string name, s_sort;
	bool sort;
	
	if(args[0] == USERNAME_ARG && args[2] == SORT_BY_COST_ARG) 
	{
		name = args[1];
		s_sort = args[3];
	}
	else if(args[0] == SORT_BY_COST_ARG && args[2] == USERNAME_ARG)
	{
		s_sort = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	if(s_sort =="" || (s_sort != YES_ARG && s_sort != NO_ARG)) throw WrongRequest_EX();

	if(s_sort == YES_ARG) sort = true;
	else sort = false;

	vector<vector<string>> presentations = app->present_all_trips(name, sort);

	int num_of_trips = app->get_number_of_trips();
	if(num_of_trips == 0) throw Empty_EX();

	for(int i=0; i<presentations.size(); i++)
		print_trip_presentation(presentations[i]);
}

void CLI_AppRuner::print_trip_presentation(vector<string> p)
{
	if(p.size() == 0) return;

	int point_pose = p[4].find(".");
	if(point_pose != -1) p[4] = p[4].substr(0, point_pose+3);

	cout << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << " " << p[4] << " " << p[5] << endl;
}

void CLI_AppRuner::delete_cmds(string cmd)
{
	int pose = cmd.find(CMD_DELIMITER);
	if(pose == -1) throw WrongRequest_EX();
	string base_command = cmd.substr(0, pose+1);
	cmd = cmd.substr(pose+2);

	if(base_command == DELETE_TRIPS) delete_trips(cmd);
	else throw WrongRequest_EX();
}

void CLI_AppRuner::delete_trips(string cmd)
{
	string name, id;
	vector<string> args = extract(cmd);
	if(args.size() != 4) throw WrongRequest_EX();

	if(args[0] == USERNAME_ARG && args[2] == ID_ARG) 
	{
		name = args[1];
		id = args[3];
	}
	else if(args[0] == ID_ARG && args[2] == USERNAME_ARG)
	{
		id = args[1];
		name = args[3];
	}
	else throw WrongRequest_EX();

	app->delete_trip(name, stoi(id));

	cout << SUCCESS_MESSAGE << endl;
}


vector<string> CLI_AppRuner::extract(string line)
{
	vector<string> args;
	int pose = line.find(" ");
	while(pose != -1)
	{
		args.push_back(line.substr(0, pose));
		line = line.substr(pose+1);
		pose = line.find(" ");
	}
	args.push_back(line);

	return args;
}


vector<Location*> CLI_AppRuner::read_input_file(string file_address)
{
	vector<Location*> locations;
	string line;
	ifstream input_file(file_address);

	getline(input_file, line);
	while(getline(input_file, line))
	{
		locations.push_back(read_line(line));
	}

	input_file.close();

	return locations;
}


Location* CLI_AppRuner::read_line(string line)
{
	string name;
	int delimiter_pose, trafic;
	float latitude, longitude;

	delimiter_pose = line.find(CSV_DELIMITER);
	name = line.substr(0, delimiter_pose);
	
	line = line.substr(delimiter_pose+1);
	delimiter_pose = line.find(CSV_DELIMITER);
	latitude = stof(line.substr(0, delimiter_pose));
	
	line = line.substr(delimiter_pose+1);
	delimiter_pose = line.find(CSV_DELIMITER);
	longitude = stof(line.substr(0, delimiter_pose));

	line = line.substr(delimiter_pose+1);
	trafic = stoi(line);

	return new Location(name, latitude, longitude, trafic);

}