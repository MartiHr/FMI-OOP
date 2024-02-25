#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Vector 
{
	int x;
	int y;
	int z;
};

Vector addUpVectors(Vector& first, Vector& second) 
{
	Vector resultVector;

	resultVector.x = first.x + second.x;
	resultVector.y = first.y + second.y;
	resultVector.z = first.z + second.z;
	
	return resultVector;
}

void printVectorCoordinates(const Vector& v) 
{
	cout << "x = " << v.x << " y = " << v.y << " z = " << v.z << endl;
}

bool compareDoubles(double a, double b) {
	return abs(a - b) < DBL_EPSILON;
}

bool linearlyDependent(const Vector& firstVector, const Vector& secondVector)
{
	double first = (double)firstVector.x / secondVector.x;
	double second = (double)firstVector.y / secondVector.y;
	double third = (double)firstVector.z / secondVector.z;
	
	return (compareDoubles(first, second) && compareDoubles(second, third));
}

int main()
{
	Vector a = {1, 2, 3};
	Vector b = {1, 2, 4};

	cout << linearlyDependent(a, b);
}