#include "BookCirculationView.h"

BOOK_CIRCULATION_VIEW::SearchBox::SearchBox()
{
	this->Initialize();
}

BOOK_CIRCULATION_VIEW::SearchBox::SearchBox(const SearchBox& other)
{
	if (this != &other)
	{
		this->~SearchBox();

		status_ = other.status_;
		title_ = other.title_;
		searchBox_ = other.searchBox_;
		readerPointer_ = other.readerPointer_;
		package_ = other.package_;
		readerTablePackage_ = other.readerTablePackage_;
		searchFilters_ = other.searchFilters_;
	}
}

BOOK_CIRCULATION_VIEW::SearchBox& BOOK_CIRCULATION_VIEW::SearchBox::operator=(const SearchBox& other)
{
	if (this == &other) { return *this; }

	this->~SearchBox();

	status_ = other.status_;
	title_ = other.title_;
	searchBox_ = other.searchBox_;
	readerPointer_ = other.readerPointer_;
	package_ = other.package_;
	readerTablePackage_ = other.readerTablePackage_;
	searchFilters_ = other.searchFilters_;
}

void BOOK_CIRCULATION_VIEW::SearchBox::SetPackage(Package* package)
{
	this->package_ = package;
}

void BOOK_CIRCULATION_VIEW::SearchBox::SetSearchData(AVL_TREE::Pointer readerPointer)
{
	this->readerPointer_ = readerPointer;
}

void BOOK_CIRCULATION_VIEW::SearchBox::SetReaderDatasheetPackage(BOOK_CIRCULATION_TABLE::DatasheetProcessor* datasheetPackage)
{
	this->readerTablePackage_ = datasheetPackage;
}

/** SEACH ALGORITHM
* There are some cases where we don't need to seach:
* 0. The seach section is inactive
* 1. The value of the seach box is equal to the default value
*
* After passing the above guard, the search algorithm start.
* The function return true, if there is a change in the filter, otherwise return false.
*
* (1): Firstly, in order to detect changes we need to keep an old version of the filter in order to do the comparaison.
* (2): Secondly, we give a linear scan through the title list, at each title, we compare the title's ISBN and the title with the
* search value. If the search value is a sub-string of the ISBN of the title then we update the filter.
* (3): Compare the original filter with new filter, if there are any changes then return true to allow re-generate the datasheet.
* Otherwise, return false.
*/
bool BOOK_CIRCULATION_VIEW::SearchBox::SearchOperation()
{
	const std::string searchTarget = this->searchBox_.GetPlaceholder();

	if (!this->status_) { return false; }

	if (this->readerPointer_ == nullptr)
	{
		std::cerr << "[ERROR] Reader's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchOperation)\n";
		throw std::logic_error("[ERROR] Reader's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchOperation)\n");

		return false;
	}

	if (searchTarget.compare("Type here to search!") == 0)
	{
		DataFilter*& dataFilter = this->readerTablePackage_->AccessDataFilter();
		dataFilter->keep_ = dataFilter->filterSize_;
		for (int i = 0; i < dataFilter->filterSize_; ++i) { dataFilter->filters_[i] = true; }

		return false;
	}

	//std::cerr << "[LOG] STARTING Search operation!\n";

	//* Initialize necessary variables
	auto searchData = this->readerPointer_->info.GetBooksCirculation();
	int dataSetSize = DOUBLE_LINKED_LIST::Size(searchData);
	DataFilter*& dataFilter = this->readerTablePackage_->AccessDataFilter();
	std::string bookID{};
	std::string borrowDate{};
	std::string returnDate{};
	std::string bookStatus{};

	//* Initialize filter's checkers
	int filterCount = 5;
	bool* filterCheckers = new bool[filterCount];
	for (int i = 0; i < filterCount; ++i) { filterCheckers[i] = false; }

	//* (1) Create a temperary version of the current filter!
	DataFilter orignalFilter;
	orignalFilter.filterSize_ = dataFilter->filterSize_;
	orignalFilter.keep_ = dataFilter->keep_;
	orignalFilter.filters_ = new bool[orignalFilter.filterSize_];
	for (int i = 0; i < orignalFilter.filterSize_; ++i) { orignalFilter.filters_[i] = dataFilter->filters_[i]; }

	//* (2) Search and update filter.
	int index = 0;
	for (auto currentNode = searchData.First; currentNode != nullptr; currentNode = currentNode->right)
	{
		for (int i = 0; i < filterCount; ++i) { filterCheckers[i] = false; }

		bookID = currentNode->info.GetID();
		borrowDate = currentNode->info.GetBorrowDate().Stringify();
		returnDate = currentNode->info.GetReturnDate().Stringify();
		bookStatus = currentNode->info.StringfyStatus();

		//std::cerr << "Checking in: " << readerFirstName + " " + readerLastName << "\n";

		if (bookID.find(searchTarget) != std::string::npos) { filterCheckers[0] = true; }
		if (borrowDate.find(searchTarget) != std::string::npos) { filterCheckers[1] = true; }
		if (returnDate.find(searchTarget) != std::string::npos) { filterCheckers[2] = true; }
		if (bookStatus.compare(searchTarget) == 0) { filterCheckers[3] = true; }

		bool res = false;
		for (int i = 0; i < filterCount; ++i)
		{
			res = res || (filterCheckers[i] * this->searchFilters_.FilterValue(i));
		}

		//* Only update filter if there are any changes
		if (res)
		{
			// The current filter is already correct, therefore we don't need to update the filter
			if (dataFilter->filters_[index] == false)
			{
				// Update filter
				if (dataFilter->keep_ < dataFilter->filterSize_) { dataFilter->keep_ += 1; }
				dataFilter->filters_[index] = true;
			}
		}
		else
		{
			// The current filter is already correct, therefore we don't need to update the filter
			if (dataFilter->filters_[index] == true)
			{
				// Update filter
				if (dataFilter->keep_ > 0) { dataFilter->keep_ -= 1; }
				dataFilter->filters_[index] = false;
			}
		}

		++index;
	}

	//* (3) Detect changes
	bool existChanges = false;
	for (int i = 0; i < dataFilter->filterSize_; ++i)
	{
		if (dataFilter->filters_[i] != orignalFilter.filters_[i])
		{
			existChanges = true;
			break;
		}
	}

	delete orignalFilter.filters_;
	delete[] filterCheckers;

	//std::cerr << "[LOG] EDNED Search operation!\n";

	return existChanges;
}

