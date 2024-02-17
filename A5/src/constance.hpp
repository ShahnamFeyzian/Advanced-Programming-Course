#ifndef _CONSTANCES_
#define _CONSTANCES_

#define FILE_ERROR "there is problem in reading file"
#define EMPTY "."
#define STABLE_ENEMY "S"
#define MOVING_ENEMY "M"
#define HOSTAGE "H"
#define EASY_LEVEL "Easy"
#define MEDIUM_LEVEL "Medium"
#define HARD_LEVEL "Hard"
#define VICTORY_MESSAGE "You won"
#define LOSE_MESSAGE "You lose"
#define NEXT_ROUND_MESSAGE "Get ready for the next round"
#define FONT_ADDRESS "./font/font.otf"
#define STABLE_ENEMY_IMG "./image/stable_enemy.png"
#define MOVING_ENEMY_IMG "./image/moving_enemy.png"
#define PLAYER_IMG "./image/player.png"
#define HOSTAGE_IMG "./image/hostage.png"
#define ENEMY_SHOT_IMG "./image/enemy_shot.png"
#define PLAYER_SHOT_IMG "./image/player_shot.png"
#define SHIELD_POWER_IMG "./image/shield_power.png"
#define FAST_FIRE_POWER_IMG "./image/fast_fire_power.png"
#define EXPLOSION_1_IMG "./image/explosion1.png"
#define EXPLOSION_2_IMG "./image/explosion2.png"
#define EXPLOSION_3_IMG "./image/explosion3.png"
#define EXPLOSION_4_IMG "./image/explosion4.png"
#define BACKGROUND_IMG "./image/back.png"
#define EXPLOSION_SOUND "./sound_effect/explosion.mp3"
#define PLAYER_SHOT_SOUND "./sound_effect/laser_2.mp3"
#define ENEMY_SHOT_SOUND "./sound_effect/laser_1.mp3"
#define BACKGROUND_SOUND "./sound_effect/back.mp3"

const int player_shot_velocity = 3;
const int enemy_shot_velocity = 1;
const int moving_enemy_velocity = 1;
const int player_velocity = 2;
const int player_ship_size = 100;
const int enemy_ship_size = 100;
const int power_icon_size = 35;
const int shot_width = 20;
const int shot_height = 100;
const int loop_delay = 10;
const int enemy_shoot_delay = 2500/loop_delay;

#endif