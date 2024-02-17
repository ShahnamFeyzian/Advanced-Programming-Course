#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include"Error.hpp"
#include<vector>

class Object
{
public:
	Object(int _id);
	bool is_id(int _id);
	virtual int calc_cost() = 0;
	virtual int calc_weight() = 0;
	virtual void add_to_contents(Object* _obj) = 0;

protected:
	int id;
};


class Product : public Object
{
public:
	Product(int _id, int _cost, int _weight);
	virtual int calc_cost();
	virtual int calc_weight();
	virtual void add_to_contents(Object* _obj);

private:
	int cost;
	int weight;
};


class Box : public Object
{
public:
	Box(int _id);
	virtual int calc_cost();
	virtual int calc_weight();
	virtual void add_to_contents(Object* _obj);

private:
	std::vector<Object*> contents;

};


#endif