#include "DanhSachDauSachView.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


namespace DAU_SACH_TAB
{
	DatasheetProcessor::DatasheetProcessor()
	{
		this->dataList_ = nullptr;
		this->dataFilter_ = nullptr;
		this->active_ = false;
		this->allowCreateDatasheet_ = false;
	}

	DatasheetProcessor::DatasheetProcessor(LINEAR_LIST::LinearList* dataList, DataFilter* dataFilter_)
	{
		this->dataList_ = dataList;
		this->dataFilter_ = dataFilter_;

		this->active_ = false;
		this->allowCreateDatasheet_ = false;

		this->datasheetController_ = {
			DATASHEET_DEFAULT_PROPERTIES::MAX_ROW,
			DAU_SACH_PROPERTIES::PROPERTIES_COUNT,
			DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
			HELPER::Coordinate(36, 210),
			HELPER::Coordinate(36, 950)
		};
	}

	void DatasheetProcessor::SetSelectedObjectContainer(SelectedObject<BOOK_TITLE::BookTitle*>* datasheetSelectedObject)
	{
		this->datasheetSelectedObject_ = datasheetSelectedObject;
	}

	void DatasheetProcessor::AllowCreateDatasheet() { this->allowCreateDatasheet_ = true; }

	void DatasheetProcessor::CreateDatasheet()
	{
		//* Filtering out all cases where cannot create datasheet
		if (!this->active_) { return; }

		if (!this->allowCreateDatasheet_) { return; }

		if (this->dataFilter_->filters_ == nullptr) { return; }

		//* Creating datasheet
		int listSize = this->dataFilter_->keep_;
		this->datasheetController_.SetDatasheetCount(
			max(1, (listSize / (DATASHEET_DEFAULT_PROPERTIES::MAX_ROW - 1) + (listSize % (DATASHEET_DEFAULT_PROPERTIES::MAX_ROW - 1) == 0 ? 0 : 1)))
		);
		this->datasheetController_.InitializeDatasheets();

		for (int i = 0; i < this->datasheetController_.GetDatasheetCount(); ++i)
		{
			this->datasheetController_[i] = {
				this->datasheetController_.GetRecordCount(),
				this->datasheetController_.GetAttributeCount(),
				this->datasheetController_.GetRowHeight(),
				this->datasheetController_.GetTopLeft(),
				(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS,
				(int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
			};
		}

		int recordIndex = 0;
		int sheetIndex = -1;
		int order = 0;

		for (int i = 0; i < this->dataFilter_->filterSize_; ++i)
		{
			if (this->dataFilter_->filters_[i] == true)
			{
				++recordIndex;
				if (recordIndex > this->datasheetController_.GetRecordCount() - 1) {
					recordIndex = 1;
				}
				if (recordIndex % (this->datasheetController_.GetRecordCount() - 1) == 1) {
					sheetIndex += 1;
				}

				std::string* data = new std::string[this->datasheetController_.GetAttributeCount()];
				data[0] = std::to_string(++order);
				data[1] = this->dataList_->nodes[i]->GetISBN();
				data[2] = this->dataList_->nodes[i]->GetTitle();
				data[3] = std::to_string(this->dataList_->nodes[i]->GetPageCount());
				data[4] = this->dataList_->nodes[i]->GetAuthor();
				data[5] = std::to_string(this->dataList_->nodes[i]->GetPublicationYear());
				data[6] = this->dataList_->nodes[i]->GetCategory();

				this->datasheetController_[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
			}
		}
		this->datasheetController_.ActivateDatasheets();

		//* Completed creating datasheet
		this->allowCreateDatasheet_ = false;
	}

	void DatasheetProcessor::SetDataFilter(DataFilter* dataFilter) { this->dataFilter_ = dataFilter; }

	DataFilter* DatasheetProcessor::GetDataFilter() { return this->dataFilter_; }

	void DatasheetProcessor::SetDataList(LINEAR_LIST::LinearList* dataList)
	{
		this->dataList_ = dataList;
	}

	LINEAR_LIST::LinearList* DatasheetProcessor::GetDataList()
	{
		return this->dataList_;
	}

	DataFilter*& DatasheetProcessor::AccessDataFilter() { return this->dataFilter_; }

	DATASHEET::Datasheet& DatasheetProcessor::AccessCurrentDatasheet()
	{
		return this->datasheetController_[this->datasheetController_.CurrentActiveDatasheet()];
	}

	void DatasheetProcessor::Display()
	{
		if (!this->active_) { return; }

		this->datasheetController_.Display();
		this->datasheetController_.DatasheetChangeButtonUpdate();
	}

	void DatasheetProcessor::Activate() { this->active_ = true; }

	void DatasheetProcessor::Deactivate() { this->active_ = false; }

	bool DatasheetProcessor::InActive() { return this->active_; }

	int DatasheetProcessor::Run()
	{
		if (!this->active_) { return 0; }

		this->Display();
		if (this->DatasheetOnAction() == 1) { return 1; }
		
		return 0;
	}

	int DatasheetProcessor::DatasheetOnAction()
	{
		if (!this->active_) { return 0; }

		int currentDatasheetIndex = this->datasheetController_.CurrentActiveDatasheet();
		int datasheetColumnCount = this->datasheetController_.GetAttributeCount();
		int datasheetRowCount = this->datasheetController_.GetRecordCount();

		for (int rowIndex = 1; rowIndex < datasheetRowCount; ++rowIndex)
		{
			for (int columnIndex = 0; columnIndex < datasheetColumnCount; ++columnIndex)
			{
				Button& currentCell = this->datasheetController_[currentDatasheetIndex][rowIndex][columnIndex];

				if (currentCell.GetPlaceholder().compare("...") == 0) { continue; }

				if (currentCell.IsHover())
				{
					currentCell.SetFillColor(rgb(221, 230, 237));
				}
				else if (currentCell.LeftMouseClicked())
				{
					delay(100);

					BOOK_TITLE::BookTitle* selectedObject = this->dataList_->nodes[(datasheetRowCount - 1) * currentDatasheetIndex + rowIndex - 1];
					this->datasheetSelectedObject_->SetObjectPointer(selectedObject);
				}
				else if (currentCell.RightMouseClicked())
				{
					delay(100);

					BOOK_TITLE::BookTitle* selectedObject = this->dataList_->nodes[(datasheetRowCount - 1) * currentDatasheetIndex + rowIndex - 1];
					this->datasheetSelectedObject_->SetObjectPointer(selectedObject);

					return 1;
				}
				else
				{
					if (rowIndex % 2 == 0) { currentCell.SetFillColor(rgb(238, 238, 238)); }
					else { currentCell.SetFillColor(rgb(255, 251, 245)); }
				}
			}
		}

		return 0;
	}

	SearchSection::SearchSection()
	{
		this->data_ = nullptr;
		this->package_ = nullptr;
		this->titleDatasheetPackage_ = nullptr;
		this->active_ = false;
	}

	SearchSection::SearchSection(Package* package, DAU_SACH_TAB::DatasheetProcessor* titleDatasheetPackage)
	{
		this->package_ = package;
		this->titleDatasheetPackage_ = titleDatasheetPackage;
		this->active_ = false;

		this->Initialize();
	}

	void SearchSection::SetSearchData(LINEAR_LIST::LinearList* data) { this->data_ = data; }

	void SearchSection::Activate() { this->active_ = true; }

	void SearchSection::Deactivate() { this->active_ = false; }

	bool SearchSection::GetStatus() { return this->active_; }

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
	bool SearchSection::SearchOperation()
	{
		const std::string searchTarget = this->searchBox_.GetPlaceholder();

		if (!this->active_) { return false; }

		if (this->data_ == nullptr || this->data_->numberOfNode == 0) { return false; }

		if (searchTarget.compare("Type here to search!") == 0)
		{
			DataFilter*& dataFilter = this->titleDatasheetPackage_->AccessDataFilter();
			dataFilter->keep_ = dataFilter->filterSize_;
			for (int i = 0; i < dataFilter->filterSize_; ++i) { dataFilter->filters_[i] = true; }

			return false;
		}

		//* Initialize necessary variables
		int dataSetSize = this->data_->numberOfNode;
		DataFilter*& dataFilter = this->titleDatasheetPackage_->AccessDataFilter();
		std::string titleISBN{};
		std::string titleName{};
		std::string titleCategory{};
		std::string titleAuthor{};
		std::string titlePublication{};

		//* Initialize filter's checkers
		int filterCount = this->searchFilters_.Size();
		bool* filterCheckers = new bool[filterCount];
		for (int i = 0; i < filterCount; ++i) { filterCheckers[i] = false; }

		//* (1) Create a temperary version of the current filter!
		DataFilter orignalFilter;
		orignalFilter.filterSize_ = dataFilter->filterSize_;
		orignalFilter.keep_ = dataFilter->keep_;
		orignalFilter.filters_ = new bool[orignalFilter.filterSize_];
		for (int i = 0; i < orignalFilter.filterSize_; ++i) { orignalFilter.filters_[i] = dataFilter->filters_[i]; }

		//* (2) Search and update filter.
		for (int i = 0; i < dataSetSize; ++i)
		{
			for (int i = 0; i < filterCount; ++i) { filterCheckers[i] = false; }
			titleName = this->data_->nodes[i]->GetTitle();
			titleISBN = this->data_->nodes[i]->GetISBN();
			titleCategory = this->data_->nodes[i]->GetCategory();
			titleAuthor = this->data_->nodes[i]->GetAuthor();
			titlePublication = std::to_string(this->data_->nodes[i]->GetPublicationYear());

			if (titleName.find(searchTarget) != std::string::npos) { filterCheckers[0] = true; }
			if (titleISBN.find(searchTarget) != std::string::npos) { filterCheckers[1] = true; }
			if (titleCategory.find(searchTarget) != std::string::npos) { filterCheckers[2] = true; }
			if (titleAuthor.find(searchTarget) != std::string::npos) { filterCheckers[3] = true; }
			if (titlePublication.find(searchTarget) != std::string::npos) { filterCheckers[4] = true; }

			bool res = false;
			for (int i = 0; i < 5; ++i)
			{
				res = res || (filterCheckers[i] * this->searchFilters_.FilterValue(i));
			}

			//* Only update filter if there are any changes
			//if (existSubstringInISBN || existSubstringInTitle)
			if (res)
			{
				// The current filter is already correct, therefore we don't need to update the filter
				if (dataFilter->filters_[i]) { continue; }

				// Update filter
				if (dataFilter->keep_ < dataFilter->filterSize_) { dataFilter->keep_ += 1; }
				dataFilter->filters_[i] = true;
			}
			else
			{
				// The current filter is already correct, therefore we don't need to update the filter
				if (!dataFilter->filters_[i]) { continue; }

				// Update filter
				if (dataFilter->keep_ > 0) { dataFilter->keep_ -= 1; }
				dataFilter->filters_[i] = false;
			}
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

		return existChanges;
	}

	void SearchSection::SearchBoxOnAction()
	{
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
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::SearchBoxStyling(&this->searchBox_);
		}
	}

	void SearchSection::Display()
	{
		if (this->active_ == false) { return; }

		this->title_.Display();
		this->searchBox_.Display();
		this->searchFilters_.Display();
	}

	bool SearchSection::Run()
	{
		this->Display();
		this->SearchBoxOnAction();
		return this->SearchOperation();
	}

	void SearchSection::Initialize()
	{
		this->title_ = Button(HELPER::Coordinate(36, 120), 750, 70);
		this->title_.SetFillColor(rgb(33, 42, 62));
		this->title_.SetBorderColor(rgb(33, 42, 62));

		this->searchBox_ = Button(HELPER::Coordinate(41, 125), 740, 60);
		this->searchBox_.SetPlaceholder("Type here to search!");

		this->InitializeSearchFilters();
	}

	void SearchSection::InitializeSearchFilters()
	{
		this->searchFilters_ = SearchFilters(5);

		std::string filterPlaceholders[] = { "Title", "ISBN", "Category", "Author", "Publication" };
		HELPER::Coordinate filterCoordinates[] = { {822, 120}, {946, 120}, {1070, 120}, {1194, 120}, {1318, 120} };
		bool filterDefaultValues[] = { true, true, true, false, false };
		for (int i = 0; i < 5; ++i)
		{
			this->searchFilters_[i].SetPlaceholder(filterPlaceholders[i]);
			this->searchFilters_[i].SetTopLeft(filterCoordinates[i]);
			this->searchFilters_[i].SetValue(filterDefaultValues[i]);
		}
		this->searchFilters_.Activate();
	}

	BookCreatingSection::BookCreatingSection()
	{
		this->active_ = false;

		this->InitializeElements();
	}

	void BookCreatingSection::Activate() { this->active_ = true; }

	void BookCreatingSection::Deactivate() { this->active_ = false; }

	bool BookCreatingSection::GetStatus() { return this->active_; }

	void BookCreatingSection::Display()
	{
		if (!this->active_) { return; }

		this->background_.Draw();
		for (int i = 0; i < 5; ++i)
		{
			this->inputField_[i].Display();
		}
		this->saveButton_.Display();
	}

	void BookCreatingSection::InitializeElements()
	{
		this->background_ = HELPER::Fill(
			HELPER::Coordinate(36, 616),
			600, 180,
			rgb(238, 238, 238),
			rgb(24, 18, 43)
		);

		HELPER::Coordinate inputFieldCoordinates[5] = {
			HELPER::Coordinate(61, 646),
			HELPER::Coordinate(398, 646),
			HELPER::Coordinate(61, 717),
			HELPER::Coordinate(229, 717),
			HELPER::Coordinate(398, 717)
		};
		std::string inputFiledPlaceholders[5] = { "Book's ID", "Book's status", "Row", "Column", "Section" };
		HELPER::Dimension inputFieldDimension[] = {
			HELPER::Dimension(308, 50),
			HELPER::Dimension(215, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50)
		};

		for (int i = 0; i < 5; ++i)
		{
			this->inputField_[i] = Button(inputFieldCoordinates[i], inputFieldDimension[i]);
			this->inputField_[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField_[i].SetFillColor(rgb(255, 251, 245));
			this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField_[i].SetTextColor(rgb(24, 18, 43));
		}

		this->saveButton_ = Button(
			HELPER::Coordinate(561, 717),
			50, 50,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->saveButton_.SetPlaceholder(">");
	}

	CatalogueCreatingSection::CatalogueCreatingSection()
	{
		this->titleList_ = nullptr;
		this->inputController_ = nullptr;

		this->active = false;
		this->items = nullptr;
		this->itemsCount = 0;
		this->activeField = -1;
	}

	CatalogueCreatingSection::CatalogueCreatingSection(LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController)
	{
		this->titleList_ = titleList;
		this->inputController_ = inputController;

		this->active = false;
		this->items = nullptr;
		this->itemsCount = 0;
		this->activeField = -1;

		this->InitializeElements();
	}

	// @CatalogueCreatingSection::Destructor
	CatalogueCreatingSection::~CatalogueCreatingSection()
	{
		delete[this->itemsCount] this->items;
	}

	void CatalogueCreatingSection::InitializeCatalogue(int catalogueSize, std::string ISBN)
	{
		this->itemsCount = catalogueSize;
		this->items = new DAU_SACH_TAB::BookCreatingSection[catalogueSize];
		this->activeField = 0;

		for (int i = 1; i <= catalogueSize; ++i)
		{
			this->items[i - 1].inputField_[0].SetPlaceholder(ISBN + "-" + std::to_string(i));
			this->items[i - 1].inputField_[1].SetPlaceholder("AVAILABLE");
		}
	}

	void CatalogueCreatingSection::InputFieldOnUpdate()
	{
		if (!this->active) { return; }

		for (int i = 2; i < 5; ++i)
		{
			if (this->items[this->activeField].inputField_[i].IsHover())
			{
				this->items[this->activeField].inputField_[i].SetFillColor(rgb(233, 248, 249));
				this->items[this->activeField].inputField_[i].SetBorderColor(rgb(83, 127, 231));
			}
			else if (this->items[this->activeField].inputField_[i].LeftMouseClicked())
			{
				//!DELAY_SECTION
				delay(150);
				this->inputController_->Activate(
					&this->items[this->activeField].inputField_[i],
					&this->items[this->activeField].inputField_[i],
					2,
					false,
					true,
					false
				);
			}
			else
			{
				this->items[this->activeField].inputField_[i].SetFillColor(rgb(255, 251, 245));
				this->items[this->activeField].inputField_[i].SetBorderColor(rgb(24, 18, 43));
			}
		}
	}

	void CatalogueCreatingSection::SaveButtonOnUpdate()
	{
		if (!this->active) { return; }

		if (this->items[this->activeField].saveButton_.IsHover())
		{
			this->items[this->activeField].saveButton_.SetFillColor(rgb(0, 255, 202));
		}
		else if (this->items[this->activeField].saveButton_.LeftMouseClicked())
		{
			//!DELAY_SECTION
			delay(150);
			if (this->activeField == this->itemsCount - 1)
			{
				this->activeField = 0;

				//TODO: Throw error log here
				//std::cerr << std::format("[INFO] Press Save to save data into the list!\n");
			}
			else
			{
				this->activeField++;
			}
		}
		else
		{
			this->items[this->activeField].saveButton_.SetFillColor(rgb(145, 216, 228));
		}
	}

	void CatalogueCreatingSection::IndexChangeButtonOnAction()
	{
		if (!this->active) { return; }

		int movement[2] = { -1, +1 };
		for (int i = 0; i < 2; ++i)
		{
			if (this->indexChangeButtons[i].IsHover())
			{
				this->indexChangeButtons[i].SetFillColor(rgb(130, 170, 227));
			}
			else if (this->indexChangeButtons[i].LeftMouseClicked())
			{
				//!DELAY_SECTION
				delay(150);
				this->activeField = (this->activeField + movement[i] + this->itemsCount) % this->itemsCount;
			}
			else
			{
				this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			}
		}
	}

	void CatalogueCreatingSection::Activate() { this->active = true; }

	void CatalogueCreatingSection::Deactivate() { this->active = false; }

	bool CatalogueCreatingSection::GetStatus() { return this->active; }

	void CatalogueCreatingSection::Display()
	{
		if (!this->active) { return; }

		this->items[this->activeField].Activate();
		this->items[this->activeField].Display();

		for (int i = 0; i < 2; ++i)
		{
			this->indexChangeButtons[i].Display();
		}
	}

	void CatalogueCreatingSection::InitializeElements()
	{
		HELPER::Coordinate buttonCoordinates[] = {
			HELPER::Coordinate(36, 811),
			HELPER::Coordinate(86, 811)
		};
		std::string placeholder[] = { "<", ">" };

		for (int i = 0; i < 2; ++i)
		{
			this->indexChangeButtons[i] = Button(buttonCoordinates[i], 50, 30);
			this->indexChangeButtons[i].SetPlaceholder(placeholder[i]);
			this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			this->indexChangeButtons[i].SetBorderColor(rgb(24, 18, 43));
			this->indexChangeButtons[i].SetTextColor(rgb(24, 18, 43));
		}
	}

	TitleCreatingSection::TitleCreatingSection()
	{
		this->package_ = nullptr;
		this->active = false;
		this->sachAddFieldDisplay = false;
	}

	TitleCreatingSection::TitleCreatingSection(Package* package)
	{
		this->package_ = package;

		this->active = false;
		this->sachAddFieldDisplay = false;

		this->InitializeElements();
	}

	bool TitleCreatingSection::InputFieldOnUpdate()
	{
		if (this->active == false) { return false; }

		int characterLimits[] = { 4, 50, 30, 20, 4, 4, 5 };
		bool acceptAlphas[] = { true, true, true, true, false, false, false };
		bool acceptNums[] = { false, true, true, true, true, true, true };
		bool acceptSpaces[] = { false, true, true, true, false, false, false };

		for (int i = 0; i < 7; ++i)
		{
			if (this->inputField_[i].IsHover())
			{
				this->inputField_[i].SetBorderColor(rgb(83, 127, 231));
				this->inputField_[i].SetFillColor(rgb(233, 248, 249));
			}
			else if (this->inputField_[i].LeftMouseClicked())
			{
				delay(100);
				this->package_->inputController->Activate(
					&this->inputField_[i],
					&this->inputField_[i],
					characterLimits[i],
					acceptAlphas[i],
					acceptNums[i],
					acceptSpaces[i]
				);
			}
			else
			{
				this->inputField_[i].SetFillColor(rgb(255, 251, 245));
				this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			}
		}

		std::string defaultInputValues[7] = {
			" ISBN ", " Title ", " Author ", " Category ", " Page number ", " Public year ", " Catalogue's size "
		};
		bool userInputed = true;
		std::string userInputValue{};
		for (int i = 0; i < 7; ++i)
		{
			userInputValue = this->inputField_[i].GetPlaceholder();
			if (userInputValue.compare(defaultInputValues[i]) == 0 || userInputValue.length() == 0)
			{
				userInputed = false;
				break;
			}
		}

		this->ISBNCheckProcessResult_ = this->ISBNInputFieldCheckProcess();

		this->catalogueSizeProcessResult_ = this->CatalogueSizeCheckProcess();

		if (this->ISBNCheckProcessResult_ && this->catalogueSizeProcessResult_ && userInputed)
		{
			this->goodInputFieldCheckResult_ = true;
			return true;
		}

		this->goodInputFieldCheckResult_ = false;
		return false;
	}

	bool TitleCreatingSection::CreateCatalogueButtonOnUpdate()
	{
		if (this->active == false) { return false; }

		if (!this->goodInputFieldCheckResult_) { return false; }

		this->alertField_[1].SetTextColor(rgb(104, 185, 132));
		this->alertField_[1].SetPlaceholder("Press the [V] button to create title's catalogue!");

		if (this->createCatalogueButton_.IsHover())
		{
			this->createCatalogueButton_.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->createCatalogueButton_.LeftMouseClicked())
		{
			delay(100);

			const std::string& catalogueSize = this->inputField_[6].GetPlaceholder();
			const std::string& titleISBN = this->inputField_[0].GetPlaceholder();
			this->catalogueCreatingSection = DAU_SACH_TAB::CatalogueCreatingSection(this->package_->titleList, this->package_->inputController);
			this->catalogueCreatingSection.Activate();
			this->catalogueCreatingSection.InitializeCatalogue(std::stoi(catalogueSize), titleISBN);

			return true;
		}
		else
		{
			this->createCatalogueButton_.SetFillColor(rgb(145, 216, 228));
		}

		return false;
	}

	bool TitleCreatingSection::SubmitButtonOnUpdate()
	{
		if (this->active == false) { return false; }

		if (!this->allowCreatingNewTitle_) { return false; }

		if (this->submit.IsHover())
		{
			this->submit.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->submit.LeftMouseClicked())
		{
			delay(100);

			BOOK_TITLE::BookTitle* newTitle = new BOOK_TITLE::BookTitle;

			newTitle->SetISBN(this->inputField_[0].GetPlaceholder());
			newTitle->SetTitle(this->inputField_[1].GetPlaceholder());
			newTitle->SetAuthor(this->inputField_[2].GetPlaceholder());
			newTitle->SetCategory(this->inputField_[3].GetPlaceholder());
			newTitle->SetPublicationYear(std::stoi(this->inputField_[4].GetPlaceholder()));
			newTitle->SetPageCount(std::stoi(this->inputField_[5].GetPlaceholder()));

			if (std::stoi(this->inputField_[6].GetPlaceholder()) == 0)
			{
				newTitle->SetCatalogue(nullptr);
			}
			else
			{
				LINKED_LIST::Pointer newBookList = nullptr;
				LINKED_LIST::Initialize(newBookList);

				for (int i = 0; i < this->catalogueCreatingSection.itemsCount; ++i)
				{
					BOOK::Book newBook;
					newBook.SetID(this->catalogueCreatingSection.items[i].inputField_[0].GetPlaceholder());
					newBook.SetStatus(BOOK::Status::AVAILABLE);
					newBook.SetDescription(std::format("ROW {} COLUMN {} SECTION {}",
						this->catalogueCreatingSection.items[i].inputField_[2].GetPlaceholder(),
						this->catalogueCreatingSection.items[i].inputField_[3].GetPlaceholder(),
						this->catalogueCreatingSection.items[i].inputField_[4].GetPlaceholder()
					));

					LINKED_LIST::PushBack(newBookList, newBook);
				}

				newTitle->SetCatalogue(newBookList);
			}

			LINEAR_LIST::InsertOrder(*this->package_->titleList, newTitle);

			//TODO: Add a notification window here
			std::cerr << "[INFO] Successfully insert a new item into title list!\n";

			this->alertField_[1].SetTextColor(rgb(104, 185, 132));
			this->alertField_[1].SetPlaceholder("New title has created successfully!");

			int defaultWindowID = getcurrentwindow();

			ELEMENTS::Window notificationWindow(HELPER::Dimension(500, 150), "NOTIFICATION");
			notificationWindow.backgroundColor = WHITE;
			int notificationWindowID = notificationWindow.Activate();
			notificationWindow.RenderBackground();

			Button notification(HELPER::Coordinate(100, 70), HELPER::Dimension(100, 70));
			notification.SetTextColor(rgb(104, 185, 132));
			notification.SetBorderColor(WHITE);
			notification.SetFillColor(WHITE);
			notification.SetPlaceholder("SUCCESSFULLY CREATED A NEW TITLE!");
			notification.Display();

			getch();

			notificationWindow.Deactivate();

			setcurrentwindow(defaultWindowID);

			return true;
		}
		else
		{
			this->submit.SetFillColor(rgb(145, 216, 228));
		}


		return false;
	}

	bool TitleCreatingSection::Run()
	{
		bool goodTitleData = this->InputFieldOnUpdate();
		bool allowCreateCatalogue = this->CreateCatalogueButtonOnUpdate();
		bool goodCatalogueData = this->CatalogueInputFieldCheckProcess();
		bool newTittleCreated = this->SubmitButtonOnUpdate();

		if (goodTitleData && allowCreateCatalogue && goodCatalogueData && newTittleCreated) { return true; }

		return false;
	}

	void TitleCreatingSection::Activate() { this->active = true; }

	void TitleCreatingSection::Deactivate() { this->active = false; }

	bool TitleCreatingSection::GetStatus() { return this->active; }

	void TitleCreatingSection::Display()
	{
		if (this->active == false) { return; }

		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 7; ++i)
		{
			this->inputField_[i].Display();
		}
		this->createCatalogueButton_.Display();

		for (int i = 0; i < 2; ++i) { this->alertField_[i].Display(); }

		if (this->catalogueCreatingSection.GetStatus() == true)
		{
			this->catalogueCreatingSection.Display();
			this->catalogueCreatingSection.IndexChangeButtonOnAction();
			this->catalogueCreatingSection.InputFieldOnUpdate();
			this->catalogueCreatingSection.SaveButtonOnUpdate();
		}

		if (this->allowCreatingNewTitle_)
		{
			this->submit.Display();
		}
		this->goBackButton.Display();
	}

	void TitleCreatingSection::InitializeElements()
	{
		this->background = HELPER::Fill(
			HELPER::Coordinate(36, 121),
			600, 480,
			rgb(238, 238, 238),
			rgb(24, 18, 43)
		);

		this->title = Button(HELPER::Coordinate(36, 121), 600, 50);
		this->title.SetPlaceholder("CREATING NEW TITLE");
		this->title.SetFillColor(rgb(87, 108, 188));
		this->title.SetBorderColor(rgb(24, 18, 43));
		this->title.SetTextColor(rgb(239, 245, 245));

		HELPER::Coordinate inputFieldCoordinates[7] = {
			HELPER::Coordinate(61, 196),
			HELPER::Coordinate(61, 267),
			HELPER::Coordinate(61, 338),
			HELPER::Coordinate(61, 409),
			HELPER::Coordinate(61, 480),
			HELPER::Coordinate(229, 480),
			HELPER::Coordinate(398, 480)
		};
		HELPER::Dimension inputFieldDimensions[7] = {
			HELPER::Dimension(200, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50)
		};
		std::string inputFiledPlaceholders[7] = {
			" ISBN ", " Title ", " Author ", " Category ", " Page number ", " Public year ", " Catalogue's size "
		};
		for (int i = 0; i < 7; ++i)
		{
			this->inputField_[i] = Button(inputFieldCoordinates[i], inputFieldDimensions[i]);
			this->inputField_[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField_[i].SetFillColor(rgb(255, 251, 245));
			this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField_[i].SetTextColor(rgb(24, 18, 43));
		}

		this->createCatalogueButton_ = Button(
			HELPER::Coordinate(561, 480),
			50, 50,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->createCatalogueButton_.SetPlaceholder("V");

		this->submit = Button(
			HELPER::Coordinate(211, 861),
			250, 60,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->submit.SetPlaceholder("CREATE NEW TITLE");

		HELPER::Coordinate alertFieldCoordinates[] = {
			HELPER::Coordinate(273, 201),
			HELPER::Coordinate(61, 551)
		};
		HELPER::Dimension alertFieldDimensions[] = {
			HELPER::Dimension(338, 40),
			HELPER::Dimension(550, 40)
		};
		for (int i = 0; i < 2; ++i)
		{
			this->alertField_[i] = Button(alertFieldCoordinates[i], alertFieldDimensions[i]);
			this->alertField_[i].SetFillColor(rgb(238, 238, 238));
			this->alertField_[i].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[i].SetTextColor(rgb(120, 122, 145));
		}
		this->alertField_[0].SetPlaceholder("Input a unique ISBN code for the new title!");
		this->alertField_[1].SetPlaceholder("Fill out all input field then press [V] to create catalogue!");

		this->goBackButton = Button(
			HELPER::Coordinate(36, 937),
			70, 40,
			rgb(24, 18, 43),
			rgb(236, 242, 255),
			rgb(24, 18, 43)
		);
		this->goBackButton.SetPlaceholder("<");
	}

	bool TitleCreatingSection::CatalogueSizeCheckProcess()
	{
		std::string catalogueSizeStringValue = this->inputField_[6].GetPlaceholder();
		if (catalogueSizeStringValue.length() == 0)
		{
			this->alertField_[1].SetFillColor(rgb(238, 238, 238));
			this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[1].SetTextColor(rgb(120, 122, 145));
			this->alertField_[1].SetPlaceholder("Don't let the catalogue's size input field empty!");

			return false;
		}

		if (VALIDATOR::OnlyDigit(catalogueSizeStringValue))
		{
			int catalogueSize = std::stoi(catalogueSizeStringValue);

			return true;
		}

		this->alertField_[1].SetFillColor(rgb(238, 238, 238));
		this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
		this->alertField_[1].SetTextColor(rgb(120, 122, 145));
		this->alertField_[1].SetPlaceholder("Fill out all input field then press [V] to create catalogue!");

		return false;
	}

	bool TitleCreatingSection::GoBackButtonOnAction()
	{
		if (this->active == false) { return false; }

		if (this->goBackButton.IsHover())
		{
			this->goBackButton.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackButton.LeftMouseClicked())
		{
			delay(100);
			this->active = false;
			this->catalogueCreatingSection.Deactivate();
			return true;
		}
		else
		{
			this->goBackButton.SetFillColor(rgb(236, 242, 255));
		}
		return false;
	}

	bool TitleCreatingSection::ISBNInputFieldCheckProcess()
	{
		if (!this->active) { return false; }

		std::string inputISBN = this->inputField_[0].GetPlaceholder();
		if (inputISBN.length() == 4) // ISBN Input value at input field of index 0
		{
			if (this->package_->titleMap->At(inputISBN) != nullptr)
			{
				this->alertField_[0].SetTextColor(rgb(231, 70, 70));
				this->alertField_[0].SetBorderColor(rgb(231, 70, 70));
				this->alertField_[0].SetPlaceholder("DUPLICATED ISBN!");

				return false;
			}
			else
			{
				this->alertField_[0].SetFillColor(rgb(95, 208, 104));
				this->alertField_[0].SetTextColor(WHITE);
				this->alertField_[0].SetBorderColor(rgb(95, 208, 104));
				this->alertField_[0].SetPlaceholder("QUALIFIED ISBN!");

				return true;
			}
		}
		else if (inputISBN.length() != 4)
		{
			this->alertField_[0].SetFillColor(rgb(238, 238, 238));
			this->alertField_[0].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[0].SetTextColor(rgb(120, 122, 145));
			this->alertField_[0].SetPlaceholder("Input a unique ISBN code for the new title!");

			return false;
		}

		return false;
	}

	bool TitleCreatingSection::CatalogueInputFieldCheckProcess()
	{
		if (!this->active) { return false; }

		if (!this->catalogueSizeProcessResult_) { return false; }

		if (this->catalogueCreatingSection.itemsCount == 0) { return false; }

		std::string defaultValues[] = { "Row", "Column", "Section" };

		for (int i = 0; i < this->catalogueCreatingSection.itemsCount; ++i)
		{
			bool allFilled = true;
			for (int j = 2; j < 5; ++j)
			{
				if (this->catalogueCreatingSection.items[i].inputField_[j].GetPlaceholder().length() == 0 ||
					this->catalogueCreatingSection.items[i].inputField_[j].GetPlaceholder().compare(defaultValues[j - 2]) == 0)
				{
					allFilled = false;
					break;
				}
			}

			if (!allFilled)
			{
				this->alertField_[1].SetFillColor(rgb(238, 238, 238));
				this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
				this->alertField_[1].SetTextColor(rgb(120, 122, 145));
				this->alertField_[1].SetPlaceholder("Fill out all input field of title's catalogue then press CREATE button!");

				this->allowCreatingNewTitle_ = false;

				return false;
			}
		}

		this->alertField_[1].SetTextColor(rgb(104, 185, 132));
		this->alertField_[1].SetPlaceholder("Press CREATE button to create new title!");

		this->allowCreatingNewTitle_ = true;

		return true;
	}
}

namespace CATEGORY_LINKED_LIST {
	Node::Node(std::string info, Node* next) {
		this->info = info;
		this->next = next;
	}

	void Initialzie(Pointer& First) {
		First = nullptr;
	}

	bool Empty(const Pointer& First) {
		return First == nullptr;
	}

	void PushFront(Pointer& First, std::string info) {
		Pointer newNode = new Node(info, First);
		First = newNode;
	}

	void InsertOrder(Pointer& First, std::string info) {
		Pointer newNode = new Node(info, nullptr);

		//* Case the list does not have any item.
		if (Empty(First)) {
			First = newNode;
			return;
		}

		//* If info is less than or equal then insert to the first element of the list.
		if (First->info.compare(info) >= 0) {
			PushFront(First, info);
			return;
		}

		//* Case the list has one item and the info is for sure greater then the first element.
		if (First->next == nullptr) {
			First->next = newNode;
			return;
		}

		//* From now on the list must has more than one (or at least two elements) and the inserting item is greater than the first one.
		Pointer previousNode = First;
		for (; previousNode->next != nullptr && previousNode->next->info.compare(info) <= 0; previousNode = previousNode->next);

		if (previousNode->next != nullptr) {
			newNode->next = previousNode->next;
			previousNode->next = newNode;
		}
		else {
			previousNode->next = newNode;
		}
	}

	void Traversal(const Pointer& First) {
		Pointer p = First;
		for (; p != nullptr; p = p->next) {
			std::cout << p->info << " ";
		}
		std::cout << "\n";
	}
}


DauSachTab::DauSachTab(Package* package)
{
	//* Initialize data
	this->package_ = package;

	this->defaultView_ = true;

	this->Initialize();
}

void DauSachTab::Destructor() {}

void DauSachTab::Run()
{
	if (this->defaultView_ == true)
	{
		//* Title datasheet section runtime logic
		int titleDatasheetPackageRunningResult = this->titleDatasheetPackage_.Run();
		if (titleDatasheetPackageRunningResult == 1)
		{
			this->defaultView_ = false;
			this->titleDetailSection_.Activate();
			this->titleDetailSection_.SetTitlePointer(this->datasheetSelectedObject_.GetObjectPointer());
		}

		//* Selected title section runtime logic
		if (this->datasheetSelectedObject_.Run() == 1)
		{
			this->defaultView_ = false;
			this->titleDetailSection_.Activate();
			this->titleDetailSection_.SetTitlePointer(this->datasheetSelectedObject_.GetObjectPointer());
		}

		for (int i = 0; i < 3; ++i) { this->functionalButtons[i].Display(); }
		this->FunctionalButtonOnAction();

		//* Search field section runtime logic
		bool allowUpdateTitleDatesheet = this->titleSearchSection_.Run();
		if (allowUpdateTitleDatesheet)
		{
			std::cerr << "[LOG] UPDATE DATESHEET!\n";
			this->titleDatasheetPackage_.AllowCreateDatasheet();
			this->titleDatasheetPackage_.CreateDatasheet();
		}

		this->DatasheetSortingFunctionality();
	}

	//* Selected title's detail display section
	if (this->titleDetailSection_.InActive())
	{
		int titleDetailSectionRunningResult = this->titleDetailSection_.Run();
		if (titleDetailSectionRunningResult == -1) //* Back Button pressed logic
		{
			this->titleDetailSection_.Deactivate();
			this->defaultView_ = true;
		}
	}

	//* Displaying the ADD function.
	if (this->titleCreatingSection.GetStatus() == true)
	{
		this->titleCreatingSection.Display();

		if (this->titleCreatingSection.GoBackButtonOnAction())
		{
			this->titleCreatingSection.Deactivate();
			this->defaultView_ = true;
		}

		//WORKING
		bool newTitleListCreated = this->titleCreatingSection.Run();
		if (newTitleListCreated)
		{
			//DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
		}
	}
}

void DauSachTab::InitializeFilters()
{
	int listSize = this->package_->titleList->numberOfNode;

	this->defaultTitleListFilter_.filterSize_ = listSize;
	this->defaultTitleListFilter_.keep_ = listSize;
	this->defaultTitleListFilter_.filters_ = new bool[listSize];
	for (int i = 0; i < listSize; ++i) { this->defaultTitleListFilter_.filters_[i] = true; }

	this->sortedByCategoryTitleListFilter_.filterSize_ = listSize;
	this->sortedByCategoryTitleListFilter_.keep_ = listSize;
	this->sortedByCategoryTitleListFilter_.filters_ = new bool[listSize];
	for (int i = 0; i < listSize; ++i) { this->sortedByCategoryTitleListFilter_.filters_[i] = true; }
}

void DauSachTab::DatasheetSortingFunctionality()
{
	Button& titleLabelButton = this->titleDatasheetPackage_.AccessCurrentDatasheet()[0][2];
	if (titleLabelButton.IsHover())
	{
		titleLabelButton.SetFillColor(rgb(83, 127, 231));
		titleLabelButton.SetTextColor(rgb(233, 248, 249));
	}
	else if (titleLabelButton.LeftMouseClicked())
	{
		delay(100);

		std::cerr << "[LOG] Sorted by title's name!\n";

		this->titleSearchSection_.SetSearchData(this->package_->titleList);
		this->titleDatasheetPackage_.SetDataList(this->package_->titleList);
		this->titleDatasheetPackage_.SetDataFilter(&this->defaultTitleListFilter_);
		this->titleDatasheetPackage_.AllowCreateDatasheet();
		this->titleDatasheetPackage_.CreateDatasheet();
	}
	else
	{
		titleLabelButton.SetFillColor(rgb(210, 218, 255));
		titleLabelButton.SetTextColor(BLACK);
	}

	Button& categoryLabelButton = this->titleDatasheetPackage_.AccessCurrentDatasheet()[0][6];
	if (categoryLabelButton.IsHover())
	{
		categoryLabelButton.SetFillColor(rgb(83, 127, 231));
		categoryLabelButton.SetTextColor(rgb(233, 248, 249));
	}
	else if (categoryLabelButton.LeftMouseClicked())
	{
		delay(100);

		std::cerr << "[LOG] Sorted by title's category!\n";

		this->titleSearchSection_.SetSearchData(&this->sortedByCategoryTitleList_);
		this->titleDatasheetPackage_.SetDataList(&this->sortedByCategoryTitleList_);
		this->titleDatasheetPackage_.SetDataFilter(&this->sortedByCategoryTitleListFilter_);
		this->titleDatasheetPackage_.AllowCreateDatasheet();
		this->titleDatasheetPackage_.CreateDatasheet();
	}
	else
	{
		categoryLabelButton.SetFillColor(rgb(210, 218, 255));
		categoryLabelButton.SetTextColor(BLACK);
	}
}

void DauSachTab::CreateSortedByCategoryTitleList()
{
	CATEGORY_LINKED_LIST::Pointer categories;
	CATEGORY_LINKED_LIST::Initialzie(categories);

	CATEGORY_LINKED_LIST::PushFront(categories, this->package_->titleList->nodes[0]->GetCategory());
	bool flag = true;
	int categoryCount = 1;
	for (int i = 1; i < this->package_->titleList->numberOfNode; ++i)
	{
		flag = true;
		for (int j = 0; j < i; ++j)
		{
			if (this->package_->titleList->nodes[j]->GetCategory().compare(this->package_->titleList->nodes[i]->GetCategory()) == 0)
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			CATEGORY_LINKED_LIST::InsertOrder(categories, this->package_->titleList->nodes[i]->GetCategory());
			++categoryCount;
		}
	}

	LINEAR_LIST::Initialize(this->sortedByCategoryTitleList_);
	this->sortedByCategoryTitleList_.numberOfNode = this->package_->titleList->numberOfNode;
	int index = 0;
	for (CATEGORY_LINKED_LIST::Pointer p = categories; p != nullptr; p = p->next)
	{
		for (int i = 0; i < this->package_->titleList->numberOfNode; ++i)
		{
			if (this->package_->titleList->nodes[i]->GetCategory().compare(p->info) == 0)
			{
				this->sortedByCategoryTitleList_.nodes[index++] = this->package_->titleList->nodes[i];
			}
		}
	}

	delete categories;
}

void DauSachTab::Initialize()
{
	this->InitializeFilters();
	this->CreateSortedByCategoryTitleList();

	this->titleDatasheetPackage_ = DAU_SACH_TAB::DatasheetProcessor(this->package_->titleList, &this->defaultTitleListFilter_);
	this->titleDatasheetPackage_.SetSelectedObjectContainer(&this->datasheetSelectedObject_);
	this->titleDatasheetPackage_.Activate();
	this->titleDatasheetPackage_.AllowCreateDatasheet();
	this->titleDatasheetPackage_.CreateDatasheet();

	this->datasheetSelectedObject_.Activate();

	HELPER::Coordinate listManipulateButtonCoordinates[] = {
		HELPER::Coordinate(1585, 210),
		HELPER::Coordinate(1585, 300),
		HELPER::Coordinate(1585, 390)
	};
	HELPER::Dimension listManipulateButtonDimension(170, 70);
	std::string listManipulateButtonPlaceholders[] = { "NEW", "EDIT", "REMOVE" };
	for (int i = 0; i < 3; ++i)
	{
		this->functionalButtons[i] = Button(listManipulateButtonCoordinates[i], listManipulateButtonDimension);
		this->functionalButtons[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(this->functionalButtons[i]);
	}

	this->titleSearchSection_ = DAU_SACH_TAB::SearchSection(this->package_, &this->titleDatasheetPackage_);
	this->titleSearchSection_.SetSearchData(this->package_->titleList);
	this->titleSearchSection_.Activate();

	this->titleDetailSection_.Deactivate();
}

void DauSachTab::FunctionalButtonOnAction()
{
	for (int i = 0; i < 3; ++i)
	{
		Button& currentBtn = this->functionalButtons[i];

		if (currentBtn.IsHover())
		{
			DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonHoverProperties(currentBtn);
		}
		else if (currentBtn.LeftMouseClicked())
		{
			delay(100);
			switch (i)
			{
				case (0):
					this->defaultView_ = false;
					this->titleCreatingSection = DAU_SACH_TAB::TitleCreatingSection(this->package_);
					this->titleCreatingSection.Activate();
					break;
				case (1):
					std::cerr << "edit item!\n";
					break;
				case (2):
					std::cerr << "remove item!\n";
					break;
			}
		}
		else
		{
			DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(currentBtn);
		}

	}
}