void BOOK_CIRCULATION_VIEW::SearchBox::SearchBoxOnAction()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchBoxOnAction)\n";
		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchBoxOnAction)");
	}

	if (this->searchBox_.IsHover())
	{
		this->searchBox_.SetFillColor(rgb(246, 241, 241));
	}
	else if (this->searchBox_.LeftMouseClicked())
	{
		delay(100);
		this->package_->inputController->Activate(
			&this->searchBox_,
			&this->searchBox_,
			50,
			true,
			true,
			true
		);
	}
	else
	{
		this->searchBox_.SetFillColor(rgb(241, 246, 249));
	}
}

void BOOK_CIRCULATION_VIEW::SearchBox::Display()
{
	if (this->status_ == false) { return; }

	this->title_.Display();
	this->searchBox_.Display();
	this->searchFilters_.Display();
}

int BOOK_CIRCULATION_VIEW::SearchBox::Run()
{
	if (!this->status_) { return 0; }

	this->Display();
	this->SearchBoxOnAction();
	if (this->SearchOperation()) { return 1; }

	return 0;
}

void BOOK_CIRCULATION_VIEW::SearchBox::Initialize()
{
	this->title_ = Button(HELPER::Coordinate(1487, 885), 210, 50);
	this->title_.SetFillColor(rgb(33, 42, 62));
	this->title_.SetBorderColor(rgb(33, 42, 62));

	this->searchBox_ = Button(HELPER::Coordinate(1492, 890), 200, 40);
	this->searchBox_.SetPlaceholder("Type here to search!");

	this->InitializeSearchFilters();
}

void BOOK_CIRCULATION_VIEW::SearchBox::InitializeSearchFilters()
{
	this->searchFilters_ = SearchFilters(4);

	std::string filterPlaceholders[] = { "Book ID", "Borrow Date", "Return Date", "Status" };
	HELPER::Coordinate filterCoordinates[] = { {36, 210}, {36, 290}, {36, 370}, {36, 450} };
	bool filterDefaultValues[] = { true, true, true, true };
	for (int i = 0; i < 4; ++i)
	{
		this->searchFilters_[i].SetPlaceholder(filterPlaceholders[i]);
		this->searchFilters_[i].SetTopLeft(filterCoordinates[i]);
		this->searchFilters_[i].SetValue(filterDefaultValues[i]);
	}
	this->searchFilters_.Activate();
}

