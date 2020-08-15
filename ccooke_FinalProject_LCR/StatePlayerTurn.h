#pragma once

#include "_State.h"
#include "Player.h"
#include "Die.h"
#include "StateGameOver.h"

class StatePlayerTurn : public _State {

public:
	StatePlayerTurn(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	Player* CheckWin() {
		Player* players = this->game_manager->Get_Players();
		int player_count = this->game_manager->Get_Player_Count();
		int winning_chip_count = this->game_manager->winning_chip_count;

		Player* currentplayer;
		Player* nextplayer = players;
		do {
			currentplayer = nextplayer;
			nextplayer = currentplayer->GetNextPlayer();
			if (currentplayer->GetChips() == winning_chip_count) {
				return currentplayer;
			}
		} while (nextplayer != NULL);
		/*for (int x = 0; x < player_count; x++) {
			if (players[x].GetChips() == winning_chip_count) {
				return x;
			}
		}*/

		return nullptr;
	}
	
	void Get_Next_Player() {
		Player* currentplayer = this->game_manager->Get_Current_Player();
		if (currentplayer->GetNextPlayer() != NULL) {
			this->game_manager->Set_Current_Player(currentplayer->GetNextPlayer());
		}
		else {
			this->game_manager->Set_Current_Player(this->game_manager->Get_Players());
		}
	}


	void execute_state() {
		//Initialize values
		this->game_manager = this->machine_ref->Get_Gm();
		GameManager* gm = this->game_manager;
		Player* currentplayer = gm->Get_Current_Player();
		/*int player_index = gm->Get_Current_Player_Index();
		int player_count = gm->Get_Player_Count();*/
		Die* dice = gm->Get_Dice();

		int chips = currentplayer->GetChips();
		int rolls;
		char* results;

		std::cout << "\n\n=======================Player Turn==========================" << std::endl << std::endl;
		std::cout << "Player " << currentplayer->GetName() << "'s turn. " << std::endl << std::endl;

		//Determine how many die rolls and prepare a results array
		chips > 3 ? rolls = 3 : rolls = chips;
		results = new char[rolls];

		//Prompt player to roll dice
		if (rolls > 0) {
			std::cout << "Press enter to roll the dice." << std::endl << std::endl;
			getchar();
		}
		else {
			std::cout << "Player " << currentplayer->GetName() << " does not have any chips. Skipping turn." << std::endl;
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
				if (currentplayer->GetPreviousPlayer() != NULL) {
					currentplayer->GetPreviousPlayer()->AddChips(1);
				}
				else {
					gm->Get_Last_Player()->AddChips(1);
				}
				currentplayer->RemoveChips(1);
				break;
			case 'R':
				if (currentplayer->GetNextPlayer() != NULL) {
					currentplayer->GetNextPlayer()->AddChips(1);
				}
				else {
					gm->Get_Players()->AddChips(1);
				}
				currentplayer->RemoveChips(1);
				break;
			case 'C':
				currentplayer->RemoveChips(1);
				gm->winning_chip_count -= 1;
			default:
				break;
			}

		}

		//Output footer
		std::cout << "\n==========================End Turn==========================" << std::endl << std::endl;
		Sleep(1000);
		std::cout << "Press enter to continue...";
		getchar();
		std::cin.clear();
		system("cls");

		if (CheckWin() == NULL) {
			Get_Next_Player();
			StateMachine* machine = this->machine_ref;
			machine->Set_Next_State(machine->Get_Circular_State());
		}
		else {
			StateGameOver* state = new StateGameOver(this->machine_ref, this->game_manager);
			this->machine_ref->Set_Next_State(state);
			this->machine_ref->Set_Game_Over(true);
			this->machine_ref->Get_Gm()->winning_player = this->machine_ref->Get_Gm()->Get_Current_Player();
		}
	}
};
