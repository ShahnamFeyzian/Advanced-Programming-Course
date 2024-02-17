#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include"game.hpp"
using namespace std;

Game::Game(string input_file_address) 
{
	f_address = input_file_address;
	read_header();
	
	round_counter = 1;
	win = new Window(width*100, height*100);
	player = new PlayerShip((width/2)*100, (height-1)*100);
	power = new ShieldPower(player->get_base());
	map_gen();
	game_runing = true;
	wining_flag = true;
	time_counter = 0;
}

void Game::run()
{
	int loop_counter = 0;
	win->play_music(BACKGROUND_SOUND);
	while(game_runing)
	{	
		win->clear();

		win->draw_img(BACKGROUND_IMG);

		handle_situation();
		
		update_game(loop_counter);

		win->update_screen();
		
		if(loop_counter == enemy_shoot_delay) loop_counter = 0;
		loop_counter++;
		
		delay(loop_delay);
	}
	free_objects();
}

void Game::map_gen()
{
	clean_map();

	ifstream input_file(f_address);
	if(!input_file.is_open())
	{
		cerr << FILE_ERROR << endl;
		exit(0);
	}

	string line;

	for(int i=0; i<2; i++) getline(input_file, line); 
	
	for(int i=0; i<round_counter-1; i++)
		for(int j=0; j<height+2; j++) getline(input_file, line);

	for(int i=0; i<height; i++)
	{
		getline(input_file, line);
		ships_gen(line, i);
	}
	player = new PlayerShip((width/2)*100, (height-1)*100);

	getline(input_file, line);
	if(line == HARD_LEVEL) game_level = hard;
	else if(line == MEDIUM_LEVEL) game_level = medium;
	else if(line == EASY_LEVEL) game_level = easy;
}

void Game::ships_gen(string line, int h)
{
	int y = h*100 + 10;
	for(int i=0; i<width; i++)
	{
		if(line.substr(i, 1) == STABLE_ENEMY) enemies.push_back(new StableEnemy(i*100, y));
		if(line.substr(i, 1) == MOVING_ENEMY) enemies.push_back(new MovingEnemy(i*100, y, enemies.size()));
		if(line.substr(i, 1) == HOSTAGE) hostages.push_back(new HostageShip(i*100, y));
	}
}

void Game::power_gen(int enemy_index)
{
	if(power->get_situation() != hide) return;

	srand(time(0));
	int i = rand()%4;
	
	if(i%2)
	{
		if(i == 1) power = new ShieldPower(enemies[enemy_index]->get_base());
		else power = new FastFirePower(enemies[enemy_index]->get_base());
		power->show_up();
	}
}

void Game::clean_map()
{
	for(int i=0; i<enemies.size(); i++)
	{
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
		i--;
	}
	for(int i=0; i<hostages.size(); i++)
	{
		delete hostages[i];
		hostages.erase(hostages.begin() + i);
		i--;
	}
	delete player;
}

void Game::process_event()
{
	if(win->has_pending_event())
	{
		Event e = win->poll_for_event();
		switch(e.get_type())
		{
			case Event::QUIT:
				game_runing = false;
				break;

			case Event::KEY_PRESS:
			{
				if(e.get_pressed_key() == ' ') win->play_sound_effect(PLAYER_SHOT_SOUND);
				player->handle_key_press(e.get_pressed_key());
				break;
			}
			case Event::KEY_RELEASE:
				player->handle_key_release(e.get_pressed_key());
				break;
		}
	}

}

void Game::handle_collisions()
{
	if(player_shoot_collision()||
	   enemy_shoot_collision()||
	   ships_collision()) win->play_sound_effect(EXPLOSION_SOUND);

	if(power_collision()) power->activate();
}

bool Game::player_shoot_collision()
{
	vector<Fire> player_fires = player->get_fires();
	for(int i=0; i<enemies.size(); i++)
	{
		if(!enemies[i]->get_is_alive()) continue;
		for(int j=0; j<player_fires.size(); j++)
		{
			if(collision(player_fires[j].get_base(), enemies[i]->get_base()))
			{
				player->delete_fire(j);
				player_fires.erase(player_fires.begin() + j);
				j--;
				enemies[i]->destroyed();
				power_gen(i);
				return true;
			}
		}
	}

	for(int i=0; i<hostages.size(); i++)
		for(int j=0; j<player_fires.size(); j++)
			if(collision(player_fires[j].get_base(), hostages[i]->get_base()))
			{
				player->delete_fire(j);
				hostages[i]->destroyed();
				lost();
				return true;
			}
	return false;
}

