#include"Loan.hpp"
#include"Document.hpp"
#include<iostream>
using namespace std;

Loan::Loan(Document* _document)
{
	document = _document;
	days_left = _document->get_loan_interval();
	doc_title = _document->get_title();
	remaining_extension = total_extension;
	can_extend = false;
}


int Loan::calc_penalty()
{
	return document->calc_penalty(days_left);
}

void Loan::handle_extension_errors()
{
	if(!can_extend)
	{
		cerr << BORROW_AND_EXTEND_ERR;
		exit(EXIT_SUCCESS);
	}

	if(days_left<0)
	{
		cerr << PENALTY_AND_EXTEND_ERR;
		exit(EXIT_SUCCESS);
	}

	if(remaining_extension == 0)
	{
		cerr << EXPIRATION_OF_EXTENSION_ERR;
		exit(EXIT_SUCCESS);	
	}
}


void Loan::extend()
{
	handle_extension_errors();

	days_left += document->get_extension_days();
	remaining_extension--;
}

void Loan::time_pass(int days)
{
	days_left -= days;
	can_extend = true;
}

string Loan::get_doc_title() { return doc_title; }