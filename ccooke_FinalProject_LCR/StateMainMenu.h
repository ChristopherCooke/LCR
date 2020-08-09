#pragma once

#include "_State.h";
#include "GameManager.h";
#include <string>;
#include "GameLoop.h"
#include <iostream>
#include <fstream>
#include "stdafx.h"
#include "StateSetupPlayers.h"


using namespace std;

class StateMainMenu : public _State {

public:
	StateMainMenu(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
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

	void DisplayRecordedScores() 
	{
		OutputFile("scores.csv");
	}

	//Welcome the player
	void DisplayRules()
	{
		OutputFile("rules.txt");
	}
	

	void DisplayMenu()
	{
		cout << "\nOptions - Please choose from the following" << endl << endl;
		cout << "1. Play Game" << endl;
		cout << "2. Read Rules" << endl;
		cout << "3. High Scores" << endl;
	}

	//Gather player input
	void GetPlayerInput(string& playerInput) const
	{
		cin >> playerInput;
	}

	void execute_state() {

		string selection;
		do {
			DisplayMenu();
			GetPlayerInput(selection);
			switch (stoi(selection)) {
			case 1:
				system("cls");
				cout << endl << "Loading Game";
				for (int x = 0; x < 10; x++) {
					Sleep(250);
					cout << ".";
				}
				cout << endl << endl;
				system("cls");
				break;
			case 2:
				system("cls");
				DisplayRules();
				Sleep(1000);
				cout << "\nPress enter to continue...";
				getchar();
				getchar();
				system("cls");
				break;
			case 3:
				system("cls");
				DisplayRecordedScores();
				Sleep(1000);
				cout << "\nPress enter to continue...";
				getchar();
				getchar();
				system("cls");
				break;
			default:
				cout << "Invalid selection! Please try again." << endl << endl;
				break;
			}
		} while (selection != "1");

		StateMachine* machine = this->machine_ref;
		StateSetupPlayers* state = new StateSetupPlayers(machine, machine->Get_Gm());
		machine->Set_Next_State(state);
	}
};