BOOK_CIRCULATION_VIEW::ToolSets::ToolSets()
{
	this->Initialize();
}

void BOOK_CIRCULATION_VIEW::ToolSets::Activate()
{
	this->status_ = true;
}

void BOOK_CIRCULATION_VIEW::ToolSets::Deactivate()
{
	this->Reset();
	this->status_ = false;
}

bool BOOK_CIRCULATION_VIEW::ToolSets::InActive()
{
	return this->status_ == true;
}

int BOOK_CIRCULATION_VIEW::ToolSets::Run()
{
	if (package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (BOOK_CIRCULATION_VIEW::ToolSets::Run)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (BOOK_CIRCULATION_VIEW::ToolSets::Run)\n");
	}

	if (reader_ == nullptr)
	{
		std::cerr << "[ERROR] Reader's pointer is NULL! (BOOK_CIRCULATION_VIEW::ToolSets::Run)\n";

		throw std::logic_error("[ERROR] Reader's pointer is NULL! (BOOK_CIRCULATION_VIEW::ToolSets::Run)\n");
	}


	if (!this->status_) { return 0; }

	this->Display();

	int selectedTool = this->ToolButtonsOnAction();
	if (selectedTool != 0)
	{
		return selectedTool;
	}

	return 0;
}

void BOOK_CIRCULATION_VIEW::ToolSets::Reset()
{
	this->Initialize();
}

void BOOK_CIRCULATION_VIEW::ToolSets::SetPackage(Package* package)
{
	if (package == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL!\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL!\n");
	}

	std::cerr << "[LOG] Tools Set SET package!\n";

	this->package_ = package;
}

void BOOK_CIRCULATION_VIEW::ToolSets::SetReader(AVL_TREE::Pointer reader)
{
	this->reader_ = reader;
}

void BOOK_CIRCULATION_VIEW::ToolSets::Initialize()
{
	this->InitializeElements();
}

void BOOK_CIRCULATION_VIEW::ToolSets::InitializeElements()
{
	HELPER::Coordinate topLefts[] = {
		{1038, 445}, {1038, 502}, {1038, 559}
	};
	std::string placeholders[] = { "BORROW", "RETURN", "LOST" };
	for (int i = 0; i < 3; ++i)
	{
		this->toolButtons_[i] = Button(topLefts[i], { 120, 47 });
		this->toolButtons_[i].SetPlaceholder(placeholders[i]);
		this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
		this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
		this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
	}
}

int BOOK_CIRCULATION_VIEW::ToolSets::Display()
{
	if (!this->status_) { return 0; }

	for (int i = 0; i < 3; ++i)
	{
		this->toolButtons_[i].Display();
	}

	return 0;
}

int BOOK_CIRCULATION_VIEW::ToolSets::ToolButtonsOnAction()
{
	if (!this->status_) { return 0; }

	auto currentBookCirculation = this->reader_->info.GetBooksCirculation();
	if (DOUBLE_LINKED_LIST::Size(currentBookCirculation) == 0)
	{
		if (this->toolButtons_[0].IsHover())
		{
			this->toolButtons_[0].SetFillColor(rgb(57, 72, 103));
		}
		else if (this->toolButtons_[0].LeftMouseClicked())
		{
			delay(130);
			return 1;
		}
		else
		{
			this->toolButtons_[0].SetTextColor(rgb(241, 246, 249));
			this->toolButtons_[0].SetFillColor(rgb(155, 164, 181));
			this->toolButtons_[0].SetBorderColor(rgb(155, 164, 181));
		}
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			if (this->toolButtons_[i].IsHover())
			{
				this->toolButtons_[i].SetFillColor(rgb(57, 72, 103));
			}
			else if (this->toolButtons_[i].LeftMouseClicked())
			{
				delay(130);
				return i + 1;
			}
			else
			{
				this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
				this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
				this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
			}
		}
	}

	return 0;
}

