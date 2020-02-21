#include "pch.h"
#include "jsonparser.h"


#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



JsonParser::JsonParser()
{
}


JsonParser::~JsonParser()
{
}


void JsonParser::SkipSpaces(std::string &cJsonString, int &nindex)
{	
	int nCounter = nindex + 1;//так потоому что всегда прибовляет если просто индекс++

	while (true)
	{
		if (nindex >= cJsonString.size())
			break;
		char cSymbol = cJsonString[nCounter];
		if (cSymbol == ' ' || cSymbol == '\t' || cSymbol == '\r' || cSymbol == '\n')
		{
			++nindex;
			++nCounter;
		}
		else
			break;
	}
}

Variant JsonParser::ParseString(std::string &cJsonString, int &nindex)
{
	std::string cParsingString = "";
	nindex++;

	while (true)
	{
		if (nindex >= cJsonString.size())
			break;

		char cSymbol = cJsonString[nindex];

		if (cSymbol == '"')
			break;

		++nindex;
		cParsingString += cSymbol;
	}
	Variant pVariantValue(cParsingString);
	//std::cout << "\"" << ParsingString << "\"\n";
	return pVariantValue;
}

Variant JsonParser::ParseNumber(std::string &cJsonString, int &nindex)
{

	std::string cParsingNumber = "";

	bool bIsDouble = false;

	while (true)
	{
		if (nindex >= cJsonString.size())
			break;

		char cSymbol = cJsonString[nindex];

		if (isdigit(cSymbol) || cSymbol == '.')
		{
			if (cSymbol == '.' && bIsDouble == false)
			{
				++nindex;
				cParsingNumber += cSymbol;
				bIsDouble = true;
			}
			else
			{
				++nindex;
				cParsingNumber += cSymbol;
			}
		}
		else
			break;		
	}
	nindex--;//что бы при следующем nextToken доходило до нашей запятой на которой остановились, тк мы прибовляем в начале он её перепрыгивает

	if (bIsDouble == true)
	{
		Variant Value(std::stod(cParsingNumber));
		return Value;
	}
	else
	{
		Variant Value(std::stoi(cParsingNumber));
		return Value;
	}
	//return K;
	//Variant test2(std::stoi(ParsingNumber));
	//Variant *test = new Variant(std::stoi(ParsingNumber));	
}

std::vector<Variant> JsonParser::ParseArray(std::string &cJsonString, int &nindex)
{
	std::vector<Variant> vpValue;

	while (true)
	{
		if (nindex >= cJsonString.size())
			break;

		SkipSpaces(cJsonString, nindex);
		NextToken(cJsonString, nindex);
		//char symbol = JsonString[index];
		if (cJsonString[nindex] == ']')
		{
			break;
		}

		if (cJsonString[nindex] == ',')
		{
			//std::cout << ",";
			continue;
		}
		nindex--;
		vpValue.push_back(ParseValue(cJsonString, nindex));
	}
	//просто вызываем ParseValue, проверки на запятые, тип след элемент и конец массива ]

	return vpValue;
}

eJsonToken JsonParser::NextToken(std::string &cJsonString, int &nindex)
{
	nindex++;

	if (nindex >= cJsonString.size())
	{
		return JsonTokenNone;
	}

	switch (cJsonString[nindex])
	{
	case '{':
		return JsonTokenCurlyOpen;
		break;
	case '}':
		return JsonTokenCurlyClose;
		break;
	case ':':
		return JsonTokenColon;
		break;
	case ',':
		return JsonTokenComma;
		break;
	case '"':
		return JsonTokenString;
		break;
	case '[':
		return JsonTokenSquaredOpen;
		break;
	case ']':
		return JsonTokenSquaredClose;
		break;		
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return JsonTokenNumber;
		break;
	}
	return JsonTokenNone;
}

Variant JsonParser::ParseValue(std::string &cJsonString, int &nindex)
{	
		SkipSpaces(cJsonString, nindex);
		eJsonToken peToken = NextToken(cJsonString, nindex);
		
		//char c;
		switch (peToken)
		{
		case JsonTokenCurlyOpen:
		{
			
			Variant pValueObject = ParseObject(cJsonString, nindex);
			return pValueObject;
		}
			break;
		case JsonTokenSquaredOpen:
		{
			//std::cout << "[";
			Variant pValueArray = ParseArray(cJsonString, nindex);
			//std::cout << "]";
			return pValueArray;
		}
			break;
		case JsonTokenNumber:
		{
			Variant pValueNumber = ParseNumber(cJsonString, nindex);
			//c = JsonString[index];
			/*if (valueNumber.GetType() == Variant::ValueTypeDouble)
				std::cout << " : " << valueNumber.ToDouble();
			else
				std::cout << " : " << valueNumber.ToInt();*/
			return pValueNumber;
		}			
			break;
		case JsonTokenString:
		{
			//тут тоже вариант только для строки
			Variant pValueString = ParseString(cJsonString, nindex);
			//std::cout << " : " << valuestring.ToString();
			return pValueString;
		}			
			break;		
		}	
}

Variant JsonParser::ParseObject(std::string &cJsonString, int &nindex)
{
	//std::cout << "{\n";
	std::string cKey = "";

	
	std::map<std::string, Variant> mpValueObject;

	while (true)
	{
		SkipSpaces(cJsonString, nindex);
		eJsonToken peToken = NextToken(cJsonString, nindex);
		if(peToken == JsonTokenNone)
		{
			return false;
		}
		else if (peToken == JsonTokenComma)
		{
			char cSymbol = cJsonString[nindex];

			SkipSpaces(cJsonString, nindex);
			//std::cout << ",\n";
			
			cSymbol = cJsonString[nindex];
		}
		else if(peToken == JsonTokenCurlyClose)
		{
			//std::cout << "\n}\n";
			break;
		}
		else
		{
			cKey = ParseString(cJsonString, nindex).ToString();
			//char symbol = JsonString[index];
			peToken = NextToken(cJsonString, nindex);
			//symbol = JsonString[index];
			if(peToken != JsonTokenColon)
				return false;

			//std::cout << "\"" << Key << "\" ";

			Variant pValue = ParseValue(cJsonString, nindex);
			mpValueObject.insert(std::pair<std::string, Variant>(cKey, pValue));
			
			//map[Key] = value;
		}
	}
	//m_JsonMap.insert
	Variant pObject = mpValueObject;
	return pObject;
}

