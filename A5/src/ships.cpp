#include"ships.hpp"
using namespace std;


PlayerShip::PlayerShip(int _x, int _y) : BaseShip::BaseShip(_x, _y, player_ship_size) 
{
	can_shot = true;
	fast_fire_power = false;
}

void PlayerShip::handle_key_press(char key)
{
	if(key == ' ') shoot();
	else speed_up(key);
}

void PlayerShip::handle_key_release(char key)
{
	if(key == ' ') can_shot = true;
	else stop(key);
}

void PlayerShip::speed_up(char key)
{
	switch(key)
	{
		case 'w' : v_y = -player_velocity; break;
		case 's' : v_y = player_velocity; break;
		case 'd' : v_x = player_velocity; break;
		case 'a' : v_x = -player_velocity; break;
	}
}

void PlayerShip::stop(char key)
{
	switch(key)
	{
		case 'w' :
		case 's' : v_y = 0; break;
		case 'a' :
		case 'd' : v_x = 0; break;
	}
}

void PlayerShip::move(Window* w)
{
	base.x += v_x;
	base.y += v_y; 
	if((base.x + base.w) > w->get_width()) base.x = w->get_width() - base.w;
	if((base.y + base.h) > w->get_height()) base.y = w->get_height() - base.h;
	if(base.x < 0) base.x = 0;
	if(base.y < 0) base.y = 0; 
}

void PlayerShip::draw(Window* w) 
{ 
	w->draw_img(PLAYER_IMG, base); 
}

void PlayerShip::shoot()
{
	if(!can_shot || !is_alive) return;

	int fire_x = base.x + base.w/2;
	int fire_y = base.y;
	Direction d = up;

	if(fast_fire_power) fires.push_back(Fire(fire_x, fire_y, player_shot_velocity*2, PLAYER_SHOT_IMG, d));
	else fires.push_back(Fire(fire_x, fire_y, player_shot_velocity, PLAYER_SHOT_IMG, d));
	can_shot = false;
}

void PlayerShip::active_power() { fast_fire_power = true; }

void PlayerShip::inactive_power() { fast_fire_power = false; }


StableEnemy::StableEnemy(int _x, int _y) : BaseShip::BaseShip(_x, _y, enemy_ship_size) {}

void StableEnemy::move(Window* w) {}

void StableEnemy::draw(Window* w)
{
	w->draw_img(STABLE_ENEMY_IMG, base);
}

void StableEnemy::shoot()
{
	if(!is_alive) return;
	int fire_x = base.x + base.w/2;
	int fire_y = base.y;
	Direction d = down;
	fires.push_back(Fire(fire_x, fire_y, enemy_shot_velocity, ENEMY_SHOT_IMG, d));
}



MovingEnemy::MovingEnemy(int _x, int _y, int dir) : BaseShip::BaseShip(_x, _y, enemy_ship_size)
{
	if(dir%2) v_x = moving_enemy_velocity;
	else v_x = -moving_enemy_velocity;
}

void MovingEnemy::move(Window* w)
{
	base.x += v_x;
	if(((base.x + base.w) >= w->get_width())) v_x = -moving_enemy_velocity;
	else if(base.x <= 0) v_x = moving_enemy_velocity;
}

void MovingEnemy::draw(Window* w)
{
	w->draw_img(MOVING_ENEMY_IMG, base);
}

void MovingEnemy::shoot()
{
	if(!is_alive) return;
	int fire_x = base.x + base.w/2;
	int fire_y = base.y;
	Direction d = down;
	fires.push_back(Fire(fire_x, fire_y, enemy_shot_velocity, ENEMY_SHOT_IMG, d));
}



HostageShip::HostageShip(int _x, int _y) : BaseShip(_x, _y, player_ship_size) {}

void HostageShip::move(Window *w) {}

void HostageShip::draw(Window* w)
{
	w->draw_img(HOSTAGE_IMG, base);	
}

void HostageShip::shoot() {}


