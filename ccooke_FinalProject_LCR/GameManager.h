#pragma once

#include "Player.h"
#include "Die.h"

class GameManager {
	
	
	Player dummy_player = Player();
	std::string empty;
	bool shouldEnd = false;
	Player* players;
	Die* dice;
	Player* lastplayer;

	public:
		const int STARTING_CHIPS = 3, INVALID = -1, DIE_COUNT = 3, MIN_PLAYERS = 3;
		Player* winning_player;
		Player* current_player;
		int player_count = INVALID;
		int winning_chip_count;
		void Set_Player_Count(int count) {
			player_count = count;
		}
		bool Is_Player_Count_Valid() {
			if (player_count >= MIN_PLAYERS) return true;
			return false;
		}
		//Legacy
		void Create_Players_Array() {
			players = new Player[player_count];
			for (int x = 0; x < player_count; x++) {
				Player player = Player();
				players[x] = player;

			}
			current_player = 0;
			winning_chip_count = player_count * STARTING_CHIPS;	//Denote the chips needed to win
			winning_player = nullptr;
		}
		void Initialize_Players() {
			winning_chip_count = player_count * STARTING_CHIPS;	//Denote the chips needed to win
			winning_player = nullptr;
			Player* lastref = nullptr;

			//Setup linked list of players
			for (int x = 0; x < player_count; x++) {
				if (x == 0) {	//First player
					players = new Player();
					current_player = players;
					lastref = players;
				}
				else {
					Player* newplayer = new Player();
					lastref->SetNextPlayer(newplayer);					
					newplayer->SetPreviousPlayer(lastref);
					lastplayer = newplayer;
					lastref = newplayer;
				}
			}
		}

		Player* Get_Last_Player() {
			return lastplayer;
		}
		bool Get_Game_Over() {
			return shouldEnd;
		}
		Player* Get_Players() {
			return players;
		}
		Player* Get_Player(int index) {
			return &players[index];
		}
		int Get_Player_Count() {
			return player_count;
		}
		int* Get_Player_Count_Ref() {
			return &player_count;
		}
		void Set_Current_Player(Player* player) {
			current_player = player;
		}
		Player* Get_Current_Player() {
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
		Player* Get_Winning_Player() {
			return winning_player;
		}
};