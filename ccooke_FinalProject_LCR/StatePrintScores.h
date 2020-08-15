#pragma once
#include "_State.h"
#include <iostream>
#include "Player.h"
#include "StatePlayerTurn.h"
#include "stdafx.h"

using namespace std;

class StatePrintScores : public _State {

public:
	StatePrintScores(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	void execute_state() {

		StateMachine* machine = this->machine_ref;
		GameManager* gm = machine->Get_Gm();
		int player_count = gm->Get_Player_Count();
		Player* players = gm->Get_Players();

		//Print score header
		std::cout << "\n---------------------------Scores---------------------------\n";
		for (int score_index = 0; score_index < player_count; score_index++) {
			std::cout << "Player " << score_index + 1 << "\t";
		}
		std::cout << "Center Pot";

		//Print scores
		std::cout << "\n-----------------------------------------------------------\n";
		for (int score_index = 0; score_index < player_count; score_index++) {
			
			std::cout << players[score_index].GetChips() << "\t\t";
		}
		std::cout << ((player_count * gm->STARTING_CHIPS) - gm->winning_chip_count);
		std::cout << "\n-----------------------------------------------------------\n";

		StatePlayerTurn* state = new StatePlayerTurn(this->machine_ref, this->game_manager);
		this->machine_ref->Set_Next_State(state);
	}
};
