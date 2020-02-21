#pragma once

#include <string>
#include <vector>
#include <map>


class Variant
{

public:
	enum eValueType
	{
		ValueTypeNone = 0,
		ValueTypeString = 1,
		ValueTypeInt = 2,
		ValueTypeDouble = 3,
		ValueTypeVector = 4,
		ValueTypeMap = 5
	};

public:
	Variant();
	~Variant();

	Variant(const std::string &value);
	Variant(int value);
	Variant(double value);
	Variant(const std::vector<Variant> &value);
	Variant(const std::map<std::string, Variant> &value);

	eValueType GetType() const;

	std::string ToString() const;
	int ToInt() const;
	double ToDouble() const;
	std::vector<Variant> ToArray() const;
	std::map<std::string, Variant> ToMap() const;
	


private:
	std::string m_StringValue;
	int m_IntValue;
	double m_DoubleValue;
	std::vector<Variant> m_VecktorValue;
	std::map<std::string, Variant> m_MapValue;
	eValueType m_TypeOfVariant;


};

