#include "pch.h"
#include "variant.h"


Variant::Variant()
{
	m_IntValue = 0;
	m_DoubleValue = 0;
	m_TypeOfVariant = Variant::ValueTypeNone;
}


Variant::~Variant()
{
}


Variant::Variant(const std::string &value) 
{
	m_TypeOfVariant = ValueTypeString;
	m_StringValue = value;
}
Variant::Variant(int value) 
{
	m_TypeOfVariant = ValueTypeInt;
	m_IntValue = value;
}
Variant::Variant(double value)
{
	m_TypeOfVariant = ValueTypeDouble;
	m_DoubleValue = value;
}
Variant::Variant(const std::vector<Variant> &value)
{
	m_TypeOfVariant = ValueTypeVector;
	m_VecktorValue = value;
}
Variant::Variant(const std::map<std::string, Variant> &value)
{
	m_TypeOfVariant = ValueTypeMap;
	m_MapValue = value;
}


Variant::eValueType Variant::GetType() const
{
	return m_TypeOfVariant;
}

std::string Variant::ToString() const
{
	return m_StringValue;
}
int Variant::ToInt() const
{
	return m_IntValue;
}
double Variant::ToDouble() const
{
	return m_DoubleValue;
}
std::vector<Variant> Variant::ToArray() const
{
	return m_VecktorValue;
}
std::map<std::string, Variant> Variant::ToMap() const
{
	return m_MapValue;
}
