#include "pch.h"
#include "cmdcommand.h"
#include <iostream>


CmdCommand::CmdCommand()
:m_cValue("") //- список инициализации, лучше делать так
//:m_Command(CmdCommand::CmdCommandNone)
{
	//m_cValue = "";
	m_Command = CmdCommandNone;

	m_mvCommands = {
		{CmdCommandGetName, std::vector<std::string> {"get","--name","value"}},
		{CmdCommandGetAll,  std::vector<std::string> {"get","--all"}}
	};
}


CmdCommand::~CmdCommand()
{
}






bool CmdCommand::GetCommand(std::string &cCommand)
{
	std::vector<std::string> vcCommand;

	std::string cBuff = "";
	for (int i = 0; i < cCommand.size(); ++i)
	{
		if (cCommand[i] == ' ')
		{
			for (int j = i; j < cCommand.size(); ++j)
			{
				if (cCommand[j + 1] != ' ')
				{
					i = j;
					break;
				}
			}
			if(cBuff != "")
				vcCommand.push_back(cBuff);
			cBuff = "";
			continue;
		}
		cBuff += cCommand[i];
	}
	vcCommand.push_back(cBuff);

	for (auto it = m_mvCommands.begin(); it != m_mvCommands.end(); ++it)
	{
		if (it->second.size() == vcCommand.size())
		{
			bool bIsRightCommand = true;
			int nSizeVector = 0;

			if (it->second.at(it->second.size() - 1) == "value")
			{
				nSizeVector = it->second.size() - 1;
			}
			else
			{
				nSizeVector = it->second.size();
			}


			for (int i = 0; i < nSizeVector; ++i)
			{
				if (it->second.at(i) != vcCommand.at(i))
				{
					bIsRightCommand = false;
					break;
				}
			}

			if (bIsRightCommand == true)
			{
				m_cValue = vcCommand.at(vcCommand.size() - 1);
				m_Command = it->first;
			}
		}

		else
			std::cout << it->second.size() << " != " << vcCommand.size() << std::endl;
	}

	if (m_Command != CmdCommandNone)
		return true;

	return false;
}
