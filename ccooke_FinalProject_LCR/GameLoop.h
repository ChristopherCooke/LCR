#pragma once

#include "Player.h"
/*
	Problem Statement
	You are playing a card game with friends and decide that you want to keep track of the scores after each round.
	Develop a program that allows you to keep a record.
	The program should first ask for the number of players in the game and the number of rounds to be played.
	Based on the number of players, the program should then ask for the names of the players and write them to a file.
	If no file exists, the program should create one.
	For each of the rounds, the program should accept the scores for each of the players.
	After each round, append the scores to the file
*/

class Game
{
public:
	void RunGame();
};