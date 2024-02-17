#include"Library.hpp"
#include<string>
#include<vector>
#include<iostream>
using namespace std;


void Library::check_name(string name)
{
	for(int i=0; i<members.size(); i++)
		if(members[i]->is_my_name(name))
		{
			cerr << DUPLICATE_NAME_ERR;
			exit(EXIT_SUCCESS);
		}
	empty_field_error(name);
}

void Library::check_title(string name)
{
	for(int i=0; i<documents.size(); i++)
		if(documents[i]->is_my_title(name))
		{
			cerr << DUPLICATE_TITLE_ERR;
			exit(EXIT_SUCCESS);
		}
	empty_field_error(name);
}

void Library::check_magazine_specs(int number, int year)
{
	if(number <= 0)
	{
		cerr << INVALID_NUMBER_ERR;
		exit(EXIT_SUCCESS);
	} 

	if(year <= 0)
	{
		cerr << INVALID_YEAR_ERR;
		exit(EXIT_SUCCESS);
	} 
}

void Library::empty_field_error(string field)
{
	if(field == "")
	{
		cerr << EMPTY_FIELD_ERR;
		exit(EXIT_SUCCESS);
	}
}

void Library::add_student_member(string student_id, string student_name)
{
	empty_field_error(student_id);
	check_name(student_name);
	members.push_back(new Student(student_name, student_id));
}

void Library::add_prof_member(string prof_name)
{

	check_name(prof_name);
	members.push_back(new Prof(prof_name));
}

void Library::add_book(string book_title, int copies)
{
	check_title(book_title);
	documents.push_back(new Book(book_title, copies));
}

void Library::add_magazine(string magazine_title, int year, int number, int copies)
{
	check_title(magazine_title);
	check_magazine_specs(number, year);
	documents.push_back(new Magazine(magazine_title, year, number, copies));
}

void Library::add_reference(string reference_title, int copies)
{
	check_title(reference_title);
	documents.push_back(new Reference(reference_title, copies));
}

void Library::borrow(string member_name, string document_title)
{
	int member_index = find_member(member_name);
	int doc_index = find_document(document_title);

	if(member_index < 0 || doc_index < 0) return;

	members[member_index]->borrow(documents[doc_index]);
	documents[doc_index]->borrow();
}  

void Library::extend(string member_name, string document_title)
{
	int member_index = find_member(member_name);

	if(member_index < 0) return;

	members[member_index]->extend(document_title);
}

void Library::return_document(string member_name, string document_title)
{
	int member_index = find_member(member_name);

	if(member_index < 0) return;

	members[member_index]->return_doc(document_title);
}

int Library::get_total_penalty(string member_name)
{
	int member_index = find_member(member_name);

	return members[member_index]->get_total_penalty();
}	

vector<string> Library::available_titles()
{
	vector<string> available_docs;

	for(int i=0; i<documents.size(); i++)
	{
		if(documents[i]->is_available()) 
			available_docs.push_back(documents[i]->get_title());
	}
	return available_docs;
}

void Library::time_pass(int days)
{
	if(days < 0)
	{
		cerr << INVALID_DAY_ERR;
		exit(EXIT_SUCCESS);
	}

	for(int i=0; i<members.size(); i++)
		members[i]->time_pass(days);
}

int Library::find_member(string name)
{
	for(int i=0; i<members.size(); i++)
		if(members[i]->is_my_name(name)) return i;

	return -1;
}

int Library::find_document(string title)
{
	for(int i=0; i<documents.size(); i++)
		if(documents[i]->is_my_title(title)) return i;

	return -1;
}
