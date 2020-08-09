#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Score {
private:
	string name;
	int score;
	string date;

public:
	Score(string record)
	{
		std::vector<std::string> values = explode(record, ',');	//I work in PHP alot these days...
		int valuesize = values.size();
		if (valuesize < 3) {
			throw exception("Improperly formatted record received.");
		} 
		name = values[0];
		score = stoi(values[1]);
		date = values[2];
	}
	Score(string _name, string _score, string _date) {
		name = _name;
		score = stoi(_score);
		date = _date;
	}
	string GetName() {
		return name;
	}
	int GetScore() {
		return score;
	}
	string GetDate() {
		return date;
	}
	std::vector<std::string> explode(std::string const & s, char delim)
	{
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); )
		{
			result.push_back(std::move(token));
		}

		return result;
	}
	string GetFormattedRecord() {
		return name + "," + std::to_string(score) + "," + date + "\n";
	}
};