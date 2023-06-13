#include "DanhSachTheDocGia.h"
#include "DanhSachTheDocGiaStyling.h"

#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/IndexGenerator.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>

DanhSachTheDocGiaView::DanhSachTheDocGiaView()
{
	this->Initialize();
}

DanhSachTheDocGiaView::DanhSachTheDocGiaView(Package* package)
{
	this->package_ = package;

	this->Initialize();

	this->mainView_.SetPackage(package);
}

int DanhSachTheDocGiaView::Run()
{
	if (!this->status_) { return 0; }

	if (this->mainView_.InActive())
	{
		int mainViewRunningResult = this->mainView_.Run();
	}

	return 0;
}

void DanhSachTheDocGiaView::Initialize()
{
	this->InitializeElements();

	this->mainView_.Activate();
}

void DanhSachTheDocGiaView::InitializeElements()
{
}

READER_TAB_MEMBERS::MainView::MainView()
{
	this->Initialize();
}

void READER_TAB_MEMBERS::MainView::SetPackage(Package* package)
{
	this->package_ = package;

	std::cerr << "[LOG] Main view's package SET! (READER_TAB_MEMBERS::MainView::SetPackage)\n";

	this->InitializeFilters();

	this->CreateSortedByNameReaderList();

	this->InitializeReaderTable();

	std::cerr << "[LOG] Set package's pointer CLOSE! (READER_TAB_MEMBERS::MainView::SetPackage)\n";
}

int READER_TAB_MEMBERS::MainView::Run()
{
	if (!this->status_) { return 0; }

	if (this->readerTablePackage_.InActive())
	{
		this->readerTablePackage_.Run();
	}



	return 0;
}

void READER_TAB_MEMBERS::MainView::Initialize()
{
	this->InitializeElements();
}

void READER_TAB_MEMBERS::MainView::InitializeElements()
{
}

void READER_TAB_MEMBERS::MainView::InitializeFilters()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	int readerListSize{ 0 };
	AVL_TREE::Size(*this->package_->readerList, readerListSize);

	this->defaultReaderListFilter_.filterSize_ = readerListSize;
	this->defaultReaderListFilter_.keep_ = readerListSize;
	this->defaultReaderListFilter_.filters_ = new bool[readerListSize];
	for (int i = 0; i < readerListSize; ++i)
	{
		this->defaultReaderListFilter_.filters_[i] = true;
	}
	std::cerr << "[LOG] Created default list's filters!\n";

	this->sortedByNameReaderListFilter_.filterSize_ = readerListSize;
	this->sortedByNameReaderListFilter_.keep_ = readerListSize;
	this->sortedByNameReaderListFilter_.filters_ = new bool[readerListSize];
	for (int i = 0; i < readerListSize; ++i)
	{
		this->sortedByNameReaderListFilter_.filters_[i] = true;
	}
	std::cerr << "[LOG] Created sorted list's filters!\n";
}

void READER_TAB_MEMBERS::MainView::InitializeReaderTable()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	std::cerr << "[LOG] Creating reader TABLE!\n";

	this->readerTablePackage_.Activate();
	this->readerTablePackage_.SetDataList(this->package_->readerList);
	this->readerTablePackage_.SetDataFilter(&this->defaultReaderListFilter_);
	this->readerTablePackage_.SetSelectedObjectContainer(&this->tableSelectedObject_);
	this->readerTablePackage_.AllowCreateDatasheet();
	this->readerTablePackage_.CreateDatasheet();

	std::cerr << "[LOG] Created reader TABLE!\n";
}

void READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	std::cerr << "[LOG] Creating reader list sorted by name!\n";

	int readerListSize{ 0 };
	AVL_TREE::Size(*this->package_->readerList, readerListSize);
	this->sortedByNameReaderList_ = LinearList<AVL_TREE::Pointer>(readerListSize);

	Stack<AVL_TREE::Pointer> pointerStack;
	AVL_TREE::Pointer currentNode = *this->package_->readerList;
	do {
		while (currentNode != nullptr) {
			pointerStack.Push(currentNode);
			currentNode = currentNode->left;
		}

		if (pointerStack.Empty() == false) {
			currentNode = pointerStack.Pop();

			this->sortedByNameReaderList_.PushBack(currentNode);

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);

	std::string fullnameI{}, fullnameJ{};
	for (int i = 0; i < readerListSize - 1; ++i)
	{
		for (int j = i + 1; j < readerListSize; ++j)
		{
			fullnameI = this->sortedByNameReaderList_[i]->info.GetLastName() + " " + this->sortedByNameReaderList_[i]->info.GetFirstName();
			fullnameJ = this->sortedByNameReaderList_[j]->info.GetLastName() + " " + this->sortedByNameReaderList_[j]->info.GetFirstName();

			if (fullnameI.compare(fullnameJ) > 0)
			{
				std::swap(this->sortedByNameReaderList_[i], this->sortedByNameReaderList_[j]);
			}
		}
	}

	std::cerr << "[LOG] Created reader list sorted by name!\n";
}

void READER_TAB_MEMBERS::MainView::Log()
{
	std::cerr << "Package pointer status: " << (this->package_ != nullptr) << "\n";
}

void READER_TAB_MEMBERS::MainView::LogSortedList()
{
	for (int i = 0; i < this->sortedByNameReaderList_.Size(); ++i)
	{
		std::cerr << this->sortedByNameReaderList_[i]->info.GetID() << "\n";
		std::cerr << this->sortedByNameReaderList_[i]->info.GetFullName() << "\n";
	}
}
