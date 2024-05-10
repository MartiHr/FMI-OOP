#pragma once

class NVector
{
private:
	int* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();
public:

	NVector(size_t size);

	NVector(const NVector& other);
	NVector& operator=(const NVector& other);
	~NVector();


};