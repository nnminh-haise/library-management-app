#pragma once

#include <string>
#include "../DataStructures/LinearList.h"

namespace BOOK 
{
	enum Status { AVAILABLE, UNAVAILABLE, SOLD };

	class Book 
	{
	public:
		Book();

		Book(std::string id, Status status, std::string description);

		void SetID(std::string id);

		std::string GetID();

		void SetStatus(Status status);

		Status GetStatus();

		std::string StringfyStatus();

		void SetDescription(std::string description);

		std::string GetDescription();

	private:
		std::string id;
		Status status;
		std::string description;
	};
}

namespace LINKED_LIST 
{
	struct Node 
	{
		BOOK::Book info;
		Node* next;

		Node();

		Node(BOOK::Book info, Node* next);
	};

	typedef Node* Pointer;

	struct Controller 
	{
		unsigned int total;
		unsigned int borrowed;
		unsigned int sold;
		Pointer first;
	};

	void Initialize(Controller& controller);

	bool Empty(const Controller& controller);

	int Size(const Controller& controller);

	void PushFront(Controller& controller, BOOK::Book item);

	void PushBack(Controller& controller, BOOK::Book item);

	bool DeleteAt(Controller& controller, BOOK::Book item);

	BOOK::Book* SearchByID(Controller& controller, const std::string& id);
}

namespace BOOK_TITLE 
{
	class BookTitle 
	{
	private:
		std::string isbn;
		std::string title;
		int pageCount;
		std::string author;
		int publiationYear;
		std::string category;
		LINKED_LIST::Controller catalogue;

	public:
		BookTitle();

		BookTitle(std::string isbn, std::string title, int pageCount, std::string author, int publiationYear, std::string category, LINKED_LIST::Controller catalogue);

		void SetISBN(std::string isbn);

		std::string GetISBN();

		void SetTitle(std::string title);

		std::string GetTitle();

		void SetPageCount(int sotrang);

		int GetPageCount();
		
		void SetAuthor(std::string author);

		std::string GetAuthor();

		void SetPublicationYear(int publiationYear);

		int GetPublicationYear();

		void SetCategory(std::string category);

		std::string GetCategory();

		void SetCatalogue(LINKED_LIST::Controller catalogue);

		LINKED_LIST::Controller GetCatalogue();

		void Log();
	};
}

class TitleLinearList : public LinearList<BOOK_TITLE::BookTitle*>
{
public:
	TitleLinearList();

	TitleLinearList(const TitleLinearList& other);

	~TitleLinearList();

	TitleLinearList& operator= (const TitleLinearList& other);

	void PushOrder(BOOK_TITLE::BookTitle* value);
};

namespace DAU_SACH_MODULES 
{
	BOOK_TITLE::BookTitle* SearchByName(const TitleLinearList* titleList, const std::string& titleName);

	BOOK_TITLE::BookTitle* SearchByISBN(const TitleLinearList* titleList, const std::string& isbn);

	bool LoadDanhSachDauSachFromDB(std::string filename, TitleLinearList* titleList);

	void DuplicateList(const LINEAR_LIST::LinearList& titleList, LINEAR_LIST::LinearList& destinationList);
}
