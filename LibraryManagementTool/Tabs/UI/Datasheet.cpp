#include "Datasheet.h"

namespace DATASHEET {

	Row::Row() {
		this->topLeft = this->bottomRight = HELPER::Coordinate();
		this->attributeCount = 0;
		this->items = nullptr;
		this->rowHeight = 0;
	}

	Row::Row(int attributeCount, int rowHeight, HELPER::Coordinate topLeft, std::string* data, int* characterLimits) {
		this->attributeCount = attributeCount;
		this->topLeft = topLeft;
		this->rowHeight = rowHeight;

		ELEMENTS::Padding padding(10);
		this->items = new Button[this->attributeCount];
		HELPER::Dimension boxDimension;
		for (int i = 0; i < this->attributeCount; ++i) {
			boxDimension.width = max(textwidth((char*)data[i].c_str()), textwidth((char*)"W") * characterLimits[i]) + padding.left + padding.right;
			boxDimension.height = this->rowHeight;
			if (i == 0) {
				this->items[i].SetTopLeft(this->topLeft);
			}
			else {
				this->items[i].SetTopLeft(HELPER::Coordinate(this->items[i - 1].GetTopLeft().x + this->items[i - 1].GetDimension().width, this->items[i - 1].GetTopLeft().y));
			}
			this->items[i].SetDimension(boxDimension);
			this->items[i].UpdateWithNewTopLeft();
			this->items[i].SetPlaceholder(data[i]);
		}
		this->bottomRight = this->items[attributeCount - 1].GetBottomRight();
	}

	Button& Row::operator[](int index) {
		if (index < 0 || index >= this->attributeCount) {
			std::cerr << "[ERROR] Row Index violation!";
			exit(1);
		}

		return this->items[index];
	}

	HELPER::Coordinate* Row::GetTopLeft() {
		return &this->topLeft;
	}

	HELPER::Coordinate* Row::GetBottomRight() {
		return &this->bottomRight;
	}

	int Row::GetItemCount() {
		return this->attributeCount;
	}

	void Row::UpdateRowData(std::string* data) {
		for (int i = 0; i < this->attributeCount; ++i) {
			this->items[i].SetPlaceholder(data[i]);
		}
	}

	void Row::Display() {
		for (int i = 0; i < this->attributeCount; ++i) {
			this->items[i].Display();
		}
	}

	int Row::IsHover() {
		for (int i = 0; i < this->attributeCount; ++i) {
			if (this->items[i].IsHover()) {
				return i;
			}
		}
		return -1;
	}

	int Row::LeftMouseClicked() {
		for (int i = 0; i < this->attributeCount; ++i) {
			if (this->items->LeftMouseClicked()) {
				return i;
			}
		}

		return -1;
	}

	void Row::Destructor() {
		delete[this->attributeCount] this->items;
	}

	void Datasheet::DefaultLabelsProperties(Row& field) {
		for (int i = 0; i < field.GetItemCount(); ++i) {
			field[i].SetFillColor(rgb(210, 218, 255));
			field[i].SetBorderColor(rgb(25, 24, 37));
			field[i].SetTextColor(rgb(25, 24, 37));
		}
	}

	void Datasheet::DefaultDataFieldProperties(Row& field, int order) {
		for (int i = 0; i < field.GetItemCount(); ++i) {
			if (order % 2 != 0) {
				field[i].SetFillColor(rgb(255, 251, 245));
			}
			else {
				field[i].SetFillColor(rgb(238, 238, 238));
			}
			field[i].SetBorderColor(rgb(25, 24, 37));
			field[i].SetTextColor(rgb(25, 24, 37));
		}
	}

	Datasheet::Datasheet() {
		this->recordCount = this->attributeCount = 0;
		this->topLeft = this->bottomRight = HELPER::Coordinate();
		this->records = nullptr;
		this->rowHeight = 0;
	}

	Datasheet::Datasheet(int recordCount, int attributeCount, int rowHeight, HELPER::Coordinate topLeft, std::string* data, int* characterLimits) {
		//* Assign parameterized field
		this->recordCount = recordCount;
		this->attributeCount = attributeCount;
		this->topLeft = topLeft;
		this->rowHeight = rowHeight;

		//* Some references for easy coding
		std::string* defaultData = new std::string[this->attributeCount];
		for (int i = 0; i < this->attributeCount; ++i) {
			defaultData[i] = "...";
		}

		//* Create Datasheet logic
		this->records = new DATASHEET::Row[this->recordCount];
		for (int i = 0; i < this->recordCount; ++i) {
			DATASHEET::Row& currentRow = this->records[i];

			if (i == 0) {//* Create labels
				currentRow = DATASHEET::Row(this->attributeCount, this->rowHeight, this->topLeft, data, characterLimits);
				currentRow.UpdateRowData(data);
				DATASHEET::Datasheet::DefaultLabelsProperties(currentRow);
			}
			else {//* Create data's field
				currentRow = DATASHEET::Row(this->attributeCount, this->rowHeight,
					HELPER::Coordinate(this->records[i - 1].GetTopLeft()->x, this->records[i - 1].GetBottomRight()->y),
					data, characterLimits
				);
				currentRow.UpdateRowData(defaultData);
				DATASHEET::Datasheet::DefaultDataFieldProperties(currentRow, i);
			}
		}

		delete[this->attributeCount] defaultData;
	}

