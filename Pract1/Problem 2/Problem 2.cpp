#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const unsigned STR_MAX_LEN = 128;
const char bachelorStr[] = "Bachelor";
const char masterStr[] = "Master";
const char doctorStr[] = "Doctor";
const char unknownStr[] = "Unknown";

// If you need type safety 
// (prevents unintended operations or conversions between different types) 
// and want to avoid potential naming collisions, prefer enum class.
enum class Degree
{
	Bachelor,
	Master,
	Doctor,
	Unknown
};

struct Teacher
{
	int id;
	// The number of students he failed
	unsigned long souls;
	Degree degree;
};

int getNumLength(int num)
{
	int length = 0;

	while (num != 0)
	{
		num /= 10;
		length++;
	}

	return length;
}

Teacher initializeTeacher(short id, unsigned long souls, char* degree)
{
	Teacher teacher;

	if (!degree)
	{
		teacher.degree = Degree::Unknown;
	}

	if (getNumLength(id) != 5)
	{
		return;
	}

	teacher.souls = souls;

	if (strcmp(degree, bachelorStr) == 0)
	{
		teacher.degree = Degree::Bachelor;
	}
	else if (strcmp(degree, masterStr) == 0)
	{
		teacher.degree = Degree::Master;
	}
	else if (strcmp(degree, doctorStr) == 0)
	{
		teacher.degree = Degree::Doctor;
	}
	else
	{
		teacher.degree = Degree::Unknown;
	}
}

void printTeacherData(Teacher& teacher)
{
	cout << "Id: " << teacher.id << endl;

	cout << "Collected souls: " << teacher.souls << endl;

	cout << "Degree: ";

	switch (teacher.degree)
	{
	case Degree::Bachelor:
		cout << bachelorStr << endl;
		break;
	case Degree::Master:
		cout << masterStr << endl;
		break;
	case Degree::Doctor:
		cout << doctorStr << endl;
		break;
	default:
		cout << unknownStr << endl;
		break;
	}
}

int main()
{
	int id;
	cin >> id;

	unsigned long souls;
	cin >> souls;

	char degree[STR_MAX_LEN];
	cin.getline(degree, STR_MAX_LEN);

	Teacher teacher = initializeTeacher(id, souls, degree);
}