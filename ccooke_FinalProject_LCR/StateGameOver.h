#pragma once
#include "_State.h"
#include <iostream>
#include <fstream>
#include "stdafx.h"

class StateGameOver : public _State {

public:
	StateGameOver(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	
	void execute_state() {
		//Display Winner
		std::cout << "Winning player is: Player " << this->machine_ref->Get_Gm()->Get_Winning_Player_Index() + 1;
	}
};
