#include"CartManager.hpp"
#include<vector>
#include<iostream>
using namespace std;


CartManager::CartManager() {}

CartManager::~CartManager() 
{
	while(items.size() != 0)
	{
		items.erase(items.begin());
	}
}


void CartManager::add_item(int id, int cost, int weight)
{
	check_duplicate_id(id);

	items.push_back(new Product(id, cost, weight));
}

void CartManager::add_box(int id)
{
	check_duplicate_id(id);

	items.push_back(new Box(id));
}

void CartManager::add_to_box(int box_id, int id)
{
	int box_index = find_item(box_id);
	int item_index = find_item(id);

	if(box_index < 0 || item_index < 0)
	{
		cerr << INVALID_ITEM_ERR;
		exit(EXIT_SUCCESS);
	}

	items[box_index]->add_to_contents(items[item_index]);
	items.erase(items.begin() + item_index);
}

int CartManager::evaluate_cart()
{
	int total_cost = 0;

	for(int i=0; i<items.size(); i++)
		total_cost += items[i]->calc_cost();

	return total_cost;
}

int CartManager::find_item(int id)
{
	int index;

	for(index=0; index<items.size(); index++)
		if(items[index]->is_id(id)) return index;

	return -1;
}

void CartManager::check_duplicate_id(int id)
{
	for(int i=0; i<items.size(); i++)
		if(items[i]->is_id(id))
		{
			cerr << DUPLICATE_ID_ERR;
			exit(EXIT_SUCCESS);
		}
}