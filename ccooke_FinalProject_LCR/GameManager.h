#pragma once

#include "Player.h"
#include "Die.h"

class GameManager {
	
	int current_player, winning_player_index;
	int player_count = INVALID;	
	Player dummy_player = Player();
	std::string empty;
	bool shouldEnd = false;
	Player* players;
	Die* dice;

	public:
		const int STARTING_CHIPS = 3, INVALID = -1, DIE_COUNT = 3, MIN_PLAYERS = 3;
		int winning_chip_count;
		void Set_Player_Count(int count) {
			player_count = count;
		}
		bool Is_Player_Count_Valid() {
			if (player_count >= MIN_PLAYERS) return true;
			return false;
		}
		void Create_Players_Array() {
			players = new Player[player_count];
			current_player = 0;
			winning_chip_count = player_count * STARTING_CHIPS;	//Denote the chips needed to win
			winning_player_index = INVALID;
		}
		bool Get_Game_Over() {
			return shouldEnd;
		}
		Player* Get_Players() {
			return players;
		}
		Player Get_Player(int index) {
			return players[index];
		}
		int Get_Player_Count() {
			return player_count;
		}
		int* Get_Player_Count_Ref() {
			return &player_count;
		}
		void Set_Current_Player_Index(int index) {
			current_player = index;
		}
		int Get_Current_Player_Index() {
			return current_player;
		}
		Player* Get_Dummy_Player() {
			return &dummy_player;
		}
		std::string* Get_Empty() {
			return &empty;
		}
		void Set_Dice(int count) {
			dice = new Die[count];
			for (int x = 0; x < count; x++) {
				dice[x].seed_die();
			}
		}
		Die* Get_Dice() {
			return dice;
		}
		int Get_Winning_Player_Index() {
			return winning_player_index;
		}
};