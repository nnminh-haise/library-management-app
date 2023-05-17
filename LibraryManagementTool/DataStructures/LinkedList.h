#pragma once

#include <iostream>

template<typename T>
class LinkedList
{
public:
	struct Node
	{
		Node(T info, Node* next);

		friend std::ostream& operator<<(std::ostream& os, const Node& node) {
			os << node.info_;
			return os;
		}

		T info_;
		Node* next_;
	};

public:
	LinkedList();

	LinkedList(const LinkedList<int>& other);

	~LinkedList();

	bool Empty() const;

	int Size() const;

	Node& operator[] (int index);

	LinkedList<T>& operator=(const LinkedList<T>& other);

	Node* Begin();

	Node* End();

	void PushFront(T value);

	void PushBack(T value);

	T PopFront();

	T PopBack();

private:
	Node* first_;
	int size_;
};

template<typename T>
inline LinkedList<T>::Node::Node(T value, Node* next)
{
	this->info_ = value;
	this->next_ = next;
}

template<typename T>
LinkedList<T>::LinkedList()
{
	this->first_ = nullptr;
	this->size_ = 0;
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<int>& other)
{
	if (this != &other)
	{
		this->first_ = nullptr;
		this->size_ = 0;
		LinkedList<T>::Node* current = other.first_;

		while (current != nullptr)
		{
			this->PushBack(current->info_);
			current = current->next_;
		}
	}
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	Node* currentNode = this->first_;
	for (; currentNode != nullptr;)
	{
		Node* deleteNode = currentNode;
		currentNode = currentNode->next_;
		delete deleteNode;
	}
}

template<typename T>
inline bool LinkedList<T>::Empty() const
{
	return this->first_ == nullptr;
}

template<typename T>
inline int LinkedList<T>::Size() const
{
	return this->size_;
}

template<typename T>
inline LinkedList<T>::Node& LinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	LinkedList<T>::Node* target = this->first_;
	for (int i = 0; i != index && target != nullptr; target = target->next_, i++);
	return *target;
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	this->first_ = nullptr;
	LinkedList<T>::Node* current = other.first_;

	while (current != nullptr)
	{
		this->PushBack(current->info_);
		current = current->next_;
	}

	return *this;
}

template<typename T>
inline LinkedList<T>::Node* LinkedList<T>::Begin()
{
	if (this->Empty())
	{
		return nullptr;
	}

	return this->first_;
}

template<typename T>
inline LinkedList<T>::Node* LinkedList<T>::End()
{
	if (this->Empty())
	{
		return nullptr;
	}

	Node* lastNode = this->first_;
	for (; lastNode->next_ != nullptr; lastNode = lastNode->next_);
	return lastNode;
}

template<typename T>
inline void LinkedList<T>::PushFront(T value)
{
	Node* newNode = new Node(value, this->first_);
	this->first_ = newNode;
	this->size_ += 1;
}

template<typename T>
inline void LinkedList<T>::PushBack(T value)
{
	if (this->Empty())
	{
		this->PushFront(value);
		return;
	}

	Node* newNode = new Node(value, nullptr);
	Node* lastNode = this->first_;
	for (; lastNode->next_ != nullptr; lastNode = lastNode->next_);
	lastNode->next_ = newNode;
	this->size_ += 1;
}

template<typename T>
inline T LinkedList<T>::PopFront()
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] LIST IS EMPTY! CANNOT REMOVE ITEM!\n");
	}

	this->size_ -= 1;
	T returnValue = this->first_->info_;
	Node* deleteNode = this->first_;
	this->first_ = this->first_->next_;
	delete deleteNode;
	return returnValue;
}

template<typename T>
inline T LinkedList<T>::PopBack()
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] LIST IS EMPTY! CANNOT REMOVE ITEM!\n");
	}

	if (this->first_->next_ == nullptr)
	{
		return this->PopFront();
	}

	this->size_ -= 1;
	Node* lastNode = this->first_;
	for (; lastNode->next_->next_ != nullptr; lastNode = lastNode->next_);
	Node* deleteNode = lastNode->next_;
	T returnValue = deleteNode->info_;
	lastNode->next_ = nullptr;
	delete deleteNode;
	return returnValue;
}
