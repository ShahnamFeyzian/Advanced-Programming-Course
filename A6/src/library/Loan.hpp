#ifndef __LOAN_HH__
#define __LOAN_HH__

#include"Document.hpp"
#include"Error.hpp"
#include<string>

const int total_extension  = 2;

class Loan
{
public:
	Loan(Document* _document);
	int calc_penalty();
	void extend();
	void time_pass(int days);
	std::string get_doc_title();

private:
	Document* document;
	std::string doc_title;
	int days_left;
	int remaining_extension;
	bool can_extend;

	void handle_extension_errors();

};



#endif