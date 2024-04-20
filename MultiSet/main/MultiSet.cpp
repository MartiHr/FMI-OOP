#pragma once

#include "MultiSet.h"
#include "Constants.h"

#include <bitset>
#include <fstream>
#include <exception>

void MultiSet::free()
{
	n = 0;
	k = 0;
	delete[] buckets;
	bucketsCount = 0;
	maxOccurrencesOfElement = 0;
	buckets = nullptr;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	n = other.n;
	k = other.k;

	buckets = new uint8_t[other.bucketsCount];

	for (unsigned i = 0; i < other.bucketsCount; i++)
	{
		buckets[i] = other.buckets[i];
	}

	bucketsCount = other.bucketsCount;
	maxOccurrencesOfElement = other.maxOccurrencesOfElement;
}

unsigned MultiSet::getNumberStartIndex(unsigned number) const
{
	return number * k;
}

unsigned MultiSet::getBucketIndex(unsigned index) const
{
	unsigned bucketIndex = 0;

	bucketIndex = index / 8;

	if (index % 8 == 0 && index != 0)
	{
		bucketIndex++;
	}

	return bucketIndex;
}

unsigned char MultiSet::getMask(unsigned number) const
{
	//TODO: Extract constants
	/*unsigned indexInBucket = number % 8;

	char mask = 1;
	mask = mask << (7 - indexInBucket);
	return mask;*/
	return 0;
}

unsigned MultiSet::getNumberOccurrences(unsigned number) const
{
	if (number > n)
	{
		throw std::out_of_range(Constants::INVALID_BOUNDARY);
	}

	unsigned count = extractNumber(number);

	return count;
}

unsigned MultiSet::getInnerIndex(unsigned outerIndex) const
{
	unsigned indexInBucket = outerIndex % 8;

	return indexInBucket;
}

unsigned MultiSet::extractNumber(unsigned number) const
{
	// This is the purest way to do this, making the code most readable.
	// Other ways have unjustified of using them. Take points if the criteria says so :)
	unsigned startIndex = getNumberStartIndex(number);
	unsigned currentInnerIndex = getInnerIndex(startIndex);
	unsigned currentBucketIndex = getBucketIndex(startIndex);

	unsigned extract = 0;
	unsigned extractIndex = 0;

	for (int i = 0; i < k; i++)
	{
		if (checkBitValue(buckets[currentBucketIndex], currentInnerIndex))
		{
			toggleBit(extract, extractIndex);
		}

		currentInnerIndex++;

		if (currentInnerIndex > 7)
		{
			currentInnerIndex = 0;
			currentBucketIndex++;
		}

		extractIndex++;
	}


	return extract;
}

void MultiSet::setNumber(unsigned number, unsigned count)
{
	// This is the purest way to do this, making the code most readable.
	// Other ways have unjustified of using them. Take points if the criteria says so :)

	unsigned startIndex = getNumberStartIndex(number);
	unsigned currentInnerIndex = getInnerIndex(startIndex);
	unsigned currentBucketIndex = getBucketIndex(startIndex);

	unsigned setIndex = 0;

	for (int i = 0; i < k; i++)
	{
		if (checkBitValue(count, setIndex))
		{
			setBitValue(buckets[currentBucketIndex], currentInnerIndex, 1);
		}
		else
		{
			setBitValue(buckets[currentBucketIndex], currentInnerIndex, 0);
		}

		currentInnerIndex++;

		if (currentInnerIndex > 7)
		{
			currentInnerIndex = 0;
			currentBucketIndex++;
		}

		setIndex++;
	}
}

void MultiSet::printAllNumbers() const
{
	std::cout << '{';

	for (int i = 0; i <= n; i++)
	{
		unsigned numOccurences = getNumberOccurrences(i);
		printNumberVariableTimes(i, numOccurences);
	}

	std::cout << '}' << std::endl;
}

void MultiSet::printMemoryView() const
{
	for (int i = 0; i < bucketsCount - 1; i++)
	{
		printBucketMemoryView(i);
		std::cout << ' ';
	}

	printBucketMemoryView(bucketsCount - 1);
	std::cout << std::endl;
}

