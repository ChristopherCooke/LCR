#include "GameLoop.h"
#include "StateMachine.h"
#include "GameManager.h"
#include "StateMainMenu.h"

using namespace std;

void OutputFile(std::string filename) {
	std::string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n';
		}
		myfile.close();
	}

	else std::cout << "Unable to locate " << filename << endl << endl;
}

void DisplayTitle()
{
	OutputFile("title.txt");
}

void Game::RunGame()
{
	const int STARTING_CHIPS = 3, INVALID = -1, DIE_COUNT = 3;
	StateMachine* statemachine = new StateMachine;

	DisplayTitle();
	Sleep(1000);

	//Preload state machine with first state and trigger it right away
	
	statemachine->Setup_Gm();
	StateMainMenu* initial_state = new StateMainMenu(statemachine, statemachine->Get_Gm());
	statemachine->Set_Next_State(initial_state);
	while (!statemachine->Get_Game_Over()) {
		statemachine->Execute_Next_State();
	}
	statemachine->Execute_Next_State();	//State machine holds a game over state at this point	

	OutputFile("gameover.txt");
	Sleep(10000);
	system("cls");
}
