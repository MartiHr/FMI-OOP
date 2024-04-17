#include "MultiSet.h"
#include <bitset>

void MultiSet::free()
{
	n = 0;
	k = 0;
	delete[] buckets;
	bucketsCount = 0;
	maxBitsForElement = 0;
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
	maxBitsForElement = other.maxBitsForElement;
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

unsigned MultiSet::getNumberOccurences(unsigned number) const
{
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
	unsigned startIndex = getNumberStartIndex(number);
	unsigned currentInnerIndex = getInnerIndex(startIndex);
	unsigned currentBucketIndex = getBucketIndex(startIndex);

	unsigned extract = 0;
	unsigned extractIndex = 0;

	for (int i = 0; i < k; i++)
	{
		if (checkBitValue(buckets[currentBucketIndex], 7 - currentInnerIndex))
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

	for (int i = 0; i < n; i++)
	{
		unsigned numOccurences = getNumberOccurences(i);
		printNumberVariableTimes(i, numOccurences);
	}

	std::cout << '}';
}

void MultiSet::printMemoryView() const
{
	for (int i = 0; i < bucketsCount; i++)
	{
		printBucketMemoryView(i);
		std::cout << ' ';
	}

	printBucketMemoryView(bucketsCount - 1);
}

void MultiSet::printNumberVariableTimes(unsigned number, unsigned occurences) const
{
	for (int i = 0; i < occurences; i++)
	{
		std::cout << ' ' << number << ' ';
	}
}

void MultiSet::printBucketMemoryView(unsigned index) const
{
	for (size_t i = 0; i < 8; i++)
	{
		std::cout << checkBitValue(index, 0);
	}
}

MultiSet::MultiSet(unsigned n, unsigned k)
{
	this->n = n;
	this->k = k;
	// elements in bucket should be changed
	// TODO: make sure bits for element is correct
	maxBitsForElement = (1 << k) - 1;

	unsigned neededBitsToStore = n * k;
	bucketsCount = neededBitsToStore / 8;

	if (neededBitsToStore % 8 != 0 || neededBitsToStore == 0)
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
	unsigned count = getNumberOccurences(num);

	// TODO: check if count of number is at max
	unsigned upperBound = ((1 << k) - 1);
	if (getNumberOccurences(num) >= upperBound)
	{
		throw "Throw a nice error";
	}

	setNumber(num, count + 1);

	// Calculate the bit mask to set the appropriate bit in the bucket
	//unsigned char mask = getMask(num);

	// Set the bit in the corresponding bucket
	//buckets[bucketIndex] |= mask;
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

void setBitZero(uint8_t& number, unsigned index) {
	uint8_t mask = 1;
	mask <<= index;
	mask = ~mask; 
	number =  number & mask;
}

void setBitToOne(uint8_t& number, unsigned index) {
	uint8_t  mask = 1;
	mask <<= index; 
	number =  number | mask;
}

void setBitValue(uint8_t& number, unsigned index, bool value) {
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

