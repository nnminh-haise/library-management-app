#include "TheDocGia.h"
#include "../Helper/Helper.h"
#include "../DataStructures/Stack.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <ctime>

BOOK_CIRCULATION::BookCirculation::BookCirculation() :
    id(std::string()), borrowDate(HELPER::Date()), returnDate(HELPER::Date()), status(BOOK_CIRCULATION::CirculationStatus::LOSTED) {}

BOOK_CIRCULATION::BookCirculation::BookCirculation(std::string id, HELPER::Date NgayMuon, HELPER::Date NgayTra, BOOK_CIRCULATION::CirculationStatus status) :
    id(id), borrowDate(borrowDate), returnDate(returnDate), status(status) {}

BOOK_CIRCULATION::BookCirculation::~BookCirculation() {}

void BOOK_CIRCULATION::BookCirculation::SetID(std::string id) {
	this->id = id;
}

std::string BOOK_CIRCULATION::BookCirculation::GetID() {
	return this->id;
}

void BOOK_CIRCULATION::BookCirculation::SetBorrowDate(HELPER::Date NgayMuon) {
	this->borrowDate = NgayMuon;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetBorrowDate() {
	return this->borrowDate;
}

void BOOK_CIRCULATION::BookCirculation::SetReturnDate(HELPER::Date NgayTra) {
	this->returnDate = NgayTra;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetReturnDate() {
	return this->returnDate;
}

void BOOK_CIRCULATION::BookCirculation::SetStatus(BOOK_CIRCULATION::CirculationStatus status) {
	this->status = status;
}

BOOK_CIRCULATION::CirculationStatus BOOK_CIRCULATION::BookCirculation::GetStatus() {
	return this->status;
}

std::string BOOK_CIRCULATION::BookCirculation::StringfyStatus()
{
    if (this->status == BOOK_CIRCULATION::CirculationStatus::BORROWING)
    {
        return "BORROWING";
    }
    else if (this->status == BOOK_CIRCULATION::CirculationStatus::RETURNED)
    {
        return "RETURNED";
    }
    return "LOSTED";
}

bool BOOK_CIRCULATION::BookCirculation::IsOverdue()
{
    if (this->status != BOOK_CIRCULATION::CirculationStatus::BORROWING)
    {
        return false;
    }

    HELPER::Date today;
    if (today.DaysBetween(this->borrowDate) > 7)
    {
        return true;
    }
    return false;
}

int BOOK_CIRCULATION::BookCirculation::CountOverdueDate()
{
    if (!this->IsOverdue())
    {
        return 0;
    }
    return HELPER::Date().DaysBetween(this->borrowDate + 7);
}

READER::Reader::Reader()
{
	this->id = -1;
	this->firstName = std::string();
	this->lastName = std::string();
	this->sex = READER::Gender::MALE;
	this->status = READER::ReaderStatus::BANNED;
    this->booksCirculation = DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>();
}

READER::Reader::Reader(int MaThe, std::string Ho, std::string Ten, READER::Gender Phai, READER::ReaderStatus status, DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> booksCirculation)
{
	this->id = MaThe;
	this->firstName = Ho;
	this->lastName = Ten;
	this->sex = Phai;
	this->status = status;
    this->booksCirculation = booksCirculation;
}

READER::Reader& READER::Reader::operator=(const READER::Reader& other)
{
    if (this != &other)
    {
        id = other.id;
        firstName = other.firstName;
        lastName = other.lastName;
        sex = other.sex;
        status = other.status;
        booksCirculation = other.booksCirculation;
    }

    return *this;
}

void READER::Reader::SetID(int MaThe) {
	this->id = MaThe;
}

int READER::Reader::GetID() {
	return this->id;
}

void READER::Reader::SetFirstName(std::string Ho) {
	this->firstName = Ho;
}

std::string READER::Reader::GetFirstName() {
	return this->firstName;
}

void READER::Reader::SetLastName(std::string Ten) {
	this->lastName = Ten;
}

std::string READER::Reader::GetLastName() {
	return this->lastName;
}

void READER::Reader::SetGender(READER::Gender Phai) {
	this->sex = Phai;
}

READER::Gender READER::Reader::GetGender() {
	return this->sex;
}

std::string READER::Reader::GetFullName() {
    return this->firstName + " " + this->lastName;
}

std::string READER::Reader::StringifyGender() {
    return (this->sex == READER::Gender::MALE ? "MALE" : "FEMALE");
}

void READER::Reader::SetStatus(READER::ReaderStatus status) {
	this->status = status;
}

READER::ReaderStatus READER::Reader::GetStatus() {
	return this->status;
}

std::string READER::Reader::StringfyStatus() {
    return (this->status == READER::ReaderStatus::BANNED ? "BANNED" : "ACTIVE");
}

void READER::Reader::SetBooksCirculation(const DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>& booksCirculation)
{
	this->booksCirculation = booksCirculation;
}

DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> READER::Reader::GetBooksCirculation() {
	return this->booksCirculation;
}

void READER::Reader::Log()
{
	std::cerr << std::format("_____ THE DOC GIA _____\n");
	std::cerr << std::format("Ma the    : {}\n", this->id);
	std::cerr << std::format("firstName        : {}\n", this->firstName);
	std::cerr << std::format("lastName       : {}\n", this->lastName);
	std::cerr << std::format("sex      : {}\n", this->sex == READER::Gender::MALE ? "Nam" : "Nu");
	std::cerr << std::format("Trang thai: {}\n", this->status == READER::ReaderStatus::BANNED ? "Bi khoa" : "Hoat dong");

    if (this->booksCirculation.Empty())
    {
		std::cerr << std::format("Doc gia chua muon sach!\n");
	}
	else
    {
		std::cerr << std::format("Doc gia co muon sach!\n");
	}
	std::cerr << std::format("-----------------------\n");
}

/**
* READ DATA FROM FILE BASED DATABASE!
*
* 1. Create a file buffer reader.
* 2. Filter out the case where we cannot open the file!
*/
bool READER_MODULES::LoadDanhSachTheDocGiaFromDB(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
{
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

        READER::Reader newReader;

        for (int i = 0; i < dataCount; ++i) 
        {
            switch (i) 
            {
                case (0): {
                    newReader.SetID(std::stoi(data[i]));
                    break;
                }
                case (1): {
                    newReader.SetFirstName(data[i]);
                    break;
                }
                case (2): {
                    newReader.SetLastName(data[i]);
                    break;
                }
                case (3): {
                    newReader.SetGender(data[i] == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);
                    break;
                }
                case (4): {
                    newReader.SetStatus(data[i] == "BANNED" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE);
                    break;
                }
                case (5): {
                    int borrowedBooksCount = std::stoi(data[i]);
                    if (borrowedBooksCount == 0) //* Case where the reader did not borrowed any book!
                    {
                        newReader.SetBooksCirculation(DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>());
                    }
                    else //* Case where the reader borrowed at least one book!
                    {
                        DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> newBorrowedBooksList;

                        while (database && borrowedBooksCount--) {
                            BOOK_CIRCULATION::BookCirculation newBorrowedBook{};

                            std::string borrowedBookData{};
                            std::getline(database, borrowedBookData);

                            if (borrowedBookData.length() == 0)
                            {
                                throw std::logic_error(std::format("[ERROR] Empty book list data in database!\n"));
                            }

                            std::string* items = nullptr;
                            int itemCount = 0;
                            STR::Extract(borrowedBookData, ", ", items, itemCount);

                            newBorrowedBook.SetID(items[0]);
                            newBorrowedBook.SetBorrowDate(HELPER::Date(items[1]));
                            newBorrowedBook.SetReturnDate(HELPER::Date(items[2]));

                            if (items[3] == "BORROWING")
                            {
                                newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::BORROWING);
                            }
                            else if (items[3] == "RETURNED")
                            {
                                newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::RETURNED);
                            }
                            else if (items[3] == "LOSTED")
                            {
                                newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::LOSTED);
                            }
                            newBorrowedBooksList.PushBack(newBorrowedBook);
                        }

                        newReader.SetBooksCirculation(newBorrowedBooksList);
                    }
                    break;
                }
            }
        }

        tree->Insert(stoi(data[0]), newReader);
    }

    databaseBuffer.close();

    return true;
}