BookCirculationView::BookCirculationView()
{
	this->Initialize();
}

void BookCirculationView::SetPackage(Package* package)
{
	this->package_ = package;

	this->tablePackage_.SetPackage(this->package_);

	this->tools_.SetPackage(this->package_);
}

void BookCirculationView::SetReader(AVL_TREE::Pointer readerPointer)
{
	this->readerPointer_ = readerPointer;

	this->InitializeFilter();

	this->InitializeTable();

	this->InitializeSearchBox();

	this->tools_.Reset();

	this->tools_.SetReader(readerPointer);
}

int BookCirculationView::Run()
{
	if (!this->status_) { return 0; }

	if (this->tablePackage_.InActive())
	{
		if (this->tablePackage_.Run())
		{
			std::string titleISBN = this->tableSelectedObject_.GetObjectPointer()->info.GetID().substr(0, 4);
			auto titlePointer = (*this->package_->titleMap)[titleISBN];
			if (titlePointer == nullptr)
			{
				throw std::logic_error("[ERROR] Title's pointer is NULL! (BookCirculationView::Run)");
			}
			this->tableSelectedObject_.AccessIndicator().SetPlaceholder(titlePointer->GetTitle());
			this->targetBook_.SetPlaceholder(this->tableSelectedObject_.GetObjectPointer()->info.GetID());
		}
	}

	if (this->searchBox_.InActive())
	{
		this->searchBox_.Run();
	}

	if (this->tableSelectedObject_.InActive())
	{
		if (this->tableSelectedObject_.Run())
		{
			std::string titleISBN = this->tableSelectedObject_.GetObjectPointer()->info.GetID().substr(0, 4);
			auto titlePointer = (*this->package_->titleMap)[titleISBN];
			if (titlePointer == nullptr)
			{
				throw std::logic_error("[ERROR] Title's pointer is NULL! (BookCirculationView::Run)");
			}
			this->tableSelectedObject_.AccessIndicator().SetPlaceholder(titlePointer->GetTitle());
			this->targetBook_.SetPlaceholder(this->tableSelectedObject_.GetObjectPointer()->info.GetID());
		}
	}

	if (this->tools_.InActive())
	{
		this->background_.Draw();

		this->targetBook_.Display();

		this->TargetBookOnAction();

		int toolSignal = this->tools_.Run();
		switch (toolSignal)
		{
			case (1): {
				std::cerr << "---\n";
				this->BorrowBookProcess();
				break;
			}
			case (2): {
				std::cerr << "---\n";
				this->ReturnBookProcess();
				break;
			}
			case (3): {
				std::cerr << "---\n";
				this->LostBookProcess();
				break;
			}
		}
	}

	return 0;
}

void BookCirculationView::Initialize()
{
	this->tablePackage_.Activate();

	this->tableSelectedObject_.Activate();
	this->tableSelectedObject_.AccessIndicator().SetTopLeft({1176, 945});
	this->tableSelectedObject_.AccessIndicator().SetDimension({ 520, 40 });
	this->tableSelectedObject_.AccessIndicator().UpdateWithNewTopLeft();

	this->tools_.Activate();

	this->background_.topLeft = {1030, 380};
	this->background_.dimension = {140, 236};
	this->background_.bottomRight = {1030 + 140, 380 + 236};
	this->background_.fillColor = rgb(238, 238, 238);
	this->background_.borderColor = rgb(238, 238, 238);

	this->targetBook_.SetPlaceholder("Book's ID");
	this->targetBook_.SetTextColor(BLACK);
	this->targetBook_.SetFillColor(WHITE);
	this->targetBook_.SetBorderColor(BLACK);
}

void BookCirculationView::InitializeFilter()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeFilter)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeFilter)\n");
	}

	if (this->readerPointer_ == nullptr)
	{
		std::cerr << "[ERROR] Reader's pointer is NULL! (BookCirculationView::InitializeFilter)\n";

		throw std::logic_error("[ERROR] Reader's pointer is NULL! (BookCirculationView::InitializeFilter)\n");
	}

	int readerListSize = DOUBLE_LINKED_LIST::Size(this->readerPointer_->info.GetBooksCirculation());

	this->dataFilter_.filterSize_ = readerListSize;
	this->dataFilter_.keep_ = readerListSize;
	this->dataFilter_.filters_ = new bool[readerListSize];
	for (int i = 0; i < readerListSize; ++i)
	{
		this->dataFilter_.filters_[i] = true;
	}
	std::cerr << "[LOG] Created book circulation list's filters!\n";
}