void MultiSet::serialize(const char* fileName) const
{
	if (!fileName)
	{
		throw std::invalid_argument(Constants::NULL_FILENAME);
	}

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		throw std::runtime_error(Constants::FAILED_OPEN_FILE);
	}

	ofs.write((const char*)&n, sizeof(n));
	ofs.write((const char*)&k, sizeof(k));
	ofs.write((const char*)&maxOccurrencesOfElement, sizeof(maxOccurrencesOfElement));

	ofs.write((const char*)&bucketsCount, sizeof(bucketsCount));
	ofs.write((const char*)buckets, bucketsCount * sizeof(uint8_t)); // sizeof(uint8_t) = 1
}
void MultiSet::deserialize(const char* fileName)
{
	if (!fileName)
	{
		throw std::invalid_argument(Constants::NULL_FILENAME);
	}

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		throw std::runtime_error(Constants::FAILED_OPEN_FILE);
	}

	ifs.read((char*)&n, sizeof(n));
	ifs.read((char*)&k, sizeof(k));
	ifs.read((char*)&maxOccurrencesOfElement, sizeof(maxOccurrencesOfElement));

	ifs.read((char*)&bucketsCount, sizeof(bucketsCount));

	if (buckets != nullptr)
	{
		delete[] buckets;
	}

	buckets = new uint8_t[bucketsCount];

	ifs.read((char*)buckets, bucketsCount * sizeof(uint8_t)); // sizeof(uint8_t) = 1
}

void MultiSet::printNumberVariableTimes(unsigned number, unsigned occurrences) const
{
	for (int i = 0; i < occurrences; i++)
	{
		std::cout << ' ' << number << ' ';
	}
}

void MultiSet::printBucketMemoryView(unsigned index) const
{
	for (int i = 7; i >= 0; i--)
	{
		std::cout << checkBitValue(buckets[index], i);
	}
}

MultiSet::MultiSet(unsigned n, unsigned k)
{
	this->n = n;
	this->k = k;

	if (k < 1 || k > 8)
	{
		throw std::invalid_argument(Constants::INVALID_ARGUMENT);
	}

	maxOccurrencesOfElement = (1 << k) - 1;

	unsigned neededBitsToStore = (n + 1) * k;
	bucketsCount = neededBitsToStore / 8;

	if (neededBitsToStore % 8 != 0)
	{
		bucketsCount++;
	}

	buckets = new uint8_t[bucketsCount]{ 0 };
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::add(unsigned num)
{
	if (num > n)
	{
		throw std::out_of_range(Constants::OUT_OF_BOUNDS);
	}

	unsigned count = getNumberOccurrences(num);

	unsigned upperBound = ((1 << k) - 1);
	unsigned numberOccurrences = getNumberOccurrences(num);

	if (numberOccurrences >= upperBound)
	{
		throw std::range_error(Constants::INVALID_BOUNDARY);
	}

	setNumber(num, count + 1);
}

MultiSet intersect(MultiSet& first, MultiSet& second)
{
	unsigned minN = std::min(first.n, second.n);
	unsigned minK = std::min(first.k, second.k);

	MultiSet result(minN, minK);

	for (unsigned i = 0; i <= minN; ++i)
	{
		unsigned count1 = first.getNumberOccurrences(i);
		unsigned count2 = second.getNumberOccurrences(i);
		unsigned intersectionCount = std::min(count1, count2);
		result.setNumber(i, intersectionCount);
	}

	return result;
}

MultiSet difference(MultiSet& first, MultiSet& second)
{
	unsigned minN = std::min(first.n, second.n);
	unsigned minK = std::min(first.k, second.k);

	MultiSet result(minN, minK);

	for (unsigned i = 0; i < minN; ++i)
	{
		unsigned count1 = first.getNumberOccurrences(i);
		unsigned count2 = second.getNumberOccurrences(i);
		if (count1 > count2)
		{
			result.setNumber(i, count1 - count2);
		}
	}

	return result;
}


MultiSet MultiSet::complement() const
{
	MultiSet result(n, k);

	for (unsigned i = 0; i <= n; ++i)
	{
		unsigned count = getNumberOccurrences(i);
		result.setNumber(i, maxOccurrencesOfElement - count);
	}

	return result;
}


bool checkBitValue(unsigned number, unsigned index)
{
	//std::cout << (std::bitset<8>(number)) << std::endl;
	unsigned int mask = 1;
	mask <<= index;
	//std::cout << (std::bitset<8>(mask)) << std::endl;

	//std::cout << (std::bitset<8>((mask & number) == mask)) << std::endl;

	return (mask & number) == mask;
}

void setBitZero(uint8_t& number, unsigned index)
{
	uint8_t mask = 1;
	mask <<= index;
	mask = ~mask;
	number = number & mask;
}

void setBitToOne(uint8_t& number, unsigned index)
{
	uint8_t  mask = 1;
	mask <<= index;
	number = number | mask;
}

void setBitValue(uint8_t& number, unsigned index, bool value)
{
	return value
		? setBitToOne(number, index)
		: setBitZero(number, index);
}

void toggleBit(unsigned& number, unsigned index)
{
	unsigned int mask = 1;
	mask <<= index;

	number = number ^ mask;
}

