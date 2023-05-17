#include "DauSach.h"
#include "../Helper/Helper.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>

BOOK::Book::Book() {
	this->id = std::string();
	this->status = BOOK::Status::AVAILABLE;
	this->description = std::string();
}

BOOK::Book::Book(std::string id, BOOK::Status status, std::string description) {
	this->id = id;
	this->status = status;
	this->description = description;
}

void BOOK::Book::SetID(std::string id) {
	this->id = id;
}

std::string BOOK::Book::GetID() {
	return this->id;
}

void BOOK::Book::SetStatus(Status status) {
	this->status = status;
}

BOOK::Status BOOK::Book::GetStatus() {
	return this->status;
}

std::string BOOK::Book::StringfyStatus() {
	switch (this->status) {
		case(BOOK::Status::AVAILABLE):
			return "AVAILABLE";
		case(BOOK::Status::UNAVAILABLE):
			return "UNAVAILABLE";
		case(BOOK::Status::SOLD):
			return "SOLD";
	}
	return std::string();
}

void BOOK::Book::SetDescription(std::string description) {
	this->description = description;
}

std::string BOOK::Book::GetDescription() {
	return this->description;
}

LINKED_LIST::Node::Node() : info(BOOK::Book()), next(nullptr) {
}

LINKED_LIST::Node::Node(BOOK::Book info, LINKED_LIST::Node* next) : info(info), next(next) {
}

void LINKED_LIST::Initialize(LINKED_LIST::Controller& controller) {
	controller.first = nullptr;
}

bool LINKED_LIST::Empty(const LINKED_LIST::Controller& controller) {
	return controller.first == nullptr;
}

int LINKED_LIST::Size(const Controller& controller) {
	int counter = 0;
	for (LINKED_LIST::Pointer p = controller.first; p != nullptr; p = p->next) {
		++counter;
	}

	return counter;
}

void LINKED_LIST::PushFront(Controller& controller, BOOK::Book item) {
	LINKED_LIST::Pointer newNode = new LINKED_LIST::Node(item, nullptr);
	controller.first = newNode;

	controller.total++;
	if (item.GetStatus() == BOOK::UNAVAILABLE) {
		controller.borrowed++;
	}
	else if (item.GetStatus() == BOOK::SOLD) {
		controller.sold++;
	}
}

void LINKED_LIST::PushBack(LINKED_LIST::Controller& controller, BOOK::Book item) {
	if (LINKED_LIST::Empty(controller)) {
		LINKED_LIST::PushFront(controller, item);
		return;
	}

	LINKED_LIST::Pointer newNode = new Node(item, nullptr);

	++controller.total;
	if (item.GetStatus() == BOOK::Status::UNAVAILABLE) {
		++controller.borrowed;
	}
	else if (item.GetStatus() == BOOK::Status::SOLD) {
		++controller.sold;
	}

	LINKED_LIST::Pointer Last = controller.first;
	for (; Last->next != nullptr; Last = Last->next);
	Last->next = newNode;
}

bool LINKED_LIST::DeleteAt(Controller& controller, BOOK::Book item) {
	if (LINKED_LIST::Empty(controller)) {
		return false;
	}

	if (controller.first->next == nullptr && controller.first->info.GetID().compare(item.GetID()) == 0) {
		delete controller.first;
		controller.first = nullptr;
		return true;
	}
	else if (controller.first->next == nullptr) {
		return false;
	}

	LINKED_LIST::Pointer p = controller.first;
	for (; p != nullptr && p->next != nullptr && p->next->info.GetID().compare(item.GetID()) != 0; p = p->next);

	if (p == nullptr) {
		return false;
	}

	LINKED_LIST::Pointer deleteNode = p->next;
	p->next = deleteNode->next;
	delete deleteNode;
	return true;
}

BOOK::Book* LINKED_LIST::SearchByID(Controller& controller, const std::string& id)
{
	for (LINKED_LIST::Pointer currentNode = controller.first; currentNode != nullptr; currentNode = currentNode->next)
	{
		if (id.compare(currentNode->info.GetID()) == 0)
		{
			return &currentNode->info;
		}
	}
	return nullptr;
}


BOOK_TITLE::BookTitle::BookTitle() {
	this->isbn = std::string();
	this->title = std::string();
	this->pageCount = 0;
	this->author = std::string();
	this->publiationYear = 0;
	this->category = std::string();
	this->catalogue.first = nullptr;
}