bool READER_MODULES::UpdateListToDatabase(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
{
    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::out))
    {
        throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
    }

    std::ostream database(&databaseBuffer);

    Stack<AVL_Tree<READER::Reader, int>::Node*> stk;

    AVL_Tree<READER::Reader, int>::Node* p = tree->GetRoot();

    do {
        while (p != nullptr) {
            stk.Push(p);
            p = p->left_;
        }

        if (stk.Empty() == false) {
            p = stk.Pop();
            
            database << p->info_.GetID() << ", ";
            database << p->info_.GetFirstName() << ", ";
            database << p->info_.GetLastName() << ", ";
            database << p->info_.StringifyGender() << ", ";
            database << p->info_.StringfyStatus() << ", ";

            if (p->info_.GetBooksCirculation().Empty()) {
                database << 0 << "\n";
            }
            else {
                //TODO: clean up here
                DoubleLinkedList<BOOK_CIRCULATION::BookCirculation> lst = p->info_.GetBooksCirculation();

                int cnt = 0;
                for (auto p = lst.Begin(); p != nullptr; p = p->right_)
                {
                    ++cnt;
                    std::cout << p->info_.GetID() << "\n";
                }

                int listSize = lst.Size();
                database << listSize << "\n";
                for (DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>::Node* currentNode = lst.Begin(); currentNode != nullptr; currentNode = currentNode->right_)
                {
                    database << currentNode->info_.GetID() << ", " << currentNode->info_.GetBorrowDate().Stringify() << ", " << currentNode->info_.GetReturnDate().Stringify() << ", " << currentNode->info_.StringfyStatus() << "\n";
                }
            }

            p = p->right_;
        }
        else {
            break;
        }
    } while (true);

    databaseBuffer.close();
    return true;
}

