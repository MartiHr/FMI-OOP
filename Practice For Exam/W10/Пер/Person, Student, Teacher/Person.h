#pragma once
#include <iostream>

class Person
{
	char* name = nullptr;
	int age = 0;

	void copyFrom(const Person& other);
	void free();
	void moveFrom(Person&& other) noexcept;

public:
	Person() = default;
	Person(const char* name, int age);
	~Person();

	Person(const Person& other);
	Person& operator=(const Person& other);

	Person(Person&& other);
	Person& operator=(Person&& other);

	const char* getName() const;
	int getAge() const;

	void print() const;

protected:
	void setName(const char* name);
	void setAge(int age);
};