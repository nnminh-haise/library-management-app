#pragma once

#include <string>
#include "../DataStructures/AVL_Tree.h"
#include "../Helper/Helper.h"

namespace BOOK_CIRCULATION
{
	enum CirculationStatus { BORROWING, RETURNED, LOSTED };

	class BookCirculation
	{
	public:
		BookCirculation();

		BookCirculation(std::string id, HELPER::Date borrowDate, HELPER::Date returnDate, CirculationStatus status);

		void SetID(std::string id);

		std::string GetID();

		void SetBorrowDate(HELPER::Date borrowDate);

		HELPER::Date GetBorrowDate();

		void SetReturnDate(HELPER::Date returnDate);

		HELPER::Date GetReturnDate();

		void SetStatus(CirculationStatus status);

		CirculationStatus GetStatus();

		std::string StringfyStatus();

		bool IsOverdue();

		int CountOverdueDate();

	private:
		std::string id;
		HELPER::Date borrowDate;
		HELPER::Date returnDate;
		CirculationStatus status;
	};
}

namespace DOUBLE_LINKED_LIST
{
	struct Node
	{
		Node();

		BOOK_CIRCULATION::BookCirculation info;
		Node* left;
		Node* right;
	};

	typedef Node* Pointer;

	struct Controller
	{
		Controller();

		Pointer First = nullptr;
		Pointer Last = nullptr;
	};

	void Initialize(DOUBLE_LINKED_LIST::Controller& list);

	bool Empty(const Controller& list);

	int Size(const Controller& list);

	void ClearList(Controller& list);

	void PushFront(Controller& list, BOOK_CIRCULATION::BookCirculation info);

	void PushBack(Controller& list, BOOK_CIRCULATION::BookCirculation info);

	void RemoveNode(Controller& list, DOUBLE_LINKED_LIST::Pointer targetNode);
}

namespace BOOK_CIRCULATION_MODULES {
	int CountBorrowedBooks(const DOUBLE_LINKED_LIST::Controller& list);
}

namespace READER
{
	enum Gender { MALE, FEMALE };

	enum ReaderStatus { BANNED, ACTIVE };

	class Reader
	{
	public:
		Reader();

		Reader(int id, std::string firstName, std::string lastName, Gender gender, ReaderStatus status, DOUBLE_LINKED_LIST::Controller borrowedBooks);

		void SetID(int id);

		int GetID();

		void SetFirstName(std::string firstName);

		std::string GetFirstName();

		void SetLastName(std::string lastName);

		std::string GetLastName();

		void SetGender(Gender sex);

		Gender GetGender();

		std::string GetFullName();

		std::string StringifyGender();

		void SetStatus(ReaderStatus status);

		ReaderStatus GetStatus();

		std::string StringfyStatus();

		void SetBooksCirculation(DOUBLE_LINKED_LIST::Controller borrowedBooks);

		DOUBLE_LINKED_LIST::Controller GetBooksCirculation();

		void Log();

	private:
		int id;
		std::string firstName;
		std::string lastName;
		Gender sex;
		ReaderStatus status;
		DOUBLE_LINKED_LIST::Controller borrowedBooks;
	};
}

namespace AVL_TREE 
{
	struct Node 
	{
		READER::Reader info;
		int balanceFactor = 0;
		int height = 1;
		Node* left = nullptr;
		Node* right = nullptr;

		Node();

		int GetKey();

		void SetKey(const int key);
	};

	typedef Node* Pointer;

	void Initialize(Pointer& root);

	bool Empty(const Pointer& root);

	void InOrderTraversal(const Pointer& root);

	void Size(const Pointer& root, int& counter);

	void NonrecursiveInOrderTraversal(const Pointer& root);

	Pointer RotateLeft(Pointer root);

	Pointer RotateRight(Pointer root);

	bool Insert(Pointer& root, READER::Reader info);

	Pointer SearchByKey(const Pointer& root, const int& key);

	Pointer GetMinValueNode(Pointer const& node);

	int GetHeight(Pointer node);

	void UpdateHeight(Pointer node);

	Pointer FindMinNode(Pointer node);

	Pointer Balance(Pointer node);

	Pointer RemoveNode(Pointer node, const int& key);
}

namespace READER_MODULES
{
	bool LoadDanhSachTheDocGiaFromDB(const std::string& filename, AVL_TREE::Pointer& root);

	bool UpdateListToDatabase(const std::string& filename, AVL_TREE::Pointer& root);

	int GetIndex(const std::string& filename, AVL_TREE::Pointer root);

	void SortByName(const AVL_TREE::Pointer& root, LinearList<AVL_TREE::Pointer>& readerPointersArr);
}