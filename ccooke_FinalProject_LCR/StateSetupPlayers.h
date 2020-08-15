#pragma once

#include "_State.h"
#include <iostream>
#include "StatePrintScores.h"

class StateSetupPlayers : public _State {

public:
	StateSetupPlayers(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	void Prompt_Player_Count(int* player_count) {
		std::cout << "Enter player count: ";
		std::cin >> *player_count;
		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "You must enter an integer value. Please try again." << std::endl;
			std::cout << "Enter player count: ";
			std::cin >> *player_count;
		}
	}
	void Setup_Players() {
		GameManager* gm = this->game_manager;

		do {
			Prompt_Player_Count(this->game_manager->Get_Player_Count_Ref());
			if (*gm->Get_Player_Count_Ref() < 3) {
				std::cout << "Invalid player count. Game requires at least three players." << std::endl;
				gm->Set_Player_Count(gm->INVALID);
				std::cin.clear();
				std::cin.clear();
			}
			
		} while (gm->player_count == gm->INVALID);

		gm->Create_Players_Array();
		std::cout << std::endl << std::endl;
		std::cin.clear();
		std::cin.clear();	//Me cheating to flush the buffer

		//Set starting chips for each player
		for (int x = 0; x < gm->Get_Player_Count(); x++) {
			gm->Get_Player(x)->SetChips(3);
		}
	}
	void execute_state() {
		
		Setup_Players();
		
		StateMachine* machine = this->machine_ref;
		StatePrintScores* state = new StatePrintScores(machine, machine->Get_Gm());
		machine->Get_Gm()->Set_Dice(3);
		machine->Set_Next_State(state);
		this->machine_ref->Set_Circular_State(state);	//Resolve circular dependency issue
	}
};