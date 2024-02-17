#include"rsdl.hpp"
#include"power.hpp"
#include"ships.hpp"
#include<fstream>

enum Difficulty { hard=1, medium, easy };

class Game
{
public:
	Game(std::string input_file_address);
	void run();
	
private:
	Window* win;
	PlayerShip* player;
	std::vector<BaseShip*> enemies;
	std::vector<HostageShip*> hostages;
	BasePower* power;
	Difficulty game_level;
	bool game_runing;
	bool wining_flag;
	int height;
	int width;
	int total_round;
	int round_counter;
	int time_counter;
	std::string f_address; 

	void process_event();
	void handle_collisions();
	bool player_shoot_collision();
	bool enemy_shoot_collision();
	bool ships_collision();
	bool power_collision();
	bool collision(Rectangle r1, Rectangle r2);
	void handle_situation();
	void map_gen();
	void ships_gen(std::string line, int h);
	void power_gen(int enemy_index);
	void clean_map();
	void read_header();
	void update_player();
	void update_enemies(int counter);
	void update_game(int counter);
	bool check_end_round();
	void lost();
	void free_objects();

};


