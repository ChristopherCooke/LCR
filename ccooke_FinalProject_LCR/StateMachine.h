#pragma once

#include <stdlib.h>
#include "_State.h"
#include "GameManager.h";

class StateMachine {
	_State* current_state;
	_State* next_state;
	GameManager* gm;
	bool game_over = false;
	
public:
	StateMachine* self;
	bool Get_Game_Over() {
		return game_over;
	}
	void Setup_Gm() {
		gm = new GameManager;
	}
	GameManager* Get_Gm() {
		return gm;
	}
	void Set_Next_State(_State* state) {
		next_state = state;
	}
	void Execute_Next_State() {
		current_state = next_state;
		current_state->execute_state();
	}
};