#ifndef __LIBRARY_HH__
#define __LIBRARY_HH__

#include"Person.hpp"
#include"Document.hpp"
#include"Error.hpp"
#include <vector>
#include <string>


class Library {
public:
	void add_student_member(std::string student_id, std::string student_name);
	void add_prof_member(std::string prof_name);
	void add_book(std::string book_title, int copies);
	void add_magazine(std::string magazine_title, int year, int number, int copies);
	void add_reference(std::string reference_title, int copies);
	void borrow(std::string member_name, std::string document_title);
	void extend(std::string member_name, std::string document_title);
	void return_document(std::string member_name, std::string document_title);
	int get_total_penalty(std::string member_name);
	std::vector<std::string> available_titles();
	void time_pass(int days);
private:
    std::vector<Person*> members;
    std::vector<Document*> documents;


    void check_name(std::string name);
    void check_title(std::string name);
    void check_magazine_specs(int number, int year);
    void empty_field_error(std::string field);
    int find_member(std::string name);
    int find_document(std::string title);
};

#endif