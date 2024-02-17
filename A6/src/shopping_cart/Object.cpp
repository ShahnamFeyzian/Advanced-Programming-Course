#include"Object.hpp"
#include<vector>
#include<iostream>
using namespace std;

Object::Object(int _id)
{
	id = _id;
}

bool Object::is_id(int _id)
{
	if(id == _id) return true;
	else return false;
}


Product::Product(int _id, int _cost, int _weight) : Object(_id)
{
	cost = _cost;
	weight = _weight;
}

int Product::calc_cost()
{
	return cost;
}

int Product::calc_weight()
{
	return weight;
}

void Product::add_to_contents(Object* _obj)
{
	cerr << CAN_NOT_ADD_ERR;
	exit(EXIT_SUCCESS);
}



Box::Box(int _id) : Object(_id) {}

int Box::calc_cost()
{
	int total_cost = 0;
	int total_weight = calc_weight();

	if(total_weight<20) total_cost += total_weight/2;
	else total_cost += total_weight/10;

	for(int i=0; i<contents.size(); i++)
		total_cost += contents[i]->calc_cost();

	return total_cost;
}

int Box::calc_weight()
{
	int total_weight = 0;

	for(int i=0; i<contents.size(); i++)
		total_weight += contents[i]->calc_weight();

	return total_weight;
}

void Box::add_to_contents(Object* _obj)
{
	contents.push_back(_obj);
}