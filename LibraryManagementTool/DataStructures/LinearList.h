#pragma once

#include <iostream>
#include <string>
#include <format>

template <typename T>
class LinearList
{
public:
	LinearList();

	LinearList(int capacity);

	LinearList(const LinearList<T>& other);

	~LinearList();

	LinearList<T>& operator=(const LinearList<T>& other);

	int Size() const;

	int Capacity() const;

	bool Empty() const;

	bool Full() const;

	void Clear() noexcept;

	void PushFront(T value);

	void PushBack(T value);

	void PushAt(T value, int position = 0);

	T PopFront();

	T PopBack();

	T PopAt(int position = 0);

	T& operator[](int index);

	T At(int index);

private:
	T* nodes_;
	int size_;
	int capacity_ = 100000;
};

template<typename T>
inline LinearList<T>::LinearList()
{
	this->nodes_ = new T [this->capacity_];
	this->size_ = 0;
}

template<typename T>
inline LinearList<T>::LinearList(int capacity)
{
	this->capacity_ = capacity;
	this->nodes_ = new T[this->capacity_];
	this->size_ = 0;
}

template<typename T>
inline LinearList<T>::LinearList(const LinearList<T>& other)
{
	if (this != &other)
	{
		delete[] this->nodes_;

		this->size_ = other.size_;
		this->capacity_ = other.capacity_;
		this->nodes_ = new T[this->capacity_];

		for (int i = 0; i < this->size_; ++i)
		{
			this->nodes_[i] = other.nodes_[i];
		}
	}
}

template<typename T>
inline LinearList<T>::~LinearList()
{
	delete[] this->nodes_;
}

template<typename T>
LinearList<T>& LinearList<T>::operator=(const LinearList<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] nodes_;

	size_ = other.size_;
	capacity_ = other.capacity_;
	nodes_ = new T[capacity_];

	for (int i = 0; i < size_; ++i)
	{
		nodes_[i] = other.nodes_[i];
	}

	return *this;
}

template<typename T>
inline int LinearList<T>::Size() const
{
	return this->size_;
}

template<typename T>
inline int LinearList<T>::Capacity() const
{
	return this->capacity_;
}

template<typename T>
inline bool LinearList<T>::Empty() const
{
	return this->size_ == 0;
}

template<typename T>
inline bool LinearList<T>::Full() const
{
	return this->size_ == this->capacity_;
}

template<typename T>
inline void LinearList<T>::Clear() noexcept
{
	std::destroy(this->nodes_, this->nodes_ + this->size_);
	this->size_ = 0;
}

template<typename T>
inline void LinearList<T>::PushFront(T value)
{
	if (this->Full())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS FULL! CANNOT INSERT NEW ELEMENT!\n"));
	}

	for (int i = this->size_; i > 0; --i)
	{
		this->nodes_[i] = this->nodes_[i - 1];
	}
	this->nodes_[0] = value;
	this->size_ += 1;
}

template<typename T>
inline void LinearList<T>::PushBack(T value)
{
	if (this->Full())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS FULL! CANNOT INSERT NEW ELEMENT!\n"));
	}

	this->nodes_[this->size_] = value;
	this->size_ += 1;
}

template<typename T>
inline void LinearList<T>::PushAt(T value, int position)
{
	if (this->Full())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS FULL! CANNOT INSERT NEW ELEMENT!\n"));
	}

	if (position < 0)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	if (position > this->size_)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	for (int i = this->size_; i > position; --i)
	{
		this->nodes_[i] = this->nodes_[i - 1];
	}
	this->nodes_[position] = value;
	this->size_ += 1;
}

template<typename T>
inline T LinearList<T>::PopFront()
{
	if (this->Empty())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS EMPTY! CANNOT POP NEW ELEMENT!\n"));
	}

	T returnValue = this->nodes_[0];
	for (int i = 0; i < this->size_ - 1; ++i)
	{
		this->nodes_[i] = this->nodes_[i + 1];
	}
	this->size_ -= 1;
	return returnValue;
}

template<typename T>
inline T LinearList<T>::PopBack()
{
	if (this->Empty())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS EMPTY! CANNOT POP NEW ELEMENT!\n"));
	}

	T returnValue = this->nodes_[this->size_ - 1];
	this->size_ -= 1;
	return returnValue;
}

template<typename T>
inline T LinearList<T>::PopAt(int position)
{
	if (this->Empty())
	{
		throw std::logic_error(std::format("[ERROR] LIST IS EMPTY! CANNOT POP NEW ELEMENT!\n"));
	}

	if (position < 0)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	if (position > this->size_)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	T returnValue = this->nodes_[position];
	for (int i = position; i < this->size_ - 1; ++i)
	{
		this->nodes_[i] = this->nodes_[i + 1];
	}
	return returnValue;
}

template<typename T>
inline T& LinearList<T>::operator[](int index)
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] EMPTY LIST\n");
	}

	if (index < 0 || index >= this->size_)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE\n");
	}

	return this->nodes_[index];
}

template<typename T>
inline T LinearList<T>::At(int index)
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] EMPTY LIST\n");
	}

	if (index < 0 || index >= this->size_)
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE\n");
	}

	return this->nodes_[index];
}