int READER_MODULES::GetIndex(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
{
    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::in))
    {
        std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
        return false;
    }

    int attributeCount = tree->Size();
    std::istream database(&databaseBuffer);

    for (int i = 0, tmp = 0; i < attributeCount; ++i, database >> tmp);
    std::string nextIndex{};
    database >> nextIndex;

    databaseBuffer.close();
    return std::stoi(nextIndex);
}

/*
* The algorithm is that we first create an array contains the pointer of all the node of the tree.
* Then we sort the array by comparing the value which the pointer pointed to and interchange the position of the element in the array
* without changing the positon of the node of the tree.
* 
! Currently, Selection sort is used! Therefore the time complexcity if very high!
*/
void READER_MODULES::SortByName(const AVL_Tree<READER::Reader, int>& tree, LinearList<AVL_Tree<READER::Reader, int>::Node*>& readerPointersArr)
{
    tree.CastToLinearList(readerPointersArr);

    int arrSize = readerPointersArr.Size();
    std::string valueA{}, valueB{};
    for (int i = 0; i < arrSize - 1; ++i)
    {
        for (int j = i + 1; j < arrSize; ++j)
        {
            valueA = readerPointersArr[i]->info_.GetLastName() + " " + readerPointersArr[i]->info_.GetFirstName();
            valueB = readerPointersArr[j]->info_.GetLastName() + " " + readerPointersArr[j]->info_.GetFirstName();

            if (valueA.compare(valueB) > 0)
            {
                std::swap(readerPointersArr[i], readerPointersArr[j]);
            }
        }
    }
}

int BOOK_CIRCULATION_MODULES::CountBorrowedBooks(const DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>& booksCirculation)
{
    int counter = 0;
    for (DoubleLinkedList<BOOK_CIRCULATION::BookCirculation>::Node* p = booksCirculation.Begin(); p != nullptr; p = p->right_)
    {
        if (p->info_.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING)
        {
            ++counter;
        }
    }
    return counter;
}
