#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define SUCCESS_MESSAGE "ok"
#define UNKNOWN_USER_MESSAGE "user not available"

const int WINING_REWARD = 2700;
const int LOSING_REWARD = 2400;

int alphabetical_comparison(string str1, string str2);

enum GameSituation { lobby, get_ready, fight };
enum PlayerType { terrorist, counter };
enum WeaponType { heavy, pistol, knife };

class Weapon
{
private:
	int damage, price, reward;
	WeaponType type;

public:
	Weapon()
	{
		price = 0;
		damage = 35;
		reward = 500;
		type = knife;
	}
	Weapon(WeaponType init_type)
	{
		if (init_type == heavy)
		{
			price = 3000;
			damage = 45;
			reward = 100;
		}
		else if (init_type == pistol)
		{
			price = 400;
			damage = 20;
			reward = 200;
		}
		type = init_type;

	}

	int get_reward() { return reward; }
	int get_price() { return price; }
	int get_damage() { return damage; }
	WeaponType get_type() { return type; }

};

struct BackPack
{
	vector<Weapon> weapons;
};

class Player
{
private:
	string name;
	int health, money, kills, deaths;
	bool is_afk;
	BackPack back_pack;
	PlayerType type;

public:
	Player(string init_name, PlayerType init_type)
	{
		name = init_name;
		health = 100;
		money = 1000;
		kills = 0;
		deaths = 0;
		is_afk = false;
		back_pack.weapons.push_back(Weapon());
		type = init_type;
	}

	string get_name() { return name; }
	PlayerType get_type() { return type; }
	int get_money() { return money; }
	int get_health() { return health; }
	bool get_afk() { return is_afk; }
	int get_kills() { return kills; }
	int get_deaths() { return deaths; }
	BackPack* get_back_pack() { return &back_pack; }

	void start_round()
	{
		health = 100;
	}
	void dead()
	{
		health = 0;
		vector<Weapon> base;
		base.push_back(Weapon());
		back_pack.weapons = base;
		deaths++;
	}
	void kill(Weapon killer_gun)
	{
		kills++;
		this->add_money(killer_gun.get_reward());
	}
	void won_round()
	{
		this->add_money(WINING_REWARD);
	}
	void lost_round()
	{
		this->add_money(LOSING_REWARD);
	}
	void buy_weapon(Weapon init_weapon)
	{
		if (init_weapon.get_price() > money) return;

		back_pack.weapons.push_back(init_weapon);
		money -= init_weapon.get_price();
	}
	void go_afk() { is_afk = true; }
	void go_atk() { is_afk = false; }
	void to_get_damage(int damage)
	{
		health -= damage;
		if (health <= 0)  this->dead();
	}
	void add_money(int reward)
	{
		money += reward;
		if (money > 10000) money = 10000;
	}
};

class GamePanel
{
private:
	vector<Player> players;
	GameSituation game_situation;


	PlayerType specify_result()
	{
		for (int i = 0; i < players.size(); i++)
			if ((players[i].get_type() == counter) && (players[i].get_health() != 0) && (!players[i].get_afk())) return counter;

		return terrorist;
	}

	void sort_by_score(vector<Player>&player_list)
	{
		for (int i = 0; i < player_list.size(); i++)
			for (int j = i + 1; j < player_list.size(); j++)
			{
				if (player_list[i].get_kills() < player_list[j].get_kills())
					swap(player_list[i], player_list[j]);
				else if (player_list[i].get_kills() == player_list[j].get_kills())
				{
					if (player_list[i].get_deaths() > player_list[j].get_deaths())
						swap(player_list[i], player_list[j]);
					else if (player_list[i].get_deaths() == player_list[j].get_deaths())
					{
						if (alphabetical_comparison(player_list[i].get_name(), player_list[j].get_name()) == 2)
							swap(player_list[i], player_list[j]);
					}
				}
				
			}

	}

	int find_player(string name)
	{
		int i;

		for (i = 0; i < players.size(); i++)
			if (name == players[i].get_name()) break;

		if (i == players.size()) return -1;
		return i;
	}

	void start_round(int num_of_command)
	{
		game_situation = get_ready;
		for (int i = 0; i < players.size(); i++) players[i].start_round();
		for (int i = 0; i < num_of_command; i++)
		{
			string command;
			cin >> command;
			this->get_command(command);
			cout << endl;
		}
		game_situation = lobby;

		if (specify_result() == counter)
		{
			cout << "counter-terrorist won";
			for (int i = 0; i < players.size(); i++)
				if (players[i].get_type() == counter) players[i].won_round();
				else players[i].lost_round();
		}
		else
		{
			cout << "terrorist won";
			for (int i = 0; i < players.size(); i++)
				if (players[i].get_type() == terrorist) players[i].won_round();
				else players[i].lost_round();
		}
	}

	void start_fight()
	{
		game_situation = fight;
		cout << "fight!";
	}

	void add_player(string name, PlayerType type)
	{
		players.push_back(Player(name, type));
		cout << SUCCESS_MESSAGE;
	}

	void get_money(string name)
	{
		int i = find_player(name);
		cout << players[i].get_money();
	}

	void get_health(string name)
	{
		int i = find_player(name);
		cout << players[i].get_health();
	}

	void go_afk(string name)
	{
		int i = find_player(name);
		players[i].go_afk();
		cout << SUCCESS_MESSAGE;
	}

	void go_atk(string name)
	{
		int i = find_player(name);
		players[i].go_atk();
		cout << SUCCESS_MESSAGE;
	}

	void shoot(string attacker, string attacked, WeaponType type)
	{
		if (game_situation != fight)
		{
			cout << "The game hasn't started yet";
			return;
		}

		int attacker_index = find_player(attacker);
		int attacked_index = find_player(attacked);
		if (attacked_index == -1 || attacker_index == -1 ||
			players[attacker_index].get_afk() || players[attacked_index].get_afk())
		{
			cout << UNKNOWN_USER_MESSAGE;
			return;
		}

		if (players[attacker_index].get_health() == 0)
		{
			cout << "attacker is dead";
			return;
		}
		if (players[attacked_index].get_health() == 0)
		{
			cout << "attacked is dead";
			return;
		}

		BackPack* attacker_back_pack = players[attacker_index].get_back_pack();
		Weapon attacker_weapon;
		for (int i = 0; i < attacker_back_pack->weapons.size(); i++)
		{
			if (type == attacker_back_pack->weapons[i].get_type())
			{
				attacker_weapon = attacker_back_pack->weapons[i];
				break;
			}
			else if (i == attacker_back_pack->weapons.size() - 1)
			{
				cout << "attacker doesn't have this gun";
				return;
			}
		}

		if (players[attacked_index].get_type() == players[attacker_index].get_type())
		{
			cout << "you can't shoot this player";
			return;
		}

		players[attacked_index].to_get_damage(attacker_weapon.get_damage());
		if (players[attacked_index].get_health() == 0) players[attacker_index].kill(attacker_weapon);
		cout << "nice shot";
	}

	void buy_weapon(string name, WeaponType type)
	{
		if (game_situation == fight)
		{
			cout << "you can't buy weapons anymore";
			return;
		}

		int player_index = find_player(name);
		if (player_index == -1 || players[player_index].get_afk())
		{
			cout << UNKNOWN_USER_MESSAGE;
			return;
		}

		BackPack* player_back_pack = players[player_index].get_back_pack();
		for (int i = 0; i < player_back_pack->weapons.size(); i++)
		{
			if (player_back_pack->weapons[i].get_type() == type)
			{
				cout << "you already have this weapon";
				return;
			}
		}

		Weapon target_weapon(type);
		if (target_weapon.get_price() > players[player_index].get_money())
		{
			cout << "insufficient money";
			return;
		}

		players[player_index].buy_weapon(target_weapon);
		cout << "weapon bought successfully";
	}

	void show_score_board()
	{
		vector<Player> terrorists, counters;
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].get_type() == terrorist) terrorists.push_back(players[i]);
			else if (players[i].get_type() == counter) counters.push_back(players[i]);
		}

		this->sort_by_score(terrorists);
		this->sort_by_score(counters);

		cout << "counter-terrorist players:\n";
		for (int i = 0; i < counters.size(); i++)
		{
			cout << counters[i].get_name() << " "
			 	 << counters[i].get_kills() << " "
			 	 << counters[i].get_deaths() << endl;
		}

		cout << "terrorist players:\n";
		for (int i = 0; i < terrorists.size(); i++)
		{
			cout << terrorists[i].get_name() << " "
				 << terrorists[i].get_kills() << " "
				 << terrorists[i].get_deaths();
			if (i != terrorists.size() - 1) cout << endl;
		}

	}

public:

	GamePanel()
	{
		game_situation = lobby;
	}

	void get_command(string command)
	{
		if (command == "round")
		{
			int num_of_command;
			cin >> num_of_command;
			start_round(num_of_command);
		}
	    else if (command == "start") start_fight();
		else if (command == "add-user")
		{
			string name, type;
			PlayerType t;
			cin >> name >> type;
			if (type == "terrorist") t = terrorist;
			else t = counter;
			add_player(name, t);
		}
		else if (command == "get-money")
		{
			string name;
			cin >> name;
			get_money(name);
		}
		else if (command == "get-health")
		{
			string name;
			cin >> name;
			get_health(name);
		}
		else if (command == "go-afk")
		{
			string name;
			cin >> name;
			go_afk(name);
		}
		else if (command == "go-atk")
		{
			string name;
			cin >> name;
			go_atk(name);
		}
		else if (command == "shoot")
		{
			string attacker, attacked, gun;
			WeaponType t;
			cin >> attacker >> attacked >> gun;
			if (gun == "heavy") t = heavy;
			else if (gun == "pistol") t = pistol;
			else t = knife;
			shoot(attacker, attacked, t);
		}
		else if (command == "buy")
		{
			string player_name, weapon_name;
			WeaponType t;
			cin >> player_name >> weapon_name;
			if (weapon_name == "heavy") t = heavy;
			else if (weapon_name == "pistol") t = pistol;
			else if (weapon_name == "knife") t = knife;
			else
			{
				cout << "weapon not available";
				return;
			}
			buy_weapon(player_name, t);
		}
		else if (command == "score-board")  show_score_board();
	}

	
};

int main()
{
	GamePanel main_game;
	string command;
	int num_of_rounds;

	cin >> num_of_rounds;

	while(cin >> command)
	{
		main_game.get_command(command);
		cout << endl;
	}
	return 0;
}



int alphabetical_comparison(string str1, string str2)
{
	if (str1 == str2) return 0;
	int index = 0;
	while ((index < str1.size()) && (index < str2.size()))
	{
		if (str1[index] > str2[index]) return 2;
		if (str1[index] < str2[index]) return 1;
		index++;
	}
	if (str1.size() > str2.size()) return 2;
	else return 1;
}