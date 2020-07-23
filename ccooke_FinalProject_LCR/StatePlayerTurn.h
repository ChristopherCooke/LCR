#pragma once

#include "_State.h"
#include "Player.h"
#include "Die.h"
#include "StateGameOver.h"

class StatePlayerTurn : public _State {

public:
	StatePlayerTurn(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	int CheckWin() {
		Player* players = this->game_manager->Get_Players();
		int player_count = this->game_manager->Get_Player_Count();
		int winning_chip_count = this->game_manager->winning_chip_count;

		for (int x = 0; x < player_count; x++) {
			if (players[x].GetChips() == winning_chip_count) {
				return x;
			}
		}

		return -1;
	}
	
	void Get_Next_Player() {
		Player* players = this->game_manager->Get_Players();
		int player_count = this->game_manager->Get_Player_Count();
		int player_index = this->game_manager->Get_Current_Player_Index();
		if (++player_index < player_count) {
			this->game_manager->Set_Current_Player_Index(player_index);
		}
		else {
			this->game_manager->Set_Current_Player_Index(0);
		}
	}


	void execute_state() {
		//Initialize values
		this->game_manager = this->machine_ref->Get_Gm();
		GameManager* gm = this->game_manager;
		Player* players = gm->Get_Players();
		int player_index = gm->Get_Current_Player_Index();
		int player_count = gm->Get_Player_Count();
		Die* dice = gm->Get_Dice();

		int chips = players[player_index].GetChips();
		int rolls;
		char* results;

		std::cout << "\n\n=======================Player Turn==========================" << std::endl << std::endl;
		std::cout << "Player " << player_index + 1 << "'s turn. " << std::endl << std::endl;

		//Determine how many die rolls and prepare a results array
		chips > 3 ? rolls = 3 : rolls = chips;
		results = new char[rolls];

		//Prompt player to roll dice
		if (rolls > 0) {
			std::cout << "Press enter to roll the dice." << std::endl << std::endl;
			getchar();
		}
		else {
			std::cout << "Player " << player_index + 1 << " does not have any chips. Skipping turn." << std::endl;
		}

		//Roll all dice
		for (int die_index = 0; die_index < rolls; die_index++) {
			dice[die_index].roll_die();
			results[die_index] = dice[die_index].get_converted_last_roll();
		}

		//Handle dice results
		for (int result_index = 0; result_index < rolls; result_index++) {
			int receiving_player_index = gm->INVALID;
			std::cout << "Dice roll " << result_index + 1 << " was: ";
			Sleep(500);
			std::cout << results[result_index] << std::endl;
			Sleep(250);
			switch (results[result_index]) {
			case 'L':
				player_index > 0 ? receiving_player_index = player_index - 1 : receiving_player_index = player_count - 1;
				players[player_index].RemoveChips(1);
				break;
			case 'R':
				player_index < (player_count - 1) ? receiving_player_index = player_index + 1 : receiving_player_index = 0;
				players[player_index].RemoveChips(1);
				break;
			case 'C':
				players[player_index].RemoveChips(1);
				gm->winning_chip_count -= 1;
			default:
				break;
			}
			if (receiving_player_index != gm->INVALID) {
				players[receiving_player_index].AddChips(1);
			}
		}

		//Output footer
		std::cout << "\n==========================End Turn==========================" << std::endl << std::endl;
		Sleep(1000);
		std::cout << "Press enter to continue...";
		getchar();
		std::cin.clear();
		system("cls");

		if (CheckWin() == -1) {
			Get_Next_Player();
			StateMachine* machine = this->machine_ref;
			machine->Set_Next_State(machine->Get_Circular_State());
		}
		else {
			StateGameOver* state = new StateGameOver(this->machine_ref, this->game_manager);
			this->machine_ref->Set_Next_State(state);
			this->machine_ref->Set_Game_Over(true);
			this->machine_ref->Get_Gm()->winning_player_index = player_index;
		}
	}
};