BOOK_TITLE::BookTitle::BookTitle(std::string isbn, std::string title, int pageCount, std::string author, int publiationYear, std::string category, LINKED_LIST::Controller catalogue) {
	this->isbn = isbn;
	this->title = title;
	this->pageCount = pageCount;
	this->author = author;
	this->publiationYear = publiationYear;
	this->category = category;
	this->catalogue = catalogue;
}

void BOOK_TITLE::BookTitle::SetISBN(std::string isbn) {
	this->isbn = isbn;
}

std::string BOOK_TITLE::BookTitle::GetISBN() {
	return this->isbn;
}

void BOOK_TITLE::BookTitle::SetTitle(std::string title) {
	this->title = title;
}

std::string BOOK_TITLE::BookTitle::GetTitle() {
	return this->title;
}

void BOOK_TITLE::BookTitle::SetPageCount(int soTrang) {
	this->pageCount = soTrang;
}

int BOOK_TITLE::BookTitle::GetPageCount() {
	return this->pageCount;
}

void BOOK_TITLE::BookTitle::SetAuthor(std::string author) {
	this->author = author;
}

std::string BOOK_TITLE::BookTitle::GetAuthor() {
	return this->author;
}

void BOOK_TITLE::BookTitle::SetPublicationYear(int publiationYear) {
	this->publiationYear = publiationYear;
}

int BOOK_TITLE::BookTitle::GetPublicationYear() {
	return this->publiationYear;
}

void BOOK_TITLE::BookTitle::SetCategory(std::string category) {
	this->category = category;
}

std::string BOOK_TITLE::BookTitle::GetCategory() {
	return this->category;
}

void BOOK_TITLE::BookTitle::SetCatalogue(LINKED_LIST::Controller catalogue) {
	this->catalogue = catalogue;
}

LINKED_LIST::Controller BOOK_TITLE::BookTitle::GetCatalogue() {
	return this->catalogue;
}

void BOOK_TITLE::BookTitle::Log() {
	std::cerr << std::format("___ Dau Book ___\n");
	std::cerr << std::format("isbn    : {}\n", this->isbn);
	std::cerr << std::format("lastName sach: {}\n", this->title);
	std::cerr << std::format("So trang: {}\n", this->pageCount);
	std::cerr << std::format("Tac gia : {}\n", this->author);
	std::cerr << std::format("NXB     : {}\n", this->publiationYear);
	std::cerr << std::format("The loai: {}\n", this->category);
	std::cerr << std::format("----------------\n");
}

BOOK_TITLE::BookTitle* DAU_SACH_MODULES::SearchByName(const TitleLinearList* titleList, const std::string& titleName)
{
	if (titleList->Empty())
	{
		return nullptr;
	}

	BOOK_TITLE::BookTitle* searchTarget = nullptr;
	for (int i = 0; i < titleList->Size(); ++i)
	{
		searchTarget = titleList->At(i);
		if (titleName.compare(searchTarget->GetTitle()) == 0)
		{
			return searchTarget;
		}
	}

	return nullptr;
}

BOOK_TITLE::BookTitle* DAU_SACH_MODULES::SearchByISBN(const TitleLinearList* titleList, const std::string& isbn)
{
	if (titleList->Empty())
	{
		return nullptr;
	}

	BOOK_TITLE::BookTitle* searchTarget = nullptr;
	for (int i = 0; i < titleList->Size(); ++i)
	{
		searchTarget = titleList->At(i);
		if (isbn.compare(searchTarget->GetISBN()) == 0)
		{
			return searchTarget;
		}
	}

	return nullptr;
}