Variant JsonParser::OpenJson(std::string filepath)
{
	std::ifstream fJsonFile(filepath);
	if (!fJsonFile.is_open())
		return false;

	
	std::string cJsonString;

	while (!fJsonFile.eof())
	{
		std::string BufStr;
		std::getline(fJsonFile, BufStr);
		cJsonString += BufStr;
	}
	fJsonFile.close();

	int nIndex = -1;
	while (true)
	{
		eJsonToken Token = NextToken(cJsonString, nIndex);

		switch (Token)
		{
		case JsonTokenCurlyOpen:
			//std::cout << '{';
			m_JsonMap = ParseObject(cJsonString, nIndex).ToMap();
			return m_JsonMap;
			break;
		case JsonTokenCurlyClose:
			//std::cout << '}';
			break;
		case JsonTokenColon:
			//std::cout << ':';
			break;
		case JsonTokenComma:
			//std::cout << ',';
			break;
		case JsonTokenString:
			//std::cout << '"';
			break;
		case JsonTokenSquaredOpen:
			//std::cout << '[';
			break;
		case JsonTokenSquaredClose:
			//std::cout << ']';
			break;
		case JsonTokenNone:
			return false;
		}
	}

	return true;
}

//void coutObject(const std::map<std::string, Variant> &mpJsonMap)//Путь к сериализации
//{
//
//	for (auto it = mpJsonMap.begin(); it != mpJsonMap.end(); ++it)
//	{
//		std::cout << it->first;
//
//		Variant::eValueType pTypeOfValue = it->second.GetType();
//
//		switch (pTypeOfValue)
//		{
//		case Variant::ValueTypeString:
//		{
//			std::cout << " : " << it->second.ToString() << std::endl;
//		}
//			break;
//		case Variant::ValueTypeInt:
//		{
//			std::cout << " : " << it->second.ToInt() << std::endl;
//		}
//			break;
//		case Variant::ValueTypeDouble:
//		{
//			std::cout << " : " << it->second.ToDouble() << std::endl;
//		}
//			break;
//		case  Variant::ValueTypeMap:
//		{
//			coutObject(it->second.ToMap());
//		}
//			break;
//		case Variant::ValueTypeVector:
//		{
//
//		}
//			break;
//		default:
//			break;
//		}
//	}
//}

std::string JsonParser::Answer(CmdCommand::eCmdCommand peCommandType,const std::string &cValue)
{
	std::string cAnswer = "";

	switch (peCommandType)
	{
	case CmdCommand::CmdCommandNone:
	{
		cAnswer = "Wrong Command!";
	}
		break;
	case CmdCommand::CmdCommandGetName:
	{
		for (auto it = m_JsonMap.begin(); it != m_JsonMap.end(); ++it)
		{
			//it->second.ToMap()::iterator = it->second.ToMap().find("Name")

			//std::string  a = it->second.ToMap().at("Name").ToString();
			std::map<std::string, Variant> mvBuf = it->second.ToMap();

			if (mvBuf.at("name").ToString() == cValue)
			{
				cAnswer += it->first + ": \n";
				
				for (auto jt = mvBuf.begin(); jt != mvBuf.end(); ++jt)
				{
					cAnswer += jt->first + ": ";

					Variant::eValueType peType = jt->second.GetType();

					switch (peType)
					{
					case Variant::ValueTypeNone:
						break;
					case Variant::ValueTypeString:
					{
						cAnswer += jt->second.ToString() + "\n";
					}
						break;
					case Variant::ValueTypeInt:
					{
						cAnswer += std::to_string(jt->second.ToInt()) + "\n";
					}
						break;
					case Variant::ValueTypeDouble:
					{
						cAnswer += std::to_string(jt->second.ToDouble()) + "\n";
					}
						break;
					case Variant::ValueTypeVector:
					{

					}
						break;
					case Variant::ValueTypeMap:
						break;
					}
				}
			}			
		}

		return cAnswer;
	}
		break;
	case CmdCommand::CmdCommandGetAll:
	{
		for (auto it = m_JsonMap.begin(); it != m_JsonMap.end(); ++it)
		{
			cAnswer += it->first + ":\n";
			std::map<std::string, Variant> mvBuf = it->second.ToMap();
			for (auto jt = mvBuf.begin(); jt != mvBuf.end(); ++jt)
			{
				cAnswer += jt->first + ": ";

				Variant::eValueType peType = jt->second.GetType();

				switch (peType)
				{
				case Variant::ValueTypeNone:
					break;
				case Variant::ValueTypeString:
				{
					cAnswer += jt->second.ToString() + "\n";
				}
				break;
				case Variant::ValueTypeInt:
				{
					cAnswer += std::to_string(jt->second.ToInt()) + "\n";
				}
				break;
				case Variant::ValueTypeDouble:
				{
					cAnswer += std::to_string(jt->second.ToDouble()) + "\n";
				}
				break;
				case Variant::ValueTypeVector:
				{

				}
				break;
				case Variant::ValueTypeMap:
					break;
				}
			}
		}
	}
		break;
	}

	//дописать вывод по командам через кейсы


	return cAnswer;
}







