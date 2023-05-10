#include "Stack.h"

#include <iostream>
#include <string>
#include <format>

STACK::Node::Node() {
	this->info = nullptr;
	this->next = nullptr;
}

STACK::Node::Node(AVL_TREE::Pointer info, STACK::Node* next) {
	this->info = info;
	this->next = next;
}

void STACK::Initialize(STACK::Stack& First) {
	First = nullptr;
}

bool STACK::IsEmpty(const STACK::Stack& First) {
	return First == nullptr;
}

void STACK::Push(STACK::Stack& First, AVL_TREE::Pointer info) {
	STACK::Stack newNode = new STACK::Node(info, First);
	First = newNode;
}

AVL_TREE::Pointer STACK::Pop(STACK::Stack& First) {
	STACK::Stack removeNode = First;
	First = removeNode->next;
	AVL_TREE::Pointer returnInfo = removeNode->info;
	delete removeNode;
	return returnInfo;
}

void STACK::Traversal(const STACK::Stack& First) {
	for (STACK::Stack p = First; p != nullptr; p = p->next) {
		p->info->info.Log();
	}
}