void BookCirculationView::InitializeTable()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeTable)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeTable)\n");
	}

	std::cerr << "[LOG] Creating book circulation TABLE!\n";

	this->tablePackage_.Activate();
	this->tablePackage_.SetDataList(this->readerPointer_);
	this->tablePackage_.SetDataFilter(&this->dataFilter_);
	this->tablePackage_.SetSelectedObjectContainer(&this->tableSelectedObject_);
	this->tablePackage_.AllowCreateDatasheet();
	this->tablePackage_.CreateDatasheet();

	std::cerr << "[LOG] Created book circulation TABLE!\n";
}

void BookCirculationView::InitializeSearchBox()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeSearchBox)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (BookCirculationView::InitializeSearchBox)\n");
	}

	std::cerr << "[LOG] Creating search box!\n";

	this->searchBox_.SetPackage(this->package_);
	this->searchBox_.SetReaderDatasheetPackage(&this->tablePackage_);
	this->searchBox_.SetSearchData(this->readerPointer_);
	this->searchBox_.Activate();

	std::cerr << "[LOG] Created search box!\n";
}

void BookCirculationView::TargetBookOnAction()
{
	if (!this->status_) { return; }

	if (this->targetBook_.IsHover())
	{
		this->targetBook_.SetBorderColor(rgb(130, 170, 227));
		this->targetBook_.SetFillColor(rgb(234, 253, 252));
	}
	else if (this->targetBook_.LeftMouseClicked())
	{
		delay(130);
		this->package_->inputController->Activate(
			&this->targetBook_,
			&this->targetBook_,
			9,
			true,
			true,
			false
		);
	}
	else
	{
		this->targetBook_.SetTextColor(BLACK);
		this->targetBook_.SetFillColor(WHITE);
		this->targetBook_.SetBorderColor(BLACK);
	}
}

void BookCirculationView::BorrowBookProcess()
{
	int borrowingCount = 0;
	for (auto book = this->readerPointer_->info.GetBooksCirculation().First; book != nullptr; book = book->right)
	{
		if (book->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING)
		{
			borrowingCount += 1;
		}
	}
	if (borrowingCount == 3)
	{
		std::cerr << "[ERROR] Each reader only borrow 3 book max!\n";
		return;
	}

	std::string targetBookID = this->targetBook_.GetPlaceholder();
	std::string targetTitleISBN = targetBookID.substr(0, 4);
	auto titlePointer = (*this->package_->titleMap)[targetTitleISBN];
	if (titlePointer == nullptr)
	{
		//todo: add an noti window
		std::cerr << "[ERROR] Title is not exist!\n";
		return;
	}
	
	auto titleCatalogue = titlePointer->GetCatalogue();
	auto book = titleCatalogue;
	for (; book != nullptr; book = book->next)
	{
		if (book->info.GetID().compare(targetBookID) == 0)
		{
			break;
		}
	}
	if (book == nullptr)
	{
		std::cerr << "[ERROR] Book's ID is not exist in the title's catalogue!\n";
		return;
	}
	bool duplicatedTitle = false;
	for (auto book = this->readerPointer_->info.GetBooksCirculation().First; book != nullptr; book = book->right)
	{
		if (book->info.GetID().substr(0, 4).compare(targetTitleISBN) == 0)
		{
			duplicatedTitle = true;
			break;
		}
	}
	if (duplicatedTitle)
	{
		std::cerr << "[ERROR] Cannot borrow many book in the same title!\n";
		return;
	}

	book->info.SetStatus(BOOK::Status::UNAVAILABLE);
	titlePointer->SetCatalogue(titleCatalogue);
	HELPER::Date borrowDate;
	HELPER::Date returnDate;
	auto readerBookCirculation = this->readerPointer_->info.GetBooksCirculation();
	DOUBLE_LINKED_LIST::PushBack(readerBookCirculation, BOOK_CIRCULATION::BookCirculation(
		targetBookID,
		borrowDate,
		returnDate,
		BOOK_CIRCULATION::CirculationStatus::BORROWING
	));
	this->readerPointer_->info.SetBooksCirculation(readerBookCirculation);
	std::cerr << "[LOG] Borrow book SUCCESS!\n";

	std::cerr << "[LOG] Update book circulation table!\n";
	this->tablePackage_.SetDataList(this->readerPointer_);
	this->tablePackage_.AllowCreateDatasheet();
	this->tablePackage_.CreateDatasheet();
}