	Row& Datasheet::operator[](int index) {
		if (index < 0 || index >= this->recordCount) {
			std::cerr << "[ERROR] Datasheet index violation!\n";
			exit(1);
		}

		return this->records[index];
	}

	void Datasheet::UpdateNewPlaceholder(std::string* newPlaceholder, int rowIndicator) {
		if (rowIndicator <= 0 || rowIndicator >= CONSTANTS::MAX_ROW_COUNT) {
			return;
		}

		for (int i = 0; i < this->attributeCount; ++i) {
			this->records[rowIndicator][i].SetPlaceholder(newPlaceholder[i]);
		}
	}

	int Datasheet::GetRecordCount() {
		return this->attributeCount;
	}

	void Datasheet::Display() {
		for (int i = 0; i < this->recordCount; ++i) {
			this->records[i].Display();
		}
	}

	void Datasheet::Destructor() {
		delete[this->recordCount] this->records;
	}

	void Controller::DatasheetChangeBTNHover(Button& btn) {
		btn.SetFillColor(rgb(130, 170, 227));
	}

	void Controller::DatasheetChangeBTNProperties(Button& btn) {
		btn.SetFillColor(rgb(236, 242, 255));
		btn.SetBorderColor(rgb(25, 24, 37));
		btn.SetTextColor(rgb(25, 24, 37));
	}

	Controller::Controller() {
		this->datasheetCount = 0;
		this->sheets = nullptr;
		this->activeSheet = -1;
		this->attributeCount = 0;
		this->recordCount = 0;
		this->rowHeight = 0;
	}

	Controller::Controller(int recordCount, int attributeCount, int rowHeight, HELPER::Coordinate topLeft) {
		this->recordCount = recordCount;
		this->attributeCount = attributeCount;
		this->rowHeight = rowHeight;
		this->topLeft = topLeft;

		this->datasheetCount = 0;
		this->sheets = nullptr;
		this->activeSheet = -1;

		HELPER::Coordinate buttonCoordinates[] = {
			HELPER::Coordinate(36, 940),
			HELPER::Coordinate(86, 940)
		};
		std::string placeholder[] = { "<", ">" };

		for (int i = 0; i < 2; ++i) {
			this->datasheetChangeButton[i] = Button(buttonCoordinates[i], 50, 30);
			this->datasheetChangeButton[i].SetPlaceholder(placeholder[i]);
			this->DatasheetChangeBTNProperties(this->datasheetChangeButton[i]);
		}
	}

	Controller::~Controller() {
		for (int i = 0; i < this->datasheetCount; ++i) {
			for (int j = 0; j < this->sheets[i].GetRecordCount(); ++j) {
				this->sheets[i][j].Destructor();
			}
			this->sheets[i].Destructor();
		}
		delete[this->datasheetCount] this->sheets;
	}

	Datasheet& Controller::operator[](int index) {
		if (index < 0 || index >= this->datasheetCount) {
			std::cerr << "[ERROR] Datasheet controller index violation!\n";
			exit(1);
		}

		return this->sheets[index];
	}

	void Controller::InitializeDatasheets() {
		this->sheets = new DATASHEET::Datasheet[this->datasheetCount];
		this->activeSheet = 0;
	}

	void Controller::SetDatasheetCount(int amount) {
		this->datasheetCount = amount;
	}

	int Controller::GetDatasheetCount() {
		return this->datasheetCount;
	}

	int Controller::GetAttributeCount() {
		return this->attributeCount;
	}

	int Controller::GetRecordCount() {
		return this->recordCount;
	}

	int Controller::GetRowHeight() {
		return this->rowHeight;
	}

	int Controller::CurrentActiveDatasheet() {
		return this->activeSheet;
	}

	void Controller::SetActiveDatasheet(int index) {
		this->activeSheet = index;
	}

	HELPER::Coordinate Controller::GetTopLeft() {
		return this->topLeft;
	}

	void Controller::UpdateActiveSheet(int indicator) {
		if (indicator < 0 || indicator >= this->datasheetCount) {
			return;
		}
		this->activeSheet = indicator;
	}

	void Controller::DatasheetChangeButtonUpdate() {
		int movement[2] = { -1, +1 };
		for (int i = 0; i < 2; ++i) {
			if (this->datasheetChangeButton[i].IsHover()) {
				this->DatasheetChangeBTNHover(this->datasheetChangeButton[i]);
			}
			else if (this->datasheetChangeButton[i].LeftMouseClicked()) {
				this->activeSheet = (this->activeSheet + movement[i] + this->datasheetCount) % this->datasheetCount;
				delay(100);
			}
			else {
				this->DatasheetChangeBTNProperties(this->datasheetChangeButton[i]);
			}
		}
	}

	void Controller::Display() {
		this->sheets[this->activeSheet].Display();

		for (int i = 0; i < 2; ++i) {
			this->datasheetChangeButton[i].Display();
		}
	}

}
