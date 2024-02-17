#include"Person.hpp"
#include<string>
#include<vector>
#include<iostream>
using namespace std;


Person::Person(string _name)
{
	name = _name;
	total_penalty = 0;
}


void Person::time_pass(int days)
{
	for(int i=0; i<loans.size(); i++) 
		loans[i].time_pass(days);
}


void Person::borrow(Document* _doc)
{
	handle_borrow_errors(_doc);
	loans.push_back(Loan(_doc));
}

void Person::extend(string doc_title)
{
	int loan_index = find_loan(doc_title);

	loans[loan_index].extend();
}

void Person::return_doc(string doc_title)
{
	int loan_index = find_loan(doc_title);

	total_penalty += loans[loan_index].calc_penalty();
	loans.erase(loans.begin() + loan_index);
}

bool Person::is_my_name(string _name)
{
	if(_name == name) return true;
	else return false;
}

void Person::handle_borrow_errors(Document* _doc)
{
	if(loans.size() >= max_loan)
	{
		cerr << MAX_BORROW_ERR;
		exit(EXIT_SUCCESS);
	}

	for(int i=0; i<loans.size(); i++)
		if(loans[i].get_doc_title() == _doc->get_title())
		{
			cerr << DUPLICATE_LOAN_ERR;
			exit(EXIT_SUCCESS);
		}
}

int Person::find_loan(string title)
{
	for(int i=0; i<loans.size(); i++)
		if(loans[i].get_doc_title() == title) return i;

	cerr << INVALID_LOAN_ERR;
	exit(EXIT_SUCCESS);
}

int Person::get_total_penalty()
{
	int temp_penalty = total_penalty;

	for(int  i=0; i<loans.size(); i++)
		temp_penalty += loans[i].calc_penalty();

	return temp_penalty;
}

Student::Student(string _name, string _id) : Person(_name)
{
	id = _id;
	max_loan = student_max_loan;
}


Prof::Prof(string _name) : Person(_name)
{
	max_loan = prof_max_loan;
}
