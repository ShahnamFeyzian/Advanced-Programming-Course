#include<iostream>
#include"game.hpp"
using namespace std;


int main(int argc , char* argv[])
{
	
	Game game(argv[1]);
	game.run();
	
	return 0;
}