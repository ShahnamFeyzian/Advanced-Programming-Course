#ifndef __PERSON_HH__
#define __PERSON_HH__

#include"Loan.hpp"
#include"Document.hpp"
#include<string>
#include<vector>

const int student_max_loan = 2;
const int prof_max_loan = 5;


class Person
{
public:
	Person(std::string _name);
	void time_pass(int days);
	void borrow(Document* _doc);
	void extend(std::string doc_title);
	void return_doc(std::string doc_title);
	bool is_my_name(std::string _name);
	int get_total_penalty();

private:
	int find_loan(std::string title);
	void handle_borrow_errors(Document* _doc);

protected:
	std::string name;
	std::vector<Loan> loans;
	int max_loan;
	int total_penalty;
};


class Student : public Person
{
public:
	Student(std::string _name, std::string _id);

private:
	std::string id;

};


class Prof : public Person
{
public:
	Prof(std::string _name);


private:

};





#endif