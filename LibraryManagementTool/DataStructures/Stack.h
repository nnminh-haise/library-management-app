#pragma once

#include <iostream>

template<typename T>
class Stack
{
private:
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
	Stack();

	Stack(const Stack<T>& other);

	~Stack();

	bool Empty() const;

	int Size() const;

	Stack<T>& operator=(const Stack<T>& other);

	void Push(T value);

	T Pop();

	T Top() const;

	void Print();

private:
	Node* Begin();

	Node* End();

	Node* NodeAt(int index);

	Node& operator[] (int index);

	void PushBack(T value);

	T PopBack();

private:
	Node* first_;
	Node* last_;

	int size_;
};

template<typename T>
inline Stack<T>::Node::Node(T value, Node* left, Node* right) : info_(value), left_(left), right_(right) {}

template<typename T>
Stack<T>::Stack()
{
	this->first_ = this->last_ = nullptr;
	this->size_ = 0;
}

template<typename T>
inline Stack<T>::Stack(const Stack<T>& other)
{
	if (this != &other)
	{
		// Clear the current list
		this->~Stack();

		// Copy the size
		this->size_ = other.size_;

		// Copy the nodes
		Stack<T>::Node* current = other.first_;
		Stack<T>::Node* prev = nullptr;
		while (current != nullptr)
		{
			Stack<T>::Node* newNode = new Stack<T>::Node(current->info_, prev, nullptr);

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
inline Stack<T>::~Stack()
{
	Node* currentNode = this->first_;
	for (; currentNode != nullptr;)
	{
		Node* deleteNode = currentNode;
		currentNode = currentNode->right_;
		delete deleteNode;
	}
}

template<typename T>
inline bool Stack<T>::Empty() const
{
	return this->first_ == nullptr;
}

template<typename T>
inline int Stack<T>::Size() const
{
	return this->size_;
}

template<typename T>
inline Stack<T>::Node& Stack<T>::operator[](int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	Stack<T>::Node* target = this->first_;
	for (int i = 0; i != index && target != nullptr; target = target->right_, i++);
	return *target;
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	// Clear the current list
	this->~Stack();

	// Copy the size
	this->size_ = other.size_;

	// Copy the nodes
	Stack<T>::Node* current = other.first_;
	Stack<T>::Node* prev = nullptr;
	while (current != nullptr)
	{
		Stack<T>::Node* newNode = new Stack<T>::Node(current->info_, prev, nullptr);

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
inline Stack<T>::Node* Stack<T>::NodeAt(int index)
{
	if (index < 0 || index >= this->Size())
	{
		throw std::logic_error("[ERROR] INDEX OUT OF RANGE!\n");
	}

	Stack<T>::Node* target = this->first_;
	for (int i = 0; i != index && target != nullptr; target = target->right_, i++);
	return target;
}

template<typename T>
inline Stack<T>::Node* Stack<T>::Begin()
{
	if (this->Empty())
	{
		return nullptr;
	}

	return this->first_;
}

template<typename T>
inline Stack<T>::Node* Stack<T>::End()
{
	if (this->Empty())
	{
		return nullptr;
	}

	return this->last_;
}

template<typename T>
inline void Stack<T>::Push(T value)
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
inline void Stack<T>::PushBack(T value)
{
	if (this->Empty())
	{
		this->Push(value);
		return;
	}

	Node* newNode = new Node(value, this->last_, nullptr);
	this->size_ += 1;
	this->last_->right_ = newNode;
	this->last_ = newNode;
}

template<typename T>
inline T Stack<T>::Pop()
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
inline T Stack<T>::Top() const
{
	return this->first_->info_;
}

template<typename T>
inline void Stack<T>::Print()
{
	for (Stack<T>::Node* p = this->first_; p != nullptr; p = p->right_)
	{
		std::cout << p->info_ << " ";
	}
	std::cout << "\b\n";
}

template<typename T>
inline T Stack<T>::PopBack()
{
	if (this->Empty())
	{
		throw std::logic_error("[ERROR] LIST IS EMPTY! CANNOT REMOVE ITEM!\n");
	}

	if (this->first_->right_ == nullptr)
	{
		return this->Pop();
	}

	T returnValue = this->last_->info_;
	Node* deleteNode = this->last_;
	this->last_ = this->last_->left_;
	delete deleteNode;
	return returnValue;
}
