#pragma once

struct A
{
	int x = 3;
	int y = 2;
};

class DynamicArrayOfPointers
{
private:
	A** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const DynamicArrayOfPointers& other);
	void moveFrom(DynamicArrayOfPointers&& other) noexcept;
	void resize(size_t newCapacity);

	int getFirstFreeIndex() const;
public:
	DynamicArrayOfPointers();
	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers& operator=(const DynamicArrayOfPointers& other);
	~DynamicArrayOfPointers();

	DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept;
	DynamicArrayOfPointers operator=(DynamicArrayOfPointers&& other) noexcept;

	void addAtFirstFreeIndex(const A& current);
	void addAtFirstFreeIndex(A&& obj);

	bool containsAt(unsigned index) const;
	void popBack();
	void removeAt(size_t index);

	void setAtIndex(const A& obj, size_t index);
	void setAtIndex(A&& obj, size_t index);

	size_t getSize() const;
	const A& operator[](size_t index) const;
	A& operator[](size_t index);
};