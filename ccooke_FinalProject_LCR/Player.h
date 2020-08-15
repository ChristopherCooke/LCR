#pragma once

#include <string>

class Player
{
private:
	std::string m_name;
	int m_chips;
	Player* next_player = nullptr;
	Player* previous_player = nullptr;

public:
	Player()
	{
	}

	void SetName(const std::string& name)
	{
		m_name = name;
	}

	const std::string& GetName() const
	{
		return m_name;
	}

	void SetChips(int score)
	{
		m_chips = score;
	}

	int GetChips() 
	{
		return m_chips;
	}

	void AddChips(int score) {
		m_chips += score;
	}

	void RemoveChips(int score) {
		m_chips -= score;
	}

	Player* GetNextPlayer() {
		return next_player;
	}

	void SetNextPlayer(Player* player) {
		next_player = player;
	}

	Player* GetPreviousPlayer() {
		return previous_player;
	}

	void SetPreviousPlayer(Player* player) {
		previous_player = player;
	}
};