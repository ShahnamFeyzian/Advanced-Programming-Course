#include "power.hpp"

BasePower::BasePower(Rectangle _base) : base(_base.x+10, _base.y+60, power_icon_size, power_icon_size)
{
	power_situation = hide;
	time_counter = 0;

}

void BasePower::update_situation(Window* w)
{
	draw(w);
	if(power_situation == show)
	{
		time_counter++;
		if(time_counter >= 5000/loop_delay) power_situation = hide;
	}

	if(power_situation == active)
	{
		time_counter++;
		if(time_counter >= 5000/loop_delay)  power_situation = hide;
	}
}

void BasePower::set_base(Rectangle r)
{
	base.x = r.x+10;
	base.y = r.y+60;
}

void BasePower::show_up() 
{ 
	time_counter = 0;
	power_situation = show; 
}

void BasePower::activate() 
{ 
	time_counter = 0;
	power_situation = active; 
}

Rectangle BasePower::get_base() { return base; }

PowerSituation BasePower::get_situation() { return power_situation; }


ShieldPower::ShieldPower(Rectangle _base) : BasePower(_base) {}

void ShieldPower::draw(Window* w)
{
	if(power_situation == hide) return;

	w->draw_img(SHIELD_POWER_IMG, base);
}

PowerType ShieldPower::get_type() { return shield; }


FastFirePower::FastFirePower(Rectangle _base) : BasePower(_base) {}

void FastFirePower::draw(Window* w)
{
	if(power_situation == hide) return;

	w->draw_img(FAST_FIRE_POWER_IMG, base);
}

PowerType FastFirePower::get_type() { return fast_fire; }

