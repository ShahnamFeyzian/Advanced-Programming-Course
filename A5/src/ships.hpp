#include"base_ship.hpp"


class PlayerShip : public BaseShip
{
public:
	PlayerShip(int _x, int _y);
	void handle_key_press(char key);
	void handle_key_release(char key);
	void speed_up(char key);
	void stop(char key);
	void active_power();
	void inactive_power();
	virtual void move(Window* w);
	virtual void draw(Window* w);
	virtual void shoot();

private:
	bool can_shot;
	bool fast_fire_power;
};


class StableEnemy : public BaseShip
{
public:
	StableEnemy(int _x, int _y);
	virtual void move(Window* w);
	virtual void draw(Window* w);
	virtual void shoot();

private:

};


class MovingEnemy : public BaseShip
{
public:
	MovingEnemy(int _x, int _y, int dir);
	virtual void move(Window* w);
	virtual void draw(Window* w);
	virtual void shoot();

private:

};


class HostageShip : public BaseShip
{
public:
	HostageShip(int _x, int _y);
	virtual void move(Window* w);
	virtual void draw(Window* w);
	virtual void shoot();

private:

};



