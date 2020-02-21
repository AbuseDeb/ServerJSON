#pragma once

#include <string>
#include <list>
#include <map> 
#include <vector>
#include "variant.h"
#include "cmdcommand.h"

enum eJsonToken {
	JsonTokenNone = 0,
	JsonTokenCurlyOpen = 1,
	JsonTokenCurlyClose = 2,
	JsonTokenSquaredOpen = 3,
	JsonTokenSquaredClose = 4,
	JsonTokenColon = 5,
	JsonTokenComma = 6,
	JsonTokenString = 7,
	JsonTokenNumber = 8,
	JsonTokenTrue = 9,
	JsonTokenFalse = 10,
	JsonTokenNull = 11
};


class JsonParser
{
public:
	JsonParser();
	~JsonParser();
	
	eJsonToken NextToken(std::string &JsonString, int &index);
	void SkipSpaces(std::string &JsonString, int &index);
	Variant ParseString(std::string &JsonString, int &index);
	Variant ParseNumber(std::string &JsonString, int &index);
	std::vector<Variant> ParseArray(std::string &JsonString, int &index);
	Variant ParseValue(std::string &JsonString, int &index);
	Variant ParseObject(std::string &JsonString, int &index);
	Variant OpenJson(std::string filepath);
	std::string Answer(CmdCommand::eCmdCommand peCommandType,const std::string &cValue);

public:
	std::map<std::string, Variant> m_JsonMap;

};

