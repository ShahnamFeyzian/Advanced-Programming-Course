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
	virtual int get_code() = 0;

protected:
	std::string message;
};

class Empty_EX : public Exception
{
public:
	Empty_EX();
	virtual int get_code() {return 400;}

};

class Undefined_EX : public Exception
{
public:
	Undefined_EX();
	virtual int get_code() {return 401;}

};

class WrongRequest_EX : public Exception
{
public:
	WrongRequest_EX();
	virtual int get_code() {return 402;}

};

class Access_EX : public Exception
{
public:
	Access_EX();
	virtual int get_code() {return 403;}

};

#endif