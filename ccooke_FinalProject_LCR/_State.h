#pragma once
#include "StateMachine.h"
#include "GameManager.h"

class StateMachine;
class _State {
protected:
	StateMachine* machine_ref;
	GameManager* game_manager;	
public:
	_State(StateMachine* ref1, GameManager* ref2) {
		machine_ref = ref1;
		game_manager = ref2;
	}
	virtual void execute_state() = 0;
};