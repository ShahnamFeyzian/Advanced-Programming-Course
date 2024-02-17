#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define EMPTY '.'
#define ROCK '#'
#define TARGET '*'
#define START_POSE_R 1
#define START_POSE_C 1
#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
#define RIGHT 'r'

typedef struct Position
{
	int r, c;
}Position;

typedef struct Position_Data
{
	Position p;
	char direction;
}Position_Data;

vector<string> set_and_get_map();
int find_shortest_path(Position panda_pose, const vector<string>&map);
int direct_movement(Position panda_pose, char direction, const vector<string>&map, vector<Position_Data> history, int counter);
char look_at(Position panda_pose, char direction, const vector<string>&map);
int look_around(Position panda_pose, char&direction, const vector<string>&map);
void move(Position&panda_pose, int&counter, char direction);
bool check_movement_history(Position panda_pose, char direction, vector<Position_Data> history);
Position_Data set_position_data(int row, int column, char direction);
int right_answer(int a, int b);

int main()
{
	vector<string> map = set_and_get_map();
	Position panda_pose = { START_POSE_R, START_POSE_C };
	
	int min = find_shortest_path(panda_pose, map);

	if (min == -1) cout << "No path found";
	else cout << min;
	return 0;
}



vector<string> set_and_get_map()
{
	vector<string> map;
	string  line, floor="";
	
	cin >> line;
	for (int i = 0; i < line.size() + 2; i++) floor += ROCK;
	map.push_back(floor);

	do
	{
		map.push_back((ROCK + line + ROCK));
	} while (cin >> line);
	map.push_back(floor);

	return map;
}


int find_shortest_path(Position panda_pose, const vector<string>&map)
{
	int path[4] = { -1, -1, -1, -1 };
	vector<Position_Data> history;
	Position_Data movement_data;

	movement_data.p.r = panda_pose.r;
	movement_data.p.c = panda_pose.c;

	if (look_at(panda_pose, UP, map) != ROCK)
	{
		movement_data.direction = UP;
		history.push_back(movement_data);
		path[0] = direct_movement(panda_pose, UP, map, history, 0);
	}
	if (look_at(panda_pose, DOWN, map) != ROCK)
	{
		movement_data.direction = DOWN;
		history.push_back(movement_data);
		path[1] = direct_movement(panda_pose, DOWN, map, history, 0);
	}
	if (look_at(panda_pose, RIGHT, map) != ROCK)
	{
		movement_data.direction = RIGHT;
		history.push_back(movement_data);
		path[2] = direct_movement(panda_pose, RIGHT, map, history, 0);
	}
	if (look_at(panda_pose, LEFT, map) != ROCK)
	{
		movement_data.direction = LEFT;
		history.push_back(movement_data);
		path[3] = direct_movement(panda_pose, LEFT, map, history, 0);
	}

	return right_answer(right_answer(path[0], path[1]), right_answer(path[2], path[3]));
}


int direct_movement(Position panda_pose, char direction, const vector<string>&map, vector<Position_Data> history, int counter)
{
	while (true)
	{
		move(panda_pose, counter, direction);
		if (map[panda_pose.r][panda_pose.c] == TARGET) return counter;
		history.push_back(set_position_data(panda_pose.r, panda_pose.c, direction));
		if (check_movement_history(panda_pose, direction, history)) return -1;
		if (look_at(panda_pose, direction, map) == ROCK)
		{
			int situation = look_around(panda_pose, direction, map);
			if (situation == -1) return -1;
			if (situation == 1)
			{
				char d1, d2;
				if (direction == UP || direction == DOWN)
				{
					d1 = RIGHT;
					d2 = LEFT;
				}
				else
				{
					d1 = UP;
					d2 = DOWN;
				}
				int a = direct_movement(panda_pose, d1, map, history, counter);
				int b = direct_movement(panda_pose, d2, map, history, counter);

				return right_answer(a, b);
			}
		}
	}
}


char look_at(Position panda_pose, char direction, const vector<string>&map)
{
	if (direction == UP) return (map[panda_pose.r - 1][panda_pose.c]);
	if (direction == DOWN) return (map[panda_pose.r + 1][panda_pose.c]);
	if (direction == RIGHT) return (map[panda_pose.r][panda_pose.c + 1]);
	if (direction == LEFT) return (map[panda_pose.r][panda_pose.c - 1]);
}


int look_around(Position panda_pose, char&direction, const vector<string>&map)
{
	if (direction == UP || direction == DOWN)
	{
		char r = look_at(panda_pose, RIGHT, map), l = look_at(panda_pose, LEFT, map);
		if (r == ROCK && l == ROCK) return -1;
		if (r == ROCK && l != ROCK) direction = LEFT;
		if (r != ROCK && l == ROCK) direction = RIGHT;
		if (r != ROCK && l != ROCK) return 1;
	}
	else
	{
		char u = look_at(panda_pose, UP, map), d = look_at(panda_pose, DOWN, map);
		if (u == ROCK && d == ROCK) return -1;
		if (u == ROCK && d != ROCK) direction = DOWN;
		if (u != ROCK && d == ROCK) direction = UP;
		if (u != ROCK && d != ROCK) return 1;
	}
	return 0;
}


void move(Position&panda_pose, int&counter, char direction)
{
	if (direction == UP) panda_pose.r--;
	if (direction == DOWN) panda_pose.r++;
	if (direction == RIGHT) panda_pose.c++;
	if (direction == LEFT) panda_pose.c--;
	counter++;
}


bool check_movement_history(Position panda_pose, char direction, vector<Position_Data> history)
{
	for (int i = 0; i < history.size() - 1; i++)
		if ((history[i].p.r == panda_pose.r) && (history[i].p.c == panda_pose.c) && (history[i].direction == direction))
			return true;

	return false;
}


Position_Data set_position_data(int row, int column, char direction)
{
	Position_Data A;
	A.direction = direction;
	A.p.r = row;
	A.p.c = column;
	return A;
}


int right_answer(int a, int b)
{
	if ((a == -1) && (b == -1)) return -1;
	if (a == -1) return b;
	if (b == -1) return a;

	if (a < b) return a;
	else return b;
}