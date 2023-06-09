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

BOOK::Book::Book(const BOOK::Book& other)
{
	if (this != &other)
	{
		this->id = other.id;
		this->status = other.status;
		this->description = other.description;
	}
}

BOOK::Book& BOOK::Book::operator=(const BOOK::Book& other)
{
	if (this == &other) { return *this; }

	this->id = other.id;
	this->status = other.status;
	this->description = other.description;
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

void LINKED_LIST::Initialize(LINKED_LIST::Pointer& first)
{
	first = nullptr;
}

bool LINKED_LIST::Empty(const LINKED_LIST::Pointer& first)
{
	return first == nullptr;
}

int LINKED_LIST::Size(const Pointer& first)
{
	int counter = 0;
	for (LINKED_LIST::Pointer p = first; p != nullptr; p = p->next)
	{
		++counter;
	}

	return counter;
}

void LINKED_LIST::PushFront(Pointer& first, BOOK::Book item)
{
	LINKED_LIST::Pointer newNode = new LINKED_LIST::Node(item, nullptr);
	first = newNode;
}

void LINKED_LIST::PushBack(LINKED_LIST::Pointer& first, BOOK::Book item)
{
	if (LINKED_LIST::Empty(first))
	{
		LINKED_LIST::PushFront(first, item);
		return;
	}

	LINKED_LIST::Pointer newNode = new Node(item, nullptr);
	LINKED_LIST::Pointer Last = first;
	for (; Last->next != nullptr; Last = Last->next);
	Last->next = newNode;
}

void LINKED_LIST::Append(LINKED_LIST::Pointer& first, LINKED_LIST::Pointer& target)
{
	if (LINKED_LIST::Empty(first))
	{
		first = target;
		return;
	}

	LINKED_LIST::Pointer lastNode = first;
	for (; lastNode->next != nullptr; lastNode = lastNode->next);
	lastNode->next = target;
}

bool LINKED_LIST::DeleteAt(LINKED_LIST::Pointer& first, BOOK::Book item)
{
	if (LINKED_LIST::Empty(first))
	{
		return false;
	}

	if (first->next == nullptr && first->info.GetID().compare(item.GetID()) == 0)
	{
		delete first;
		first = nullptr;
		return true;
	}
	else if (first->next == nullptr)
	{
		return false;
	}

	LINKED_LIST::Pointer p = first;
	for (; p != nullptr && p->next != nullptr && p->next->info.GetID().compare(item.GetID()) != 0; p = p->next);

	if (p == nullptr) { return false; }

	LINKED_LIST::Pointer deleteNode = p->next;
	p->next = deleteNode->next;
	delete deleteNode;
	return true;
}

BOOK::Book* LINKED_LIST::SearchByID(LINKED_LIST::Pointer& first, const std::string& id)
{
	for (LINKED_LIST::Pointer currentNode = first; currentNode != nullptr; currentNode = currentNode->next)
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
	this->catalogue = nullptr;
}

BOOK_TITLE::BookTitle::BookTitle(std::string isbn, std::string title, int pageCount, std::string author, int publiationYear, std::string category, LINKED_LIST::Pointer catalogue) {
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

void BOOK_TITLE::BookTitle::SetCatalogue(LINKED_LIST::Pointer catalogue) {
	this->catalogue = catalogue;
}

LINKED_LIST::Pointer BOOK_TITLE::BookTitle::GetCatalogue() {
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

LINEAR_LIST::LinearList::LinearList() {
	this->numberOfNode = 0;
	for (int i = 0; i < LINEAR_LIST::MAX_SIZE; ++i) {
		this->nodes[i] = nullptr;
	}
}

void LINEAR_LIST::Initialize(LINEAR_LIST::LinearList& list) {
	list.numberOfNode = 0;
	for (int i = 0; i < LINEAR_LIST::MAX_SIZE; ++i) {
		list.nodes[i] = nullptr;
	}
}

bool LINEAR_LIST::Empty(const LinearList& list) {
	return list.numberOfNode == 0;
}

bool LINEAR_LIST::IsFull(const LinearList& list) {
	return list.numberOfNode == MAX_SIZE;
}

bool LINEAR_LIST::PushFront(LinearList& list, BOOK_TITLE::BookTitle* item) {
	if (LINEAR_LIST::IsFull(list)) {
		return false;
	}

	list.nodes[0] = item;
	list.numberOfNode = 1;
	return true;
}

bool LINEAR_LIST::InsertItem(LINEAR_LIST::LinearList& list, BOOK_TITLE::BookTitle* item, int position) {
	if (LINEAR_LIST::IsFull(list)) {
		std::cerr << std::format("[ERROR] LIST IS FULL CANNOT INSERT NEW ELEMENT!\nSUGGEST CREATE A NEW LIST WITH BIGGER SIZE!\n");
		exit(1);
	}

	if (position < 0 || position >= list.numberOfNode) {
		std::cerr << std::format("[ERROR] POSITION OUT OF RANGE! INSERT POSITION MUST IN RANGE 0 TO {}\n", LINEAR_LIST::MAX_SIZE - 1);
		exit(1);
	}

	//* Shift all item from position + 1 to the right by 1.
	for (int i = list.numberOfNode; i > position; --i) {
		list.nodes[i] = list.nodes[i - 1];
	}
	
	//* Insert new item into the list.
	list.nodes[position] = item;

	//* Increase the size of the list by one.
	++list.numberOfNode;

	return true;
}

bool LINEAR_LIST::PushBack(LinearList& list, BOOK_TITLE::BookTitle* item) {
	if (LINEAR_LIST::IsFull(list)) {
		std::cerr << std::format("[ERROR] DANH BOOK DAU BOOK IS FULL!\n");
		exit(1);
	}

	list.nodes[list.numberOfNode] = item;
	++list.numberOfNode;

	return false;
}

bool LINEAR_LIST::InsertOrder(LinearList& list, BOOK_TITLE::BookTitle* item) {
	if (LINEAR_LIST::IsFull(list)) {
		exit(1);
	}

	int index = 0;
	for (; index < list.numberOfNode && item->GetTitle().compare(list.nodes[index]->GetTitle()) >= 0; ++index);

	for (int i = list.numberOfNode; i > index; --i) {
		list.nodes[i] = list.nodes[i - 1];
	}

	list.numberOfNode++;
	list.nodes[index] = item;

	return true;
}

void LINEAR_LIST::Traversal(const LinearList& list) {
	for (int i = 0; i < list.numberOfNode; ++i) {
		list.nodes[i]->Log();
	}
}

BOOK_TITLE::BookTitle* LINEAR_LIST::SearchByName(const LinearList& list, const std::string& titleName) {
	if (LINEAR_LIST::Empty(list)) {
		return nullptr;
	}

	for (int i = 0; i < list.numberOfNode; ++i) {
		if (titleName.compare(list.nodes[i]->GetTitle()) == 0) {
			return list.nodes[i];
		}
	}

	return nullptr;
}

BOOK_TITLE::BookTitle* LINEAR_LIST::SearchByISBN(const LinearList& list, const std::string& isbn)
{
	for (int i = 0; i < list.numberOfNode; ++i)
	{
		if (isbn.compare(list.nodes[i]->GetISBN()) == 0)
		{
			return list.nodes[i];
		}
	}
	return nullptr;
}

bool DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(std::string filename, LINEAR_LIST::LinearList& danhSachDauSach) 
{
	LINEAR_LIST::Initialize(danhSachDauSach);
	
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) 
	{
		throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
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
						newTitle->SetCatalogue(nullptr);
					}
					else 
					{
						LINKED_LIST::Pointer newBookList = nullptr;
						LINKED_LIST::Initialize(newBookList);

						while (database && bookListSize--) 
						{
							BOOK::Book newBook{};

							std::string bookData{};
							std::getline(database, bookData);

							if (bookData.length() == 0) 
							{
								throw std::logic_error(std::format("[ERROR] Empty book list data in database!\n"));
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

		if (LINEAR_LIST::Empty(danhSachDauSach)) 
		{
			LINEAR_LIST::PushFront(danhSachDauSach, newTitle);
		}
		else 
		{
			LINEAR_LIST::InsertOrder(danhSachDauSach, newTitle);
		}
	}

	databaseBuffer.close();

	return true;
}

bool DAU_SACH_MODULES::UpdateListToDatabase(const std::string& filename, const LINEAR_LIST::LinearList& titleList) 
{
	std::cerr << "[LOG] Updating title list to database!\n";

	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::out)) 
	{
		throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
		return false;
	}

	std::ostream database(&databaseBuffer);

	for (int i = 0; i < titleList.numberOfNode; ++i) 
	{
		database << titleList.nodes[i]->GetISBN() << ", ";
		database << titleList.nodes[i]->GetTitle() << ", ";
		database << titleList.nodes[i]->GetPageCount() << ", ";
		database << titleList.nodes[i]->GetAuthor() << ", ";
		database << titleList.nodes[i]->GetPublicationYear() << ", ";
		database << titleList.nodes[i]->GetCategory() << ", ";

		LINKED_LIST::Pointer danhMucSach = titleList.nodes[i]->GetCatalogue();

		if (LINKED_LIST::Empty(danhMucSach)) 
		{
			database << 0 << "\n";
		}
		else 
		{
			int danhMucSachSize = LINKED_LIST::Size(danhMucSach);
			database << danhMucSachSize << "\n";
			for (LINKED_LIST::Pointer p = danhMucSach; p != nullptr; p = p->next) 
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

void DAU_SACH_MODULES::DuplicateList(const LINEAR_LIST::LinearList& titleList, LINEAR_LIST::LinearList& destinationList)
{
	destinationList.numberOfNode = titleList.numberOfNode;
	for (int i = 0; i < titleList.numberOfNode; ++i)
	{
		destinationList.nodes[i] = titleList.nodes[i];
	}
}
