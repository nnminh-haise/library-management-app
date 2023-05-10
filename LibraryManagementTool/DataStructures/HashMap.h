#pragma once

#include <string>
#include <format>
#include <iostream>

template < typename HASH_VALUE >
class HashMap {
public:
	HashMap();

	HashMap(int maxValue, HASH_VALUE defaultValue);

	void Insert(const std::string& key, HASH_VALUE value);

	HASH_VALUE At(const std::string& key);

	HASH_VALUE& operator[](const std::string& key);

	int Size();

private:
	int HashFunction(const std::string& combination);

private:
	int maxValue_;
	int size_;

	HASH_VALUE* container_;
};

template<typename HASH_VALUE>
HashMap<HASH_VALUE>::HashMap()
{
	this->container_ = nullptr;
	this->maxValue_ = 0;
	this->size_ = 0;
}

template<typename HASH_VALUE>
HashMap<HASH_VALUE>::HashMap(int maxValue, HASH_VALUE defaultValue)
{
	this->maxValue_ = maxValue;

	this->container_ = new HASH_VALUE[this->maxValue_];

	for (int i = 0; i < this->maxValue_; ++i)
	{
		this->container_[i] = defaultValue;
	}
}

template<typename HASH_VALUE>
void HashMap<HASH_VALUE>::Insert(const std::string& key, HASH_VALUE value)
{
	int hashValueFromKey = this->HashFunction(key);

	if (hashValueFromKey >= this->maxValue_)
	{
		throw std::logic_error(std::format("[ERROR] HASH VALUE OUT OF RANGE! HASH VALUE MUST FROM [{}, {}]! PLEASE CHANGE USER'S INPUT MAX VALUE", 0, this->maxValue_ - 1));
		exit(1);
	}

	this->container_[hashValueFromKey] = value;

	this->size_ += 1;
}

template<typename HASH_VALUE>
HASH_VALUE HashMap<HASH_VALUE>::At(const std::string& key)
{
	return this->container_[this->HashFunction(key)];
}

template<typename HASH_VALUE>
HASH_VALUE& HashMap<HASH_VALUE>::operator[](const std::string& key)
{
	return this->container_[this->HashFunction(key)];
}

template<typename HASH_VALUE>
int HashMap<HASH_VALUE>::Size()
{
	return this->size_;
}

template<typename HASH_VALUE>
int HashMap<HASH_VALUE>::HashFunction(const std::string& combination)
{
	int result = 0;
	int base = 1;

	for (int i = 3; i >= 0; i--)
	{
		int numericalValue = combination[i] - 'A';
		result += numericalValue * base;
		base *= 26;
	}

	return result;
}


