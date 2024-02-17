#include"exception.hpp"
#include<string>
#include<iostream>
using namespace std;

Exception::Exception(string _message)
{
	message = _message;
}

string Exception::show_message()
{
 	return message;
}

Empty_EX::Empty_EX() : Exception(EMPTY_MESSAGE) {}

Undefined_EX::Undefined_EX() : Exception(UNDEFINED_MESSAGE) {}

WrongRequest_EX::WrongRequest_EX() : Exception(WRONG_REQUEST_MESSAGE) {}

Access_EX::Access_EX() : Exception(ACCESS_MESSAGE) {}