bool DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(std::string filename, TitleLinearList* titleList)
{	
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) 
	{
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		exit(0);
	}

	std::istream database(&databaseBuffer);
	while (database) 
	{
		std::string titleData{};
		std::getline(database, titleData);

		if (titleData.length() == 0) 
		{
			continue;
		}

		std::string* data = nullptr;
		int dataCount = 0;
		STR::Extract(titleData, ", ", data, dataCount);

		BOOK_TITLE::BookTitle* newTitle = new BOOK_TITLE::BookTitle;

		for (int i = 0; i < dataCount; ++i) 
		{
			switch (i) 
			{
				case (0): 
				{
					newTitle->SetISBN(data[i]);
					break;
				}
				case (1): 
				{
					newTitle->SetTitle(data[i]);
					break;
				}
				case (2): 
				{
					newTitle->SetPageCount(std::stoi(data[i]));
					break;
				}
				case (3): 
				{
					newTitle->SetAuthor(data[i]);
					break;
				}
				case (4): 
				{
					newTitle->SetPublicationYear(std::stoi(data[i]));
					break;
				}
				case (5): 
				{
					newTitle->SetCategory(data[i]);
					break;
				}
				case (6): 
				{
					int bookListSize = std::stoi(data[i]);
					if (bookListSize == 0) 
					{
						newTitle->SetCatalogue(LINKED_LIST::Controller());
					}
					else 
					{
						LINKED_LIST::Controller newBookList;
						LINKED_LIST::Initialize(newBookList);

						while (database && bookListSize--) 
						{
							BOOK::Book newBook{};

							std::string bookData{};
							std::getline(database, bookData);

							if (bookData.length() == 0) 
							{
								std::cerr << std::format("[ERROR] Empty book list data in database!\n");
								exit(1);
							}

							std::string* bookItems = nullptr;
							int itemCount = 0;
							STR::Extract(bookData, ", ", bookItems, itemCount);

							newBook.SetID(bookItems[0]);
							if (bookItems[1] == "AVAILABLE") 
							{
								newBook.SetStatus(BOOK::AVAILABLE);
							}
							else if (bookItems[1] == "UNAVAILABLE") 
							{
								newBook.SetStatus(BOOK::UNAVAILABLE);
							}
							else 
							{
								newBook.SetStatus(BOOK::SOLD);
							}
							newBook.SetDescription(bookItems[2]);

							LINKED_LIST::PushBack(newBookList, newBook);
						}

						newTitle->SetCatalogue(newBookList);
					}
					break;
				}
			}
		}

		if (titleList->Empty()) 
		{
			titleList->PushFront(newTitle);
		}
		else 
		{
			titleList->PushFront(newTitle);
		}
	}

	databaseBuffer.close();

	return true;
}

bool DAU_SACH_MODULES::UpdateListToDatabase(const std::string& filename, const TitleLinearList* titleList)
{
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::out)) 
	{
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::ostream database(&databaseBuffer);

	for (int i = 0; i < titleList->Size(); ++i) 
	{
		database << titleList->At(i)->GetISBN() << ", ";
		database << titleList->At(i)->GetTitle() << ", ";
		database << titleList->At(i)->GetPageCount() << ", ";
		database << titleList->At(i)->GetAuthor() << ", ";
		database << titleList->At(i)->GetPublicationYear() << ", ";
		database << titleList->At(i)->GetCategory() << ", ";

		LINKED_LIST::Controller danhMucSach = titleList->At(i)->GetCatalogue();
		
		if (LINKED_LIST::Empty(danhMucSach)) 
		{
			database << 0 << "\n";
		}
		else 
		{
			int danhMucSachSize = LINKED_LIST::Size(danhMucSach);
			database << danhMucSachSize << "\n";
			for (LINKED_LIST::Pointer p = danhMucSach.first; p != nullptr; p = p->next) 
			{
				database << p->info.GetID() << ", ";
				database << p->info.StringfyStatus() << ", ";
				database << p->info.GetDescription() << "\n";
			}
		}
	}

	databaseBuffer.close();
	return true;
}

TitleLinearList::TitleLinearList() : LinearList<BOOK_TITLE::BookTitle*>() {}

TitleLinearList::TitleLinearList(const TitleLinearList& other) : LinearList<BOOK_TITLE::BookTitle*>(other) {}

TitleLinearList::~TitleLinearList() {}

TitleLinearList& TitleLinearList::operator=(const TitleLinearList& other)
{
	if (this == &other)
	{
		return *this;
	}

	LinearList<BOOK_TITLE::BookTitle*>::operator=(other);
	return *this;
}

void TitleLinearList::PushOrder(BOOK_TITLE::BookTitle* value)
{
	if (this->Full())
	{
		throw std::logic_error("[ERROR] LIST IS FULL! CANNOT INSERT MORE TITLE!");
	}

	int index = 0;
	for (; index < this->Size() && value->GetTitle().compare((*this)[index]->GetTitle()) >= 0; ++index);

	LinearList<BOOK_TITLE::BookTitle*>::PushAt(value, index);
}
