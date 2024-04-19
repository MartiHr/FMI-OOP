#pragma once
#include <iostream>
#include "GlobalConstants.h"

struct KeyValue
{
	int16_t key = 0;
	int16_t value = 0;

	bool isExcluded = false;
	//bool hasCustomValue = false;
	
};

class ModifiableIntegersFunction
{
	int16_t(*function)(int16_t number);
	
	KeyValue* valueByPoint = nullptr;

	void copyFrom(const ModifiableIntegersFunction& other);
	void free();

public:
	ModifiableIntegersFunction();
	ModifiableIntegersFunction(int16_t(*pred)(int16_t number));
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	~ModifiableIntegersFunction();

	void setCustomResult(int16_t input, int16_t result);
	void excludePoint(int16_t point);
	int16_t operator()(int16_t input) const;

	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction operator()(const ModifiableIntegersFunction& inner);

	friend bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
	friend bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
};

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);