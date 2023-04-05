#pragma once

#include "../TheDocGia/TheDocGia.h"

/**
* This stack data structure is built based on the linked list data structure.
* The top element of the stack is the first element of the linked list.
*/

namespace STACK {
	const int MAX_SIZE = 1000;

	struct Node {
		AVL_TREE::Pointer info;
		Node* next;

		Node();

		Node(AVL_TREE::Pointer info, Node* next);
	};

	typedef Node* Stack;

	void Initialize(Stack& First);

	bool IsEmpty(const Stack& First);

	void Push(Stack& First, AVL_TREE::Pointer info);

	AVL_TREE::Pointer Pop(Stack& First);

	void Traversal(const Stack& First);
}