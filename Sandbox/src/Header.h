#pragma once
#include "gbpch.h"
enum class EAnswer
{
	Ignore	 = 0,
	Insecure = 1,
	Logical  = 2,
	Pasional = 3
};

class Action
{
public:
	Action(const std::string& name = "Action") : m_actionName(name){}
	void virtual OnEvent() = 0;

private:
	const std::string m_actionName;
};


class Decision
{
public:

	void MakeDecision(const EAnswer answer);

private:
	EAnswer m_LastAnswer;
	std::vector<Action*> m_Actions;
};