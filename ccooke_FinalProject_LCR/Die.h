#pragma once

#include <stdlib.h>
#include <ctime>

class Die {
	int last_roll;
	const int NUM_SIDES = 6;
public:
	void seed_die() {
		//Seed the randomizer
		srand(time(0));
	}
	void roll_die() {
		last_roll = rand() % NUM_SIDES + 1;	//Add 1 to make it 1-6 instead of 0-5
	}
	int get_last_roll() {
		return last_roll;
	};
	char get_converted_last_roll() {
		int roll = get_last_roll();
		switch (roll) {
			case 1:
				return 'L';
			case 2:
				return 'C';
			case 3:
				return 'R';
			default:
				return '*';
		}
	}

};