#include<string>
#include"rsdl.hpp"
#include"constance.hpp"
enum Direction{ up, down };

class Fire
{
public:
	Fire(int _x, int _y, int _v_y, std::string _img_address, Direction d);
	void move();
	void draw(Window* w);
	int get_x();
	int get_y();
	int get_h();
	int get_w();
	Rectangle get_base();
	
private:
	Rectangle base;
	std::string img_address;
	int v_y;

};