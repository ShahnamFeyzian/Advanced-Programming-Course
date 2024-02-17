#include"fire.hpp"
using namespace std;

Fire::Fire(int _x, int _y, int _v_y, string _img_address, Direction d) : base(_x, _y, shot_width, shot_height)
{
	img_address = _img_address;
	if(d == up) v_y = -_v_y;
	else v_y = _v_y;
}

void Fire::move()
{
	base.y += v_y;
}

void Fire::draw(Window* w)
{
	w->draw_img(img_address, base);
}

int Fire::get_x() { return base.x; }
int Fire::get_y() { return base.y; }
int Fire::get_h() { return base.h; }
int Fire::get_w() { return base.w; }
Rectangle Fire::get_base() { return base; }

