#include "SearchBox.hpp"

READER_SEARCH_BOX::SearchBox::SearchBox()
{
	this->Initialize();
}

READER_SEARCH_BOX::SearchBox::SearchBox(const SearchBox& other)
{
	if (this != &other)
	{
		this->~SearchBox();

		status_ = other.status_;
		title_ = other.title_;
		searchBox_ = other.searchBox_;
		searchData_ = other.searchData_;
		package_ = other.package_;
		readerTablePackage_ = other.readerTablePackage_;
		searchFilters_ = other.searchFilters_;
	}
}

READER_SEARCH_BOX::SearchBox& READER_SEARCH_BOX::SearchBox::operator=(const SearchBox& other)
{
	if (this == &other) { return *this; }

	this->~SearchBox();

	status_ = other.status_;
	title_ = other.title_;
	searchBox_ = other.searchBox_;
	searchData_ = other.searchData_;
	package_ = other.package_;
	readerTablePackage_ = other.readerTablePackage_;
	searchFilters_ = other.searchFilters_;
}

void READER_SEARCH_BOX::SearchBox::SetPackage(Package* package)
{
	this->package_ = package;
}

void READER_SEARCH_BOX::SearchBox::SetSearchData(AVL_TREE::Pointer* data) { this->searchData_ = data; }

void READER_SEARCH_BOX::SearchBox::SetReaderDatasheetPackage(READER_TABLE::DatasheetProcessor* datasheetPackage)
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
bool READER_SEARCH_BOX::SearchBox::SearchOperation()
{
	const std::string searchTarget = this->searchBox_.GetPlaceholder();

	if (!this->status_) { return false; }

	if (this->searchData_ == nullptr)
	{
		std::cerr << "[ERROR] Search data's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchOperation)\n";
		throw std::logic_error("[ERROR] Search data's pointer is NULL! (READER_SEARCH_BOX::SearchBox::SearchOperation)\n");

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
	int dataSetSize{ 0 };
	AVL_TREE::Size(*this->searchData_, dataSetSize);
	DataFilter*& dataFilter = this->readerTablePackage_->AccessDataFilter();
	std::string readerID{};
	std::string readerFirstName{};
	std::string readerLastName{};
	std::string readerGender{};
	std::string readerStatus{};

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
	Stack<AVL_TREE::Pointer> stk;
	AVL_TREE::Pointer currentNode = *this->searchData_;
	int index = 0;
	do {
		while (currentNode != nullptr) {
			stk.Push(currentNode);
			currentNode = currentNode->left;
		}

		if (stk.Empty() == false) {
			currentNode = stk.Pop();

			//* Logic stays here

			for (int i = 0; i < filterCount; ++i) { filterCheckers[i] = false; }

			readerID = std::to_string(currentNode->info.GetID());
			readerFirstName = currentNode->info.GetFirstName();
			readerLastName = currentNode->info.GetLastName();
			readerGender = currentNode->info.StringifyGender();
			readerStatus = currentNode->info.StringfyStatus();

			//std::cerr << "Checking in: " << readerFirstName + " " + readerLastName << "\n";

			if (readerID.find(searchTarget) != std::string::npos) { filterCheckers[0] = true; }
			if (readerFirstName.find(searchTarget) != std::string::npos) { filterCheckers[1] = true; }
			if (readerLastName.find(searchTarget) != std::string::npos) { filterCheckers[2] = true; }
			//if (readerGender.find(searchTarget) != std::string::npos) { filterCheckers[3] = true; }
			if (readerGender.compare(searchTarget) == 0) { filterCheckers[3] = true; }
			if (readerStatus.find(searchTarget) != std::string::npos) { filterCheckers[4] = true; }

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
			//---

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);


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

void READER_SEARCH_BOX::SearchBox::SearchBoxOnAction()
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

void READER_SEARCH_BOX::SearchBox::Display()
{
	if (this->status_ == false) { return; }

	this->title_.Display();
	this->searchBox_.Display();
	this->searchFilters_.Display();
}

int READER_SEARCH_BOX::SearchBox::Run()
{
	if (!this->status_) { return 0; }

	this->Display();
	this->SearchBoxOnAction();
	if (this->SearchOperation()) { return 1; }

	return 0;
}

void READER_SEARCH_BOX::SearchBox::Initialize()
{
	this->title_ = Button(HELPER::Coordinate(147, 120), 750, 70);
	this->title_.SetFillColor(rgb(33, 42, 62));
	this->title_.SetBorderColor(rgb(33, 42, 62));

	this->searchBox_ = Button(HELPER::Coordinate(152, 125), 740, 60);
	this->searchBox_.SetPlaceholder("Type here to search!");

	this->InitializeSearchFilters();
}

void READER_SEARCH_BOX::SearchBox::InitializeSearchFilters()
{
	this->searchFilters_ = SearchFilters(5);

	std::string filterPlaceholders[] = { "Reader ID", "First name", "Last name", "Gender", "Status" };
	HELPER::Coordinate filterCoordinates[] = { {933, 120}, {1057, 120}, {1181, 120}, {1305, 120}, {1429, 120} };
	bool filterDefaultValues[] = { true, true, true, false, false };
	for (int i = 0; i < 5; ++i)
	{
		this->searchFilters_[i].SetPlaceholder(filterPlaceholders[i]);
		this->searchFilters_[i].SetTopLeft(filterCoordinates[i]);
		this->searchFilters_[i].SetValue(filterDefaultValues[i]);
	}
	this->searchFilters_.Activate();
}
