#pragma once

class StringPool
{
private:
	struct StringRecord
	{
		char* str = nullptr;
		unsigned refCount = 0;
	};

	StringRecord* records = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	int findString(const char* soghtString) const;
	int allocateString(const char* str);
	void deleteRecord(int index);

	void resize();
public:

	StringPool();
	StringPool(const StringPool& other) = delete;
	StringPool& operator=(const StringPool& other) = delete;
	~StringPool();

	const char* getString(const char* str);
	void removeOneString(const char* str);

	void print() const;
};