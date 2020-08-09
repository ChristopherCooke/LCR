#pragma once
#include "_State.h"
#include "stdafx.h"
#include "Score.h";
#include <ctime>
#include <iostream>

using namespace std;

class StateGameOver : public _State {
private:
	std::string highscoreheader = "Player Name, Winning Chip Count, Date\n";
public:
	StateGameOver(StateMachine* sm, GameManager* gm) : _State(sm, gm) {

	}
	
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

	void append_to_file(std::string record, std::string file) {
		std::ofstream outfile;

		outfile.open(file, std::ios_base::app); // append instead of overwrite
		outfile << record;
	}

	std::vector<Score> GetHighScores(std::string filename) {
		std::vector<Score> scores;
		std::string line;
		ifstream myfile(filename);

		if (myfile.is_open())
		{
			bool header = false;
			while (getline(myfile, line))
			{
				if(header)
				{
					Score score = Score(line);
					scores.push_back(score);
				}
				else {
					header = true;
				}				
			}
			myfile.close();
		}
		else
		{
			ofstream myfile(filename);
			myfile << this->highscoreheader;
			myfile.close();
		}

		return scores;
	}

	string current_time() {
		time_t _tm = time(NULL);
		tm * curtime = new tm;
		localtime_s(curtime, &_tm);
		char str_time[80];
		asctime_s(str_time, sizeof str_time, curtime);
		return str_time;
	}

	void execute_state() {
		string playername = this->machine_ref->Get_Gm()->Get_Winning_Player()->GetName();
		string playerscore = to_string(this->machine_ref->Get_Gm()->Get_Winning_Player()->GetChips());
		string time = current_time();		 

		//Display Winner
		OutputFile("gameover.txt");
		std::cout << "Winning player is: Player " << playername;
		OutputFile("gameover.txt");

		//Handle High Scores
		std::vector<Score> highscores = GetHighScores("scores.csv");	//Ensures scores.csv is created with header row if it doesn't exist
		Score newscore = Score(playername, playerscore, time);
		highscores.push_back(newscore);

		//Here would be were we sort and/or limit our high scores
		//TODO - High Score Logic
		//Temporarily just append new score to file
		append_to_file(newscore.GetFormattedRecord(), "scores.csv");

		Sleep(6000);
		system("cls");
	}
};
