#pragma once

#include <string>

class Player
{
private:
	std::string m_name;
	int m_chips;

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

	void SetChips(const int& score)
	{
		m_chips = score;
	}

	const int& GetChips() const
	{
		return m_chips;
	}

	void AddChips(const int& score) {
		m_chips += score;
	}

	void RemoveChips(const int& score) {
		m_chips -= score;
	}
};