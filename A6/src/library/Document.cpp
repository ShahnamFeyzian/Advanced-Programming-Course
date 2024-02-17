#include"Document.hpp"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


Document::Document(string _title, int _copies)
{
	title = _title;
	total_copies = _copies;
	available_copies = _copies;
}


int Document::calc_penalty(int day)
{
	if(day>=0) return 0;
	else day = -day;

	int penalty = 0, i;

	for(i=0; i<penalty_intervals.size(); i++)
	{
		if(day > penalty_intervals[i])
		{
			day -= penalty_intervals[i];
			penalty += penalty_intervals[i]*penalty_costs[i];
		}
		else
		{
			penalty += day*penalty_costs[i];
			return penalty;
		}
	}
	
	penalty += day*penalty_costs[i];
	return penalty;
}


bool Document::is_my_title(string _name)
{
	if(_name == title) return true;
	else return false;
}

bool Document::is_available()
{
	if(available_copies > 0) return true;
	else return false;
}

void Document::borrow()
{
	if(available_copies < 1) return;
	available_copies--;
}

string Document::get_title() { return title; }
int Document::get_loan_interval() { return loan_interval; }
int Document::get_extension_days() { return loan_interval; }


Book::Book(string _title, int _copies) : Document(_title, _copies) 
{
	loan_interval = book_return_deadline;

	penalty_intervals.push_back(book_penalty_interval_1);
	penalty_intervals.push_back(book_penalty_interval_2);

	penalty_costs.push_back(book_penalty_cost_1);
	penalty_costs.push_back(book_penalty_cost_2);
	penalty_costs.push_back(book_penalty_cost_3);
}



Reference::Reference(string _title, int _copies) : Document(_title, _copies) 
{
	loan_interval = reference_return_deadline;

	penalty_intervals.push_back(reference_penalty_interval_1);

	penalty_costs.push_back(reference_penalty_cost_1);
	penalty_costs.push_back(reference_penalty_cost_2);
}



Magazine::Magazine(string _title, int _year, int _number, int _copies) : Document(_title, _copies)
{
	year = _year;
	number = _number;

	loan_interval = magazine_return_deadline;

	penalty_costs.push_back(magazine_penalty_cost_1);
	penalty_costs.push_back(magazine_penalty_cost_2);
}


int Magazine::calc_penalty(int day)
{
	if(day>=0) return 0;
	else day = -day;

	if(year<1390) return day*penalty_costs[0];
	else return day*penalty_costs[1];
}

int Magazine::get_extension_days()
{
	cerr << MAGAZINE_EXTENSION_ERR;
	exit(EXIT_SUCCESS);
}