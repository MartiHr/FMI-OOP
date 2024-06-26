#pragma once
#include <iostream>

class MultiSet
{
	// TODO: add comparison function to order collection

	unsigned n = 0;
	unsigned k = 0;
	unsigned maxOccurrencesOfElement = 0;

	unsigned bucketsCount = 0;
	uint8_t* buckets = nullptr;

	void free();
	void copyFrom(const MultiSet& other);

	unsigned getNumberStartIndex(unsigned number) const;
	unsigned getBucketIndex(unsigned number) const;
	unsigned getInnerIndex(unsigned outerIndex) const;
	unsigned extractNumber(unsigned number) const;
	void setNumber(unsigned number, unsigned count);
	void printNumberVariableTimes(unsigned number, unsigned occurrences) const;
	void printBucketMemoryView(unsigned index) const;
public:
	MultiSet(unsigned n, unsigned k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void add(unsigned num);
	unsigned getNumberOccurrences(unsigned number) const;
	void printAllNumbers() const;
	void printMemoryView() const;
	void serialize(const char* fileName) const;
	void deserialize(const char* fileName);

	friend MultiSet intersect(MultiSet& first, MultiSet& second);
	friend MultiSet difference(MultiSet& first, MultiSet& second);
	MultiSet complement() const;
};

bool checkBitValue(unsigned number, unsigned index);
void toggleBit(unsigned& number, unsigned index);
void setBitZero(uint8_t& number, unsigned index);
void setBitToOne(uint8_t& number, unsigned index);
void setBitValue(uint8_t& number, unsigned index, bool value);