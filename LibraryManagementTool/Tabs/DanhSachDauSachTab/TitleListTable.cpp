#include "TitleListTable.hpp"

TITLE_LIST_TABLE::TitleRecord::TitleRecord()
{
}

TITLE_LIST_TABLE::TitleRecord::TitleRecord(const TitleRecord& other)
{
	if (this != &other)
	{
		this->~TitleRecord();

		this->status_ = other.status_;

		this->objectPointer_ = other.objectPointer_;

		this->indexIndicator_ = other.indexIndicator_;

		this->recordIndex_ = other.recordIndex_;

		this->attributeCount_ = other.attributeCount_;

		for (int i = 0; i < other.attributeCount_; ++i)
		{
			this->attributes_[i] = other.attributes_[i];
		}
	}
}

TITLE_LIST_TABLE::TitleRecord& TITLE_LIST_TABLE::TitleRecord::operator=(const TitleRecord& other)
{
	if (this == &other) { return *this; }

	this->~TitleRecord();

	this->status_ = other.status_;

	this->objectPointer_ = other.objectPointer_;

	this->indexIndicator_ = other.indexIndicator_;

	this->recordIndex_ = other.recordIndex_;

	this->attributeCount_ = other.attributeCount_;

	for (int i = 0; i < other.attributeCount_; ++i)
	{
		this->attributes_[i] = other.attributes_[i];
	}
}

bool TITLE_LIST_TABLE::TitleRecord::Create(int recordIndex, BOOK_TITLE::BookTitle* objectPointer, HELPER::Coordinate topLeft)
{
	this->recordIndex_ = recordIndex;
	this->objectPointer_ = objectPointer;
	this->topLeft_ = topLeft;

	this->indexIndicator_.SetTopLeft(this->topLeft_);
	this->indexIndicator_.UpdateWithNewTopLeft();
	this->indexIndicator_.SetPlaceholder(std::to_string(recordIndex));

	HELPER::Coordinate cellTopLeft[6] = {};
	HELPER::Dimension cellDimensions[6] = {};
	for (int i = 0; i < this->attributeCount_; ++i)
	{
		if (i == 0)
		{
			cellTopLeft[i] = {
				this->topLeft_.x + this->indexIndicator_.GetDimension().width,
				this->topLeft_.y
			};
			cellDimensions[i] = {
				DATASHEET_DEFAULT_PROPERTIES::LETTER_WIDTH * TITLE_LIST_TABLE_PROPERTIES::MAX_CHARACTERS[i] + 20,
				DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT
			};
		}
		else
		{
			cellTopLeft[i] = {
				cellTopLeft[i - 1].x + cellDimensions[i - 1].width,
				cellTopLeft[i - 1].y
			};
			cellDimensions[i] = {
				DATASHEET_DEFAULT_PROPERTIES::LETTER_WIDTH* TITLE_LIST_TABLE_PROPERTIES::MAX_CHARACTERS[i] + 20,
				DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT
			};
		}
		this->attributes_[i] = Button(cellTopLeft[i], cellDimensions[i]);
		this->attributes_[i].SetPlaceholder("...");

		this->dimension_.width = this->indexIndicator_.GetDimension().width;
		for (int i = 0; i < 6; ++i) { this->dimension_.width += this->attributes_[i].GetDimension().width; }
		this->dimension_.height = DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT;
	}

	if (objectPointer == nullptr)
	{
		//std::cerr << std::format("[ERROR] Object's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::TitleRecord::Create)\n");
		return false;
	}

	this->attributes_[0].SetPlaceholder(objectPointer->GetISBN());
	this->attributes_[1].SetPlaceholder(objectPointer->GetTitle());
	this->attributes_[2].SetPlaceholder(std::to_string(objectPointer->GetPageCount()));
	this->attributes_[3].SetPlaceholder(objectPointer->GetAuthor());
	this->attributes_[4].SetPlaceholder(std::to_string(objectPointer->GetPublicationYear()));
	this->attributes_[5].SetPlaceholder(objectPointer->GetCategory());

	return true;
}

TITLE_LIST_TABLE::TitleListTable::TitleListTable()
{
}

TITLE_LIST_TABLE::TitleListTable::TitleListTable(const TitleListTable& other)
{
	if (this != &other)
	{
		this->~TitleListTable();

		this->status_ = other.status_;

		this->topLeft_ = other.topLeft_;

		this->dimension_ = other.dimension_;

		this->recordCount_ = other.recordCount_;

		for (int i = 0; i < other.recordCount_; ++i)
		{
			this->records_[i] = other.records_[i];
		}
	}
}

TITLE_LIST_TABLE::TitleListTable& TITLE_LIST_TABLE::TitleListTable::operator=(const TitleListTable& other)
{
	if (this == &other) { return *this; }

	this->~TitleListTable();

	this->status_ = other.status_;

	this->topLeft_ = other.topLeft_;

	this->dimension_ = other.dimension_;

	this->recordCount_ = other.recordCount_;

	for (int i = 0; i < other.recordCount_; ++i)
	{
		this->records_[i] = other.records_[i];
	}
}

int TITLE_LIST_TABLE::CreateTables(LINEAR_LIST::LinearList* titleList, TITLE_LIST_TABLE::TitleListTableController* tables, HELPER::Coordinate topLeft)
{
	tables->SetTopLeft(topLeft);

	topLeft.Log();

	const std::string* placeholders = TITLE_LIST_TABLE_PROPERTIES::LABEL_PLACEHOLDERS;
	int tableCount = titleList->numberOfNode / DATASHEET_DEFAULT_PROPERTIES::MAX_ROW + (titleList->numberOfNode % DATASHEET_DEFAULT_PROPERTIES::MAX_ROW != 0);
	tables->Initialize(tableCount);

	int tableIndex = 0;
	int recordIndex = 0;
	HELPER::Coordinate recordTopLeft = topLeft;
	for (int i = 0; i < titleList->numberOfNode; ++i)
	{
		if (recordIndex == DATASHEET_DEFAULT_PROPERTIES::MAX_ROW)
		{
			recordIndex = 0;
			++tableIndex;
			recordTopLeft = topLeft;
		}
		recordTopLeft.Log();
		auto& record = (*tables)[tableIndex][recordIndex];
		record.Activate();
		record.Create(recordIndex + 1, titleList->nodes[i], recordTopLeft);
		recordTopLeft = {
			recordTopLeft.x,
			recordTopLeft.y + DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT
		};
	}

	if (titleList == nullptr)
	{
		//throw std::logic_error("[ERROR] Empty title list pointer!\n");

		std::cerr << "[ERROR] Empty title list pointer!\n";
		std::cerr << "[LOG] Generating empty talbes!\n";

		return 0;
	}

	return 1;
}
