#pragma once

#include <string>
#include <map>
#include <vector>


class CmdCommand
{
public:
	enum eCmdCommand
	{
		CmdCommandNone,
		CmdCommandGetName,
		CmdCommandGetAll
	};

public:
	CmdCommand();
	~CmdCommand();

	bool GetCommand(std::string &cCommand);
	std::string m_cValue;
	eCmdCommand m_Command;
private:
	

	std::map<eCmdCommand, std::vector<std::string>> m_mvCommands;
};

