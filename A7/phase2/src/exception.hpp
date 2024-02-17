#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include<string>

#define EMPTY_MESSAGE "Empty"
#define UNDEFINED_MESSAGE "Not Found"
#define WRONG_REQUEST_MESSAGE "Bad Request"
#define ACCESS_MESSAGE "Permission Denied"
#define SUCCESS_MESSAGE "OK"

class Exception
{
public:
	Exception(std::string _message);
	std::string show_message();

protected:
	std::string message;
};

class Empty_EX : public Exception
{
public:
	Empty_EX();

};

class Undefined_EX : public Exception
{
public:
	Undefined_EX();

};

class WrongRequest_EX : public Exception
{
public:
	WrongRequest_EX();

};

class Access_EX : public Exception
{
public:
	Access_EX();

};

#endif