#pragma once

#include <string>
#include "../DataStructures/AVL_Tree.h"
#include "../DataStructures/DoubleLinkedList.h"
#include "../Helper/Helper.h"

namespace BOOK_CIRCULATION 
{
	enum CirculationStatus { BORROWING, RETURNED, LOSTED };

	class BookCirculation 
	{
	public:
		BookCirculation();

		BookCirculation(std::string id, HELPER::Date borrowDate, HELPER::Date returnDate, CirculationStatus status);

		~BookCirculation();

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

namespace BOOK_CIRCULATION_MODULES {
	int CountBorrowedBooks(const DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>& booksCirculation);
}

namespace READER 
{
	enum Gender { MALE, FEMALE };

	enum ReaderStatus { BANNED, ACTIVE };

	class Reader 
	{
	public:
		Reader();

		Reader(int id, std::string firstName, std::string lastName, Gender gender, ReaderStatus status, DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> booksCirculation);

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

		void SetBooksCirculation(DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> booksCirculation);

		DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> GetBooksCirculation();

		void Log();

	private:
		int id;
		std::string firstName;
		std::string lastName;
		Gender sex;
		ReaderStatus status;
		DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> booksCirculation;
	};
}

namespace READER_MODULES 
{
	bool LoadDanhSachTheDocGiaFromDB(const std::string& filename, AVL_Tree<READER::Reader, int>* tree);

	bool UpdateListToDatabase(const std::string& filename, AVL_Tree<READER::Reader, int>* tree);

	int GetIndex(const std::string& filename, AVL_Tree<READER::Reader, int>* tree);

	void SortByName(const AVL_Tree<READER::Reader, int>& tree, LinearList< AVL_Tree<READER::Reader, int>::Node*>& readerPointersArr);
}
