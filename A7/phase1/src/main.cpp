#include"cli_app_runer.hpp"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;




int main(int argc, char*argv[])
{
	CLI_AppRuner app(argv[1]);

	app.run();

}