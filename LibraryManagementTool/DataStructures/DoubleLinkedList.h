#pragma once

#include <iostream>

template<typename T>
class DoubleLinkedList
{
public:
	struct Node
	{
		Node(T info, Node* left, Node* right);

		friend std::ostream& operator<<(std::ostream& os, const Node& node) {
			os << node.info_;
			return os;
		}

		T info_;
		Node* left_;
		Node* right_;
	};

public:
	DoubleLinkedList();

	DoubleLinkedList(const DoubleLinkedList<T>& other);

	~DoubleLinkedList();

	bool Empty() const;

	int Size() const;

	Node& operator[] (int index);

	DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>& other);

	Node* NodeAt(int index);

	Node* Begin() const;

	Node* End() const;

	void PushFront(T value);

	void PushBack(T value);

	T PopFront();

	T PopBack();

private:
	Node* first_;
	Node* last_;

	int size_;
};

template<typename T>
inline DoubleLinkedList<T>::Node::Node(T value, Node* left, Node* right) : info_(value), left_(left), right_(right) {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	this->first_ = this->last_ = nullptr;
	this->size_ = 0;
}

template<typename T>
inline DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other)
{
	if (this != &other)
	{
		// Clear the current list
		this->~DoubleLinkedList();

		// Copy the size
		this->size_ = other.size_;

		// Copy the nodes
		DoubleLinkedList<T>::Node* current = other.first_;
		DoubleLinkedList<T>::Node* prev = nullptr;
		while (current != nullptr)
		{
			DoubleLinkedList<T>::Node* newNode = new DoubleLinkedList<T>::Node(current->info_, prev, nullptr);

			if (prev != nullptr)
			{
				prev->right_ = newNode;
			}
			else
			{
				this->first_ = newNode;
			}

			prev = newNode;
			current = current->right_;
		}

		// Update the last node
		this->last_ = prev;
	}
}

template<typename T>
inline DoubleLinkedList<T>::~DoubleLinkedList()
{
	//Node* currentNode = this->first_;
	//for (; currentNode != nullptr;)
	//{
	//	Node* deleteNode = currentNode;
	//	currentNode = currentNode->right_;
	//	delete deleteNode;
	//}
}

template<typename T>
inline bool DoubleLinkedList<T>::Empty() const
{
	return this->first_ == nullptr;
}

template<typename T>
inline int DoubleLinkedList<T>::Size() const
{
	return this->size_;
}

template<typename T>
inline DoubleLinkedList<T>::Node& DoubleLinkedList<T>::operator[](int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	DoubleLinkedList<T>::Node* target = this->first_;
	for (int i = 0; i != index && target != nullptr; target = target->right_, i++);
	return *target;
}

template<typename T>
inline DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	// Clear the current list
	this->~DoubleLinkedList();

	// Copy the size
	this->size_ = other.size_;

	// Copy the nodes
	DoubleLinkedList<T>::Node* current = other.first_;
	DoubleLinkedList<T>::Node* prev = nullptr;
	while (current != nullptr)
	{
		DoubleLinkedList<T>::Node* newNode = new DoubleLinkedList<T>::Node(current->info_, prev, nullptr);

		if (prev != nullptr)
		{
			prev->right_ = newNode;
		}
		else
		{
			this->first_ = newNode;
		}

		prev = newNode;
		current = current->right_;
	}

	// Update the last node
	this->last_ = prev;

	return *this;
}

template<typename T>
inline DoubleLinkedList<T>::Node* DoubleLinkedList<T>::NodeAt(int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	DoubleLinkedList<T>::Node* target = this->first_;
	for (int i = 0; i != index && target != nullptr; target = target->right_, i++);
	return target;
}

template<typename T>
inline DoubleLinkedList<T>::Node* DoubleLinkedList<T>::Begin() const
{
	if (this->Empty())
	{
		return nullptr;
	}

	return this->first_;
}

template<typename T>
inline DoubleLinkedList<T>::Node* DoubleLinkedList<T>::End() const
{
	if (this->Empty())
	{
		return nullptr;
	}

	return this->last_;
}

template<typename T>
inline void DoubleLinkedList<T>::PushFront(T value)
{
	Node* newNode = new Node(value, nullptr, this->first_);
	this->size_ += 1;
	if (this->Empty())
	{
		this->first_ = newNode;
		this->last_ = newNode;
		return;
	}
	this->first_->left_ = newNode;
	this->first_ = newNode;
}

template<typename T>
inline void DoubleLinkedList<T>::PushBack(T value)
{
	if (this->Empty())
	{
		this->PushFront(value);
		return;
	}

	Node* newNode = new Node(value, this->last_, nullptr);
	this->size_ += 1;
	this->last_->right_ = newNode;
	this->last_ = newNode;
}

template<typename T>
inline T DoubleLinkedList<T>::PopFront()
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] LIST IS EMPTY! CANNOT REMOVE ITEM!\n");
	}

	T returnValue = this->first_->info_;
	Node* deleteNode = this->first_;
	this->first_ = this->first_->right_;
	delete deleteNode;
	return returnValue;
}

template<typename T>
inline T DoubleLinkedList<T>::PopBack()
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] LIST IS EMPTY! CANNOT REMOVE ITEM!\n");
	}

	if (this->first_->right_ == nullptr)
	{
		return this->PopFront();
	}

	T returnValue = this->last_->info_;
	Node* deleteNode = this->last_;
	this->last_ = this->last_->left_;
	delete deleteNode;
	return returnValue;
}
