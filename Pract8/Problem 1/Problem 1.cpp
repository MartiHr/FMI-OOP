#include <iostream>
#include <fstream>

namespace GlobalConstants
{
	constexpr unsigned BUFFER_SIZE = 1024;
}

class Student
{
	char* name = nullptr;
	int facultyNumber = 0;
	int group = 0;
	double averageGrade = 0;

	void copyFrom(Student& other);
	void free();
public:
	Student() = default;
	Student(Student& student);
	Student& operator=(Student& otherStudent);
	~Student();

	const char* getName() const;
	int getFacultyNumber() const;
	int getGroup() const;
	double getAverageGrade() const;

	void setName(const char* name);
	void setFacultyNumber(int number);
	void setGroup(int number);
	void setAverageGrade(double averageGrade);

	friend std::ostream& operator<<(std::ostream& os, const Student& data);
	friend std::istream& operator>>(std::istream& is, Student& data);
};

void Student::copyFrom(Student& other)
{
	strcpy(this->name, other.name);

}

void Student::free()
{
	delete[] name;
	facultyNumber = 0;
	group = 0;
	averageGrade = 0.0;
}

Student::Student(Student& otherStudent)
{
	copyFrom(otherStudent);
}

Student& Student::operator=(Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Student::~Student()
{
	free();
}

const char* Student::getName() const
{
	return this->name;
}

int Student::getFacultyNumber() const
{
	return this->facultyNumber;
}

int Student::getGroup() const
{
	return this->group;
}

double Student::getAverageGrade() const
{
	return this->averageGrade;
}

std::ostream& operator<<(std::ostream& os, const Student& data)
{
	return os << "Name: " << data.name << ", faculty number: " << data.facultyNumber
		<< ", group number: " << data.group << ", average grade: " << data.averageGrade;
}

std::istream& operator>>(std::istream& is, Student& data)
{
	return is;
}

int main()
{
	Student s;
	std::cout << s;
}