bool Game::enemy_shoot_collision()
{
	if(!player->get_is_alive()) return false;
	if(power->get_situation() == active && power->get_type() == shield) return false;

	for(int i=0; i<enemies.size(); i++)
	{
		vector<Fire> enemy_fires = enemies[i]->get_fires();
		for(int j=0; j<enemy_fires.size(); j++)
		{
			if(collision(enemy_fires[j].get_base(), player->get_base()))
			{
				player->destroyed();
				enemies[i]->delete_fire(j);
				lost();
				return true;
			}
		}
	}
	return false;
}

bool Game::ships_collision()
{
	if(!player->get_is_alive()) return false;

	for(int i=0; i<enemies.size(); i++)
	{
		if(!enemies[i]->get_is_alive()) continue;
		if(collision(player->get_base(), enemies[i]->get_base()))
		{
			enemies[i]->destroyed();
			player->destroyed();
			lost();
			return true;
		}
	}

	for(int i=0; i<hostages.size(); i++)
		if(collision(player->get_base(), hostages[i]->get_base()))
		{
			hostages[i]->destroyed();
			player->destroyed();
			lost();
			return true;
		}
	return false;
}

bool Game::power_collision()
{
	if(power->get_situation() != show) return false;
	if(collision(power->get_base(), player->get_base())) return true;
	return false;
}

bool Game::collision(Rectangle r1, Rectangle r2)
{
	r1.x += 35; r1.w -= 35; r1.y += 35; r1.h -= 35;
	r2.x += 35; r2.w -= 35; r2.y += 35; r2.h -= 35;

	if(((r1.x > r2.x) && (r1.x < r2.x+r2.w)) || 
	  ((r1.x+r1.w > r2.x) && (r1.x+r1.w < r2.x+r2.w)))
	{
		if(((r1.y > r2.y) && (r1.y < r2.y+r2.h)) || 
		  ((r1.y+r1.h > r2.y) && (r1.y+r1.h < r2.y+r2.h)))
			return true;
	}
	
	return false;
}

void Game::read_header()
{
	ifstream input_file(f_address);
	if(!input_file.is_open())
	{
		cerr << FILE_ERROR << endl;
		exit(0);
	}

	string line;
	
	getline(input_file, line);
	height = stoi(line.substr(0, 1));
	width = stoi(line.substr(2, 1));
	
	getline(input_file, line);
	total_round = stoi(line);

}

void Game::update_game(int counter)
{
	update_player();

	power->update_situation(win);

	update_enemies(counter);
	
	for(int i=0; i<hostages.size(); i++) hostages[i]->update_situation(win);
	
	handle_collisions();
}

void Game::update_player()
{
	process_event();
	player->update_situation(win);
	player->inactive_power();
	if(power->get_situation() == active) 
	{
		power->set_base(player->get_base());
		if(power->get_type() == fast_fire) player->active_power(); 
	}		
}

void Game::update_enemies(int counter)
{
	vector<int> index;
	bool can_shoot = true;
	for(int i=0; i<game_level; i++)
	{
		srand(time(0));
		index.push_back((rand()+(player->get_base().x*i))%width);
	}
	for(int i=0; i<game_level-1; i++)
		if(index[i] == index[i+1]) index[i+1] = (index[i]+i+1)%width;

	for(int i=0; i<enemies.size(); i++)
	{
		for(int j=0; j<game_level; j++) 
			if(enemies[i]->get_base().x == index[j]*100) can_shoot = false; 

		if((counter == enemy_shoot_delay) && can_shoot)
		{ 
			enemies[i]->shoot();
		}	
		enemies[i]->update_situation(win);
		can_shoot = true;
	}

}

bool Game::check_end_round()
{
	for(int i=0; i<enemies.size(); i++)
		if(enemies[i]->get_is_alive()) return false;

	if(round_counter > total_round) game_runing = false;
	return true;

}

void Game::lost()
{
	wining_flag = false;
}

void Game::handle_situation()
{
	if(!wining_flag)
	{
		win->show_text(LOSE_MESSAGE, Point((width/2-1)*100, (height/2)*100), RED, FONT_ADDRESS);
		time_counter++;
		if(time_counter > 5000/loop_delay) 
			{
				time_counter = 0;
				game_runing = false;
				return;
			}
	}

	if(check_end_round())
	{
		if(round_counter >= total_round) win->show_text(VICTORY_MESSAGE, Point((width/2-1)*100, (height/2)*100), RED, FONT_ADDRESS);
		else win->show_text(NEXT_ROUND_MESSAGE, Point(10, 10), RED, FONT_ADDRESS);

		time_counter++;
		if(time_counter > 5000/loop_delay) 
			{
				time_counter = 0;
				round_counter++;
				map_gen();
			}
	}

}

void Game::free_objects()
{
	clean_map();
	delete win;
}


