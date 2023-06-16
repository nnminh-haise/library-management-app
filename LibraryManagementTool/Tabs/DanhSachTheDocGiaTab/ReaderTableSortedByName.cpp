#include "ReaderTableSortedByName.h"

READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::DatasheetProcessor()
{
	this->datasheetController_ = {
	DATASHEET_DEFAULT_PROPERTIES::MAX_ROW,
	READER_PROPERTIES::PROPERTIES_COUNT,
	DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
	HELPER::Coordinate(147, 210),
	HELPER::Coordinate(147, 940)
	};
}

READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::DatasheetProcessor(const READER_TABLE_SORTED_BY_NAME::DatasheetProcessor& other)
{
	if (this != &other)
	{
		status_ = other.status_;
		allowCreateDatasheet_ = other.allowCreateDatasheet_;
		datasheetController_ = other.datasheetController_;
		dataFilter_ = other.dataFilter_;
		dataList_ = other.dataList_;
		datasheetSelectedObject_ = other.datasheetSelectedObject_;
	}
}

READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::DatasheetProcessor(LinearList<AVL_TREE::Pointer>* dataList, DataFilter* dataFilter_)
{
	this->dataList_ = dataList;
	this->dataFilter_ = dataFilter_;
}

READER_TABLE_SORTED_BY_NAME::DatasheetProcessor& READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::operator=(const READER_TABLE_SORTED_BY_NAME::DatasheetProcessor& other)
{
	if (this == &other) { return *this; }

	status_ = other.status_;
	allowCreateDatasheet_ = other.allowCreateDatasheet_;
	datasheetController_ = other.datasheetController_;
	dataFilter_ = other.dataFilter_;
	dataList_ = other.dataList_;
	datasheetSelectedObject_ = other.datasheetSelectedObject_;
}

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::SetSelectedObjectContainer(SelectedObject<AVL_TREE::Pointer>* datasheetSelectedObject)
{
	this->datasheetSelectedObject_ = datasheetSelectedObject;
}

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::AllowCreateDatasheet() { this->allowCreateDatasheet_ = true; }

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::CreateDatasheet()
{
	//* Filtering out all cases where cannot create datasheet
	if (!this->status_) { return; }

	if (!this->allowCreateDatasheet_) { return; }

	if (this->dataFilter_->filters_ == nullptr) { return; }

	//* Creating datasheet
	int listSize = this->dataFilter_->keep_;
	this->datasheetController_.SetDatasheetCount(
		max(1,
			(listSize / (DATASHEET_DEFAULT_PROPERTIES::MAX_ROW - 1) +
				(listSize % (DATASHEET_DEFAULT_PROPERTIES::MAX_ROW - 1) == 0 ? 0 : 1))
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
			(std::string*)READER_PROPERTIES::LABEL_PLACEHOLDERS,
			(int*)READER_PROPERTIES::CHARACTER_LIMITS
		};
	}

	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	int dataListSize = this->dataList_->Size();
	for (int i = 0; i < dataListSize; ++i)
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
			if (this->datasheetController_.GetAttributeCount() == 6)
			{
				auto readerPointer = (*this->dataList_)[i];

				data[0] = std::to_string(++order);
				data[1] = std::to_string(readerPointer->info.GetID());
				data[2] = readerPointer->info.GetFirstName();
				data[3] = readerPointer->info.GetLastName();
				data[4] = readerPointer->info.StringifyGender();
				data[5] = readerPointer->info.StringfyStatus();

				(this->datasheetController_)[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
			}

			delete[] data;
		}
	}

	//std::cerr << datasheetController_.GetBottomRight().x - datasheetController_.GetTopLeft().x << "\n";

	//* Completed creating datasheet
	this->datasheetController_.ActivateDatasheets();
	this->allowCreateDatasheet_ = false;
}

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::SetDataFilter(DataFilter* dataFilter) { this->dataFilter_ = dataFilter; }

DataFilter* READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::GetDataFilter() { return this->dataFilter_; }

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::SetDataList(LinearList<AVL_TREE::Pointer>* dataList)
{
	this->dataList_ = dataList;
}

DataFilter*& READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::AccessDataFilter() { return this->dataFilter_; }

DATASHEET::Datasheet& READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::AccessCurrentDatasheet()
{
	return this->datasheetController_[this->datasheetController_.CurrentActiveDatasheet()];
}

void READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::Display()
{
	if (!this->status_) { return; }

	this->datasheetController_.Display();
	this->datasheetController_.DatasheetChangeButtonUpdate();
}

int READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::Run()
{
	if (!this->status_) { return 0; }

	this->Display();
	if (this->DatasheetOnAction() == 1) { return 1; }

	return 0;
}

int READER_TABLE_SORTED_BY_NAME::DatasheetProcessor::DatasheetOnAction()
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
				AVL_TREE::Pointer selectedObject = nullptr;

				int dataListSize = this->dataList_->Size();
				for (int i = 0; i < dataListSize; ++i)
				{
					auto readerPointer = (*this->dataList_)[i];

					if (this->dataFilter_->filters_[i] && std::to_string(readerPointer->info.GetID()).compare(targetID) == 0)
					{
						selectedObject = readerPointer;
					}
				}

				if (selectedObject == nullptr)
				{
					throw std::logic_error("[ERROR] Selected object is NULL! (DatasheetProcessor::DatasheetOnAction)");
				}

				this->datasheetSelectedObject_->SetObjectPointer(selectedObject);
				(*this->datasheetSelectedObject_).AccessIndicator().SetPlaceholder("Selecting Reader ID: " + std::to_string(selectedObject->info.GetID()));
			}
			else if (IDCell.RightMouseClicked())
			{
				delay(130);

				targetID = this->datasheetController_[currentDatasheetIndex][rowIndex][1].GetPlaceholder();
				AVL_TREE::Pointer selectedObject = nullptr;

				int dataListSize = this->dataList_->Size();
				for (int i = 0; i < dataListSize; ++i)
				{
					auto readerPointer = (*this->dataList_)[i];

					if (this->dataFilter_->filters_[i] && std::to_string(readerPointer->info.GetID()).compare(targetID) == 0)
					{
						selectedObject = readerPointer;
					}
				}

				if (selectedObject == nullptr)
				{
					throw std::logic_error("[ERROR] Selected object is NULL! (DatasheetProcessor::DatasheetOnAction)");
				}

				this->datasheetSelectedObject_->SetObjectPointer(selectedObject);
				(*this->datasheetSelectedObject_).AccessIndicator().SetPlaceholder("Selecting Reader ID: " + std::to_string(selectedObject->info.GetID()));

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
