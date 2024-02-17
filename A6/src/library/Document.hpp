#ifndef __DOCUMENT_HH__
#define __DOCUMENT_HH__

#include"Error.hpp"
#include<string>
#include<vector>

const int book_return_deadline = 10;
const int book_penalty_interval_1 = 7;
const int book_penalty_interval_2 = 14;
const int book_penalty_cost_1 = 2000;
const int book_penalty_cost_2 = 3000;
const int book_penalty_cost_3 = 5000;
const int reference_return_deadline = 5;
const int reference_penalty_interval_1 = 3;
const int reference_penalty_cost_1 = 5000;
const int reference_penalty_cost_2 = 7000;
const int magazine_return_deadline = 2;
const int magazine_penalty_cost_1 = 2000;
const int magazine_penalty_cost_2 = 3000;


class Document
{
public:
	Document(std::string _title, int _copies);
	virtual int calc_penalty(int day);
	bool is_my_title(std::string _name);
	bool is_available();
	std::string get_title();
	int get_loan_interval();
	virtual int get_extension_days();
	void borrow();

protected:
	std::string title;
	int total_copies;
	int available_copies;
	int loan_interval;
	std::vector<int> penalty_intervals;
	std::vector<int> penalty_costs;
};


class Book : public Document
{
public:
	Book(std::string _title, int _copies);



private:

};

class Reference : public Document
{
public:
	Reference(std::string _title, int _copies);



private:

};


class Magazine : public Document
{
public:
	Magazine(std::string _title, int _year, int _number, int _copies);
	virtual int calc_penalty(int day);
	virtual int get_extension_days();

private:
	int year;
	int number;

};


#endif