#pragma once

#include <string>
#include "../Helper/Helper.h"

namespace BOOK_CIRCULATION 
{
	enum CirculationStatus { BORROWED, RETURNED, LOSTED };

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

		Pointer First;
		Pointer Last;
	};

	void Initialize(DOUBLE_LINKED_LIST::Controller& list);

	bool IsEmpty(const Controller& list);

	int Size(const Controller& list);

	void ClearList(Controller& list);
}

namespace BOOK_CIRCULATION_MODULES {
	int CountBorrowedBooks(const DOUBLE_LINKED_LIST::Controller& list);
}

namespace READER 
{
	enum Sex { MALE, FEMALE };

	enum ReaderStatus { BANNED, ACTIVE };

	class Reader 
	{
	public:
		Reader();

		Reader(int id, std::string firstName, std::string lastName, Sex sex, ReaderStatus status, DOUBLE_LINKED_LIST::Controller borrowedBooks);

		void SetID(int id);

		int GetID();

		void SetFirstName(std::string firstName);

		std::string GetFirstName();

		void SetLastName(std::string lastName);

		std::string GetLastName();

		void SetSex(Sex sex);

		Sex GetSex();

		std::string GetFullName();

		std::string StringfySex();

		void SetStatus(ReaderStatus status);

		ReaderStatus GetStatus();

		std::string StringfyStatus();

		void SetBorrowedBooks(DOUBLE_LINKED_LIST::Controller borrowedBooks);

		DOUBLE_LINKED_LIST::Controller GetBorrowedBooks();

		void Log();

	private:
		int id;
		std::string firstName;
		std::string lastName;
		Sex sex;
		ReaderStatus status;
		DOUBLE_LINKED_LIST::Controller borrowedBooks;
	};
}

namespace AVL_TREE 
{
	struct Node 
	{
		READER::Reader info;
		int balanceFactor;
		int height;
		Node* left;
		Node* right;

		Node();

		int GetKey();

		void SetKey(const int key);
	};

	typedef Node* Pointer;

	void Initialize(Pointer& root);

	bool IsEmpty(const Pointer& root);

	void PreOrderTraversal(const Pointer& root);

	void InOrderTraversal(const Pointer& root);

	void PostOrderTraversal(const Pointer& root);

	void CountNode(const Pointer& root, int& counter);

	void NonrecursiveInOrderTraversal(const Pointer& root);

	Pointer RotateLeft(Pointer root);

	Pointer RotateRight(Pointer root);

	bool Insert(Pointer& root, READER::Reader info);

	Pointer SearchByKey(const Pointer& root, const int& key);

	Pointer GetMinValueNode(Pointer const& node);

	Pointer RemoveNode(Pointer& node, const int& key);
}

namespace READER_MODULES 
{
	bool TheDocGiaExtractor(std::string data, std::string seperator, READER::Reader& returnData);

	bool LoadDanhSachTheDocGiaFromDB(std::string filename, AVL_TREE::Pointer& tree);

	bool UpdateListToDatabase(const std::string& filename, AVL_TREE::Pointer& tree);

	int GetIndex(const std::string& filename, AVL_TREE::Pointer& tree);

	void SortByName(AVL_TREE::Pointer const& node, AVL_TREE::Pointer*& pointerArr, int& arrSize);
}
