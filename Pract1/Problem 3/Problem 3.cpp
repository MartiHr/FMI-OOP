#include <iostream>

struct Teacher 
{
	char name[100];
	int dropout_students;
};

struct University 
{
	Teacher* teachers;
	int num_teachers;
	float avg_dropout_rate;
};

// Function to create a university
University createUniversity() 
{
	University uni;
	std::cout << "Enter the number of teachers: ";
	std::cin >> uni.num_teachers;

	uni.teachers = new Teacher[uni.num_teachers];
	int total_dropout = 0;

	for (int i = 0; i < uni.num_teachers; ++i) 
	{
		std::cout << "Name of teacher " << i + 1 << ": ";
		std::cin >> uni.teachers[i].name;
		std::cout << "Number of dropout students: ";
		std::cin >> uni.teachers[i].dropout_students;
		total_dropout += uni.teachers[i].dropout_students;
	}

	uni.avg_dropout_rate = (total_dropout) / (uni.num_teachers * 1.0);

	return uni;
}

// Function to find the number of teachers eligible for bonus
int teachersWithBonus(const University& uni, int min_dropout) 
{
	int count = 0;
	for (int i = 0; i < uni.num_teachers; ++i) 
	{
		if (uni.teachers[i].dropout_students >= min_dropout) 
		{
			count++;
		}
	}
	return count;
}

// Helper function to compare teachers based on the number of dropout students
bool compareByDropout(const Teacher& a, const Teacher& b) 
{
	return a.dropout_students < b.dropout_students;
}

// Function to sort teachers in ascending order of dropout students
void sortTeachersByDropout(University& uni) 
{
	for (int i = 0; i < uni.num_teachers - 1; ++i) 
	{
		for (int j = 0; j < uni.num_teachers - i - 1; ++j) 
		{
			if (uni.teachers[j].dropout_students > uni.teachers[j + 1].dropout_students) 
			{
				Teacher temp = uni.teachers[j];
				uni.teachers[j] = uni.teachers[j + 1];
				uni.teachers[j + 1] = temp;
			}
		}
	}
}

int main() 
{
	University university = createUniversity();

	std::cout << "Average number of dropout students: "
		<< university.avg_dropout_rate << std::endl;

	int min_dropout;
	std::cout << "Minimum number of dropout students for bonus: ";
	std::cin >> min_dropout;

	int teachers_with_bonus = teachersWithBonus(university, min_dropout);
	std::cout << "Teachers eligible for bonus: " << teachers_with_bonus << std::endl;

	sortTeachersByDropout(university);
	std::cout << "Teachers sorted by number of dropout students in ascending order:" << std::endl;
	for (int i = 0; i < university.num_teachers; ++i) 
	{
		std::cout << university.teachers[i].name << ": " << university.teachers[i].dropout_students << std::endl;
	}

	delete[] university.teachers; // Freeing dynamically allocated memory

	return 0;
}
