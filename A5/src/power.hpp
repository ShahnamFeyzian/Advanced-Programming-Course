#include "rsdl.hpp"
#include "constance.hpp"

enum PowerSituation { hide, show, active };
enum PowerType { shield, fast_fire };

class BasePower
{
public:
	BasePower(Rectangle _base);
	virtual void draw(Window* w) = 0;
	virtual PowerType get_type() = 0;
	void update_situation(Window* w);
	void show_up();
	void activate();
	void set_base(Rectangle r);
	Rectangle get_base();
	PowerSituation get_situation();

protected:
	Rectangle base;
	PowerSituation power_situation;
	int time_counter;

};

class ShieldPower : public BasePower
{
public:
	ShieldPower(Rectangle _base);
	virtual void draw(Window* w);
	virtual PowerType get_type();

private:

};

class FastFirePower : public BasePower
{
public:
	FastFirePower(Rectangle _base);
	virtual void draw(Window* w);
	virtual PowerType get_type();

private:

};