void BookCirculationView::ReturnBookProcess()
{
	if (this->tableSelectedObject_.GetObjectPointer() == nullptr || this->targetBook_.GetPlaceholder().length() == 0)
	{
		std::cerr << "[ERROR] Select a borrowing book to return!\n";
		return;
	}

	std::string targetBookID = this->targetBook_.GetPlaceholder();
	std::string targetTitleISBN = targetBookID.substr(0, 4);
	auto titlePointer = (*this->package_->titleMap)[targetTitleISBN];
	if (titlePointer == nullptr)
	{
		//todo: add an noti window
		std::cerr << "[ERROR] Title is not exist!\n";
		return;
	}

	auto titleCatalogue = titlePointer->GetCatalogue();
	for (auto book = titleCatalogue; book != nullptr; book = book->next)
	{
		if (book->info.GetID().compare(targetBookID) == 0)
		{
			book->info.SetStatus(BOOK::Status::AVAILABLE);
			break;
		}
	}
	titlePointer->SetCatalogue(titleCatalogue);

	auto readerBookCirculation = this->readerPointer_->info.GetBooksCirculation();
	for (auto circulation = readerBookCirculation.First; circulation != nullptr; circulation = circulation->right)
	{
		if (circulation->info.GetID().compare(targetBookID) == 0)
		{
			circulation->info.SetStatus(BOOK_CIRCULATION::CirculationStatus::RETURNED);
			HELPER::Date today;
			circulation->info.SetReturnDate(today);
			break;
		}
	}
	this->readerPointer_->info.SetBooksCirculation(readerBookCirculation);
	std::cerr << "[LOG] Return book SUCCESS!\n";
}

void BookCirculationView::LostBookProcess()
{
	if (this->tableSelectedObject_.GetObjectPointer() == nullptr || this->targetBook_.GetPlaceholder().length() == 0)
	{
		std::cerr << "[ERROR] Select a borrowing book to alert losted!\n";
		return;
	}

	std::string targetBookID = this->targetBook_.GetPlaceholder();
	std::string targetTitleISBN = targetBookID.substr(0, 4);
	auto titlePointer = (*this->package_->titleMap)[targetTitleISBN];
	if (titlePointer == nullptr)
	{
		//todo: add an noti window
		std::cerr << "[ERROR] Title is not exist!\n";
		return;
	}

	for (auto circulation = this->readerPointer_->info.GetBooksCirculation().First; circulation != nullptr; circulation = circulation->right)
	{
		if (circulation->info.GetID().compare(targetBookID) == 0 && (circulation->info.GetStatus() == BOOK_CIRCULATION::RETURNED || circulation->info.GetStatus() == BOOK_CIRCULATION::LOSTED))
		{
			std::cerr << "[ERROR] Impossible to alert a losted book when the book is already lost or returned!\n";

			return;
		}
	}

	auto titleCatalogue = titlePointer->GetCatalogue();
	for (auto book = titleCatalogue; book != nullptr; book = book->next)
	{
		if (book->info.GetID().compare(targetBookID) == 0)
		{
			book->info.SetStatus(BOOK::Status::UNAVAILABLE);
			break;
		}
	}
	titlePointer->SetCatalogue(titleCatalogue);

	auto readerBookCirculation = this->readerPointer_->info.GetBooksCirculation();
	for (auto circulation = readerBookCirculation.First; circulation != nullptr; circulation = circulation->right)
	{
		if (circulation->info.GetID().compare(targetBookID) == 0)
		{
			circulation->info.SetStatus(BOOK_CIRCULATION::CirculationStatus::LOSTED);
			HELPER::Date today;
			circulation->info.SetReturnDate(today);
			break;
		}
	}
	this->readerPointer_->info.SetBooksCirculation(readerBookCirculation);
	std::cerr << "[LOG] Alert losted book SUCCESS!\n";
}
