#include "GameLoop.h"
#include "GameActions.h"
#include "Die.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

void OutputFile(string filename) {
	string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to locate " << filename << endl << endl;
}
//Welcome the player
void Game::DisplayRules()
{
	OutputFile("rules.txt");
}

void Game::DisplayTitle()
{
	OutputFile("title.txt");
}

void Game::DisplayMenu()
{
	cout << "\nOptions - Please choose from the following" << endl << endl;
	cout << "1. Play Game" << endl;
	cout << "2. Read Rules" << endl;
}

//Gather player input
void Game::GetPlayerInput(string& playerInput) const
{
	cin >> playerInput;
}

//Perform the selected action
void Game::PerformAction(GameActions& c_action, int& integer, Player& player, string toWrite) const
{
	string input;
	ofstream myfile;
	static bool append = false;

	switch (c_action) {
	case GameActions::PromptPlayerCount:
		cout << "Enter player count: ";
		cin >> integer;
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "You must enter an integer value. Please try again." << endl;
			cout << "Enter player count: ";
			cin >> integer;
		}
		break;
	default:
		throw new exception("Invalid action selected!");
		break;
	}
}

int Game::CheckWin(Player* players, int& player_count, int& winning_chip_count) {
	for (int x = 0; x < player_count; x++) {
		if (players[x].GetChips() == winning_chip_count) {
			return x;
		}
	}

	return -1;
}

void Game::RunGame()
{
	//Variables
	const int STARTING_CHIPS = 3, INVALID = -1, DIE_COUNT = 3;
	Player manager = Player();
	string empty;
	bool shouldEnd = false;
	int player_count = INVALID, winning_chip_count, winning_player_index;
	Player* players;

	DisplayTitle();
	Sleep(1000);

	string selection;
	do {	
		DisplayMenu();
		GetPlayerInput(selection);
		if (selection == "1") {
			system("cls");
			cout << endl << "Loading Game";
			for (int x = 0; x < 10; x++) {
				Sleep(250);
				cout << ".";
			}
			cout << endl << endl;
			system("cls");
		}
		else if (selection == "2") {
			system("cls");
			DisplayRules();
			Sleep(1000);
			cout << "\nPress enter to continue...";	
			getchar();
			getchar();
			system("cls");
		}
		else {
			cout << "Invalid selection! Please try again." << endl << endl;
		}
	} while (selection != "1");

	//Gather the player count
	GameActions next_action = GameActions::PromptPlayerCount;
	do {
		PerformAction(next_action, player_count, manager, empty);
		if (player_count < 3) {
			cout << "Invalid player count. Game requires at least three players." << endl;
			player_count = INVALID;
			cin.clear();
			cin.clear();
		}
	} while (player_count == INVALID);
	
	system("cls");

	players = new Player[player_count];	//Create that many players
	cout << endl << endl;
	cin.clear();	//Me cheating to flush the buffer

	//Set starting chips for each player
	for (int x = 0; x < player_count; x++) {
		players[x].SetChips(STARTING_CHIPS);
	}

	//Initialize dice
	Die* dice;
	dice = new Die[DIE_COUNT];
	for (int x = 0; x < DIE_COUNT; x++) {
		dice[x].seed_die();
	}

	winning_chip_count = player_count * STARTING_CHIPS;	//Denote the chips needed to win

	winning_player_index = CheckWin(players, player_count, winning_chip_count);	//Initialize winning index

	while (winning_player_index == INVALID) {
		//Foreach player
		for (int player_index = 0; player_index < player_count; player_index++) {
			//Initialize values
			int chips = players[player_index].GetChips();
			int rolls;
			char* results;

			//Print score header
			cout << "\n---------------------------Scores---------------------------\n";
			for (int score_index = 0; score_index < player_count; score_index++) {
				cout << "Player " << score_index + 1 << "\t";
			}
			cout << "Center Pot";

			//Print scores
			cout << "\n-----------------------------------------------------------\n";
			for (int score_index = 0; score_index < player_count; score_index++) {
				cout << players[score_index].GetChips() << "\t\t";
			}
			cout << ((player_count * STARTING_CHIPS) - winning_chip_count);
			cout << "\n-----------------------------------------------------------\n";

			cout << "\n\n=======================Player Turn==========================" << endl << endl;			
			cout << "Player " << player_index + 1 << "'s turn. "<< endl << endl;

			//Determine how many die rolls and prepare a results array
			chips > 3 ? rolls = 3 : rolls = chips;			
			results = new char[rolls];

			//Prompt player to roll dice
			if (rolls > 0) {
				cout << "Press enter to roll the dice." << endl << endl;
				getchar();
			}
			else {
				cout << "Player " << player_index + 1 << " does not have any chips. Skipping turn." << endl;
			}
			

			//Roll all dice
			for (int die_index = 0; die_index < rolls; die_index++) {
				dice[die_index].roll_die();
				results[die_index] = dice[die_index].get_converted_last_roll();
			}

			//Handle dice results
			for (int result_index = 0; result_index < rolls; result_index++) {
				int receiving_player_index = INVALID;
				cout << "Dice roll " << result_index + 1 << " was: ";
				Sleep(500);
				cout << results[result_index] << endl;
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
						winning_chip_count -= 1;
					default:
						break;
				}
				if (receiving_player_index != INVALID) {
					players[receiving_player_index].AddChips(1);
				}
			}

			//Output footer
			cout << "\n==========================End Turn==========================" << endl << endl;
			Sleep(1000);
			cout << "Press enter to continue...";
			getchar();
			cin.clear();
			system("cls");

			//Check for winner and break out of loop if one exists
			winning_player_index = CheckWin(players, player_count, winning_chip_count);
			if (winning_player_index != INVALID) {
				break;	//Break out of loop if we have a winner
			}
		}
	}

	//Display Winner
	OutputFile("gameover.txt");
	cout << "Winning player is: Player " << winning_player_index + 1;
	OutputFile("gameover.txt");
	Sleep(10000);
	system("cls");
}
