#pragma once

#include "_State.h";
#include "GameManager.h";

class StatePlayerTurn : _State {

public:
	void execute_state() {
		this->game_manager = this->machine_ref.Get_Gm();		
	}
};