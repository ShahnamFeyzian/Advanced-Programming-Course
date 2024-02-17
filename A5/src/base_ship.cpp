#include"base_ship.hpp"
using namespace std;

BaseShip::BaseShip(int _x, int _y, int size) : base(_x, _y, size, size)
{
	v_x = 0;
	v_y = 0;
	animate_seter = 0;
	is_alive = true;
}

void BaseShip::update_situation(Window* w)
{
	if(is_alive)
	{
		move(w);
		draw(w);
	}
	else explosion_animation(w);

	for(int i=0; i<fires.size(); i++)
	{
		fires[i].move();
		fires[i].draw(w);
		if((fires[i].get_y()+50 < 0) || (fires[i].get_y() > w->get_height()))
		{
			delete_fire(i);
			i--;
		}
	}

}

void BaseShip::delete_fire(int index)
{
	fires.erase(fires.begin() + index);
}

void BaseShip::destroyed()
{
	is_alive = false;
}

void BaseShip::explosion_animation(Window* w)
{
	if(animate_seter > 1000) return;
	animate_seter++;
	if(animate_seter < (1000/loop_delay)/4)
		w->draw_img(EXPLOSION_1_IMG, base);
	else if(animate_seter < (1000/loop_delay)/2)
			w->draw_img(EXPLOSION_2_IMG, base);
	else if(animate_seter < (1000/loop_delay)/4*3)
		w->draw_img(EXPLOSION_3_IMG, base);
	else if(animate_seter < (1000/loop_delay))
		w->draw_img(EXPLOSION_4_IMG, base);

}

Rectangle BaseShip::get_base() { return base; }
vector<Fire> BaseShip::get_fires() { return fires; }
bool BaseShip::get_is_alive() { return is_alive; }