#include "BookCirculationTable.h"

BOOK_CIRCULATION_TABLE::DatasheetProcessor::DatasheetProcessor()
{
	this->datasheetController_ = {
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::MAX_ROW,
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		HELPER::Coordinate(1175, 380)
	};

	this->datasheetController_.NavigateIndicator(0).SetTopLeft({ 1175, 885 });
	this->datasheetController_.NavigateIndicator(0).SetDimension({ 40, 30 });
	this->datasheetController_.NavigateIndicator(0).SetPlaceholder("<");
	this->datasheetController_.NavigateIndicator(0).UpdateWithNewTopLeft();

	this->datasheetController_.NavigateIndicator(1).SetTopLeft({ 1215, 885 });
	this->datasheetController_.NavigateIndicator(1).SetDimension({ 40, 30 });
	this->datasheetController_.NavigateIndicator(1).SetPlaceholder(">");
	this->datasheetController_.NavigateIndicator(1).UpdateWithNewTopLeft();
}

BOOK_CIRCULATION_TABLE::DatasheetProcessor::DatasheetProcessor(const DatasheetProcessor& other)
{
	if (this != &other)
	{
		status_ = other.status_;
		allowCreateDatasheet_ = other.allowCreateDatasheet_;
		datasheetController_ = other.datasheetController_;
		dataFilter_ = other.dataFilter_;
		readerPointer_ = other.readerPointer_;
		datasheetSelectedObject_ = other.datasheetSelectedObject_;
	}
}

BOOK_CIRCULATION_TABLE::DatasheetProcessor::DatasheetProcessor(AVL_TREE::Pointer readerPointer, DataFilter* dataFilter)
{
	this->readerPointer_ = readerPointer;
	this->dataFilter_ = dataFilter_;
}

BOOK_CIRCULATION_TABLE::DatasheetProcessor& BOOK_CIRCULATION_TABLE::DatasheetProcessor::operator=(const DatasheetProcessor& other)
{
	if (this == &other) { return *this; }

	status_ = other.status_;
	allowCreateDatasheet_ = other.allowCreateDatasheet_;
	datasheetController_ = other.datasheetController_;
	dataFilter_ = other.dataFilter_;
	readerPointer_ = other.readerPointer_;
	datasheetSelectedObject_ = other.datasheetSelectedObject_;
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::SetSelectedObjectContainer(SelectedObject<DOUBLE_LINKED_LIST::Pointer>* datasheetSelectedObject)
{
	this->datasheetSelectedObject_ = datasheetSelectedObject;
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::AllowCreateDatasheet() { this->allowCreateDatasheet_ = true; }

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::CreateDatasheet()
{
	//* Filtering out all cases where cannot create datasheet
	if (!this->status_) { return; }

	if (!this->allowCreateDatasheet_) { return; }

	if (this->dataFilter_->filters_ == nullptr) { return; }

	//* Creating datasheet
	int listSize = this->dataFilter_->keep_;
	this->datasheetController_.SetDatasheetCount(
		max(1,
			(listSize / (READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::MAX_ROW - 1) +
				(listSize % (READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::MAX_ROW - 1) == 0 ? 0 : 1))
		)
	);
	this->datasheetController_.InitializeDatasheets();

	for (int i = 0; i < this->datasheetController_.GetDatasheetCount(); ++i)
	{
		this->datasheetController_[i] = {
			this->datasheetController_.GetRecordCount(),
			this->datasheetController_.GetAttributeCount(),
			this->datasheetController_.GetRowHeight(),
			this->datasheetController_.GetTopLeft(),
			(std::string*)READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
			(int*)READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::CHARACTER_LIMITS
		};
	}

	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;
	int index = 0;

	auto dataList = this->readerPointer_->info.GetBooksCirculation();
	for (auto currentNode = dataList.First; currentNode != nullptr; currentNode = currentNode->right)
	{
		if (this->dataFilter_->filters_[index] == true)
		{
			++recordIndex;
			if (recordIndex > this->datasheetController_.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (this->datasheetController_.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[this->datasheetController_.GetAttributeCount()];
			if (this->datasheetController_.GetAttributeCount() == 5)
			{
				std::string isbn = currentNode->info.GetID().substr(0, 4);

				data[0] = std::to_string(++order);
				data[1] = currentNode->info.GetID();
				data[2] = currentNode->info.GetBorrowDate().Stringify();
				data[3] = currentNode->info.GetReturnDate().Stringify();
				data[4] = currentNode->info.StringfyStatus();

				(this->datasheetController_)[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
			}

			delete[] data;
		}
		++index;
	}

	//std::cerr << "[BOOK_CIRCULATION_TABLE::DatasheetProcessor::CreateDatasheet] Width: " << datasheetController_.GetBottomRight().x - datasheetController_.GetTopLeft().x << "\n";

	//* Completed creating datasheet
	this->datasheetController_.ActivateDatasheets();
	this->allowCreateDatasheet_ = false;
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::SetPackage(Package* package)
{
	this->package_ = package;
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::SetDataFilter(DataFilter* dataFilter) { this->dataFilter_ = dataFilter; }

DataFilter* BOOK_CIRCULATION_TABLE::DatasheetProcessor::GetDataFilter() { return this->dataFilter_; }

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::SetDataList(AVL_TREE::Pointer readerPointer)
{
	this->readerPointer_ = readerPointer;
}

DataFilter*& BOOK_CIRCULATION_TABLE::DatasheetProcessor::AccessDataFilter() { return this->dataFilter_; }

DATASHEET::Datasheet& BOOK_CIRCULATION_TABLE::DatasheetProcessor::AccessCurrentDatasheet()
{
	return this->datasheetController_[this->datasheetController_.CurrentActiveDatasheet()];
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::Initialize()
{
}

void BOOK_CIRCULATION_TABLE::DatasheetProcessor::Display()
{
	if (!this->status_) { return; }

	this->datasheetController_.Display();
	this->datasheetController_.DatasheetChangeButtonUpdate();
}

int BOOK_CIRCULATION_TABLE::DatasheetProcessor::Run()
{
	if (!this->status_) { return 0; }

	this->Display();
	if (this->DatasheetOnAction() == 1) { return 1; }

	return 0;
}

int BOOK_CIRCULATION_TABLE::DatasheetProcessor::DatasheetOnAction()
{
	if (!this->status_) { return 0; }

	int currentDatasheetIndex = this->datasheetController_.CurrentActiveDatasheet();
	int datasheetColumnCount = this->datasheetController_.GetAttributeCount();
	int datasheetRowCount = this->datasheetController_.GetRecordCount();

	std::string targetID{};

	for (int rowIndex = 1; rowIndex < datasheetRowCount; ++rowIndex)
	{
		for (int columnIndex = 1; columnIndex <= 3; ++columnIndex)
		{
			Button& IDCell = this->datasheetController_[currentDatasheetIndex][rowIndex][columnIndex];

			if (IDCell.GetPlaceholder().compare("...") == 0) { continue; }

			if (IDCell.IsHover())
			{
				IDCell.SetFillColor(rgb(221, 230, 237));
			}
			else if (IDCell.LeftMouseClicked())
			{
				delay(130);

				targetID = this->datasheetController_[currentDatasheetIndex][rowIndex][1].GetPlaceholder();
				DOUBLE_LINKED_LIST::Pointer selectedObject = nullptr;

				int index = 0;
				auto dataList = this->readerPointer_->info.GetBooksCirculation();
				for (auto currentNode = dataList.First; currentNode != nullptr; currentNode = currentNode->right)
				{
					if (this->dataFilter_->filters_[index] && currentNode->info.GetID().compare(targetID) == 0)
					{
						selectedObject = currentNode;
					}
					//---

					++index;
				}

				if (selectedObject == nullptr)
				{
					throw std::logic_error("[ERROR] Selected object is NULL! (DatasheetProcessor::DatasheetOnAction)");
				}

				this->datasheetSelectedObject_->SetObjectPointer(selectedObject);
				(*this->datasheetSelectedObject_).AccessIndicator().SetPlaceholder("Selecting Reader ID: " + selectedObject->info.GetID());
			}
			else if (IDCell.RightMouseClicked())
			{
				delay(130);

				targetID = this->datasheetController_[currentDatasheetIndex][rowIndex][1].GetPlaceholder();
				DOUBLE_LINKED_LIST::Pointer selectedObject = nullptr;

				int index = 0;
				auto dataList = this->readerPointer_->info.GetBooksCirculation();
				for (auto currentNode = dataList.First; currentNode != nullptr; currentNode = currentNode->right)
				{
					if (this->dataFilter_->filters_[index] && currentNode->info.GetID().compare(targetID) == 0)
					{
						selectedObject = currentNode;
					}
					//---

					++index;
				}

				if (selectedObject == nullptr)
				{
					throw std::logic_error("[ERROR] Selected object is NULL! (DatasheetProcessor::DatasheetOnAction)");
				}

				this->datasheetSelectedObject_->SetObjectPointer(selectedObject);
				(*this->datasheetSelectedObject_).AccessIndicator().SetPlaceholder("Selecting Reader ID: " + selectedObject->info.GetID());

				return 1;
			}
			else
			{
				if (rowIndex % 2 == 0) { IDCell.SetFillColor(rgb(238, 238, 238)); }
				else { IDCell.SetFillColor(rgb(255, 251, 245)); }
			}
		}
	}

	return 0;
}
