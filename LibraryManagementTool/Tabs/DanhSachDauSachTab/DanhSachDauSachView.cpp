#include "DanhSachDauSachView.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


namespace DAU_SACH_TAB {
	SearchField::SearchField() {
		this->background = new HELPER::Fill(HELPER::Coordinate(1405, 120), 350, 250);
		this->title = new Button(HELPER::Coordinate(1405, 120), 350, 50);
		this->title->SetPlaceholder("SEARCH");

		this->inputSearchBox = new Button(HELPER::Coordinate(1430, 200), 300, 70);
		this->inputSearchBox->SetPlaceholder("Type here to search");

		this->searchStatusBox = new Button(HELPER::Coordinate(1430, 295), 300, 50);
		this->searchStatusBox->SetPlaceholder("Result:");
	}

	void SearchField::Display() {
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::BackgroundStyling(this->background);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::TitleStyling(this->title);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchStatusBox);

		this->background->Draw();
		this->title->Display();
		this->inputSearchBox->Display();
		this->searchStatusBox->Display();
	}
}



void DauSachTab::CreateDatasheetsFromList(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controller& controler) {
	int attributeCount = danhSachDauSach.numberOfNode;
	controler.SetDatasheetCount(
		attributeCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (attributeCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
	);
	controler.InitializeDatasheets();

	for (int i = 0; i < controler.GetDatasheetCount(); ++i) {
		controler[i] = DATASHEET::Datasheet(
			controler.GetRecordCount(), controler.GetAttributeCount(), controler.GetRowHeight(), controler.GetTopLeft(),
			(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, (int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
		);
	}

	int recordIndex = 0;
	int sheetIndex = -1;

	for (int i = 0; i < danhSachDauSach.numberOfNode; ++i) {

		++recordIndex;
		if (recordIndex > controler.GetRecordCount() - 1) {
			recordIndex = 1;
		}
		if (recordIndex % (controler.GetRecordCount() - 1) == 1) {
			sheetIndex += 1;
		}

		std::string* data = new std::string[controler.GetAttributeCount()];
		data[0] = std::to_string(i + 1);
		data[1] = danhSachDauSach.nodes[i]->GetISBN();
		data[2] = danhSachDauSach.nodes[i]->GetTenSach();
		data[3] = std::to_string(danhSachDauSach.nodes[i]->GetSoTrang());
		data[4] = danhSachDauSach.nodes[i]->GetTacGia();
		data[5] = std::to_string(danhSachDauSach.nodes[i]->GetNamXuatBan());
		data[6] = danhSachDauSach.nodes[i]->GetTheLoai();
		data[7] = "DANH MUC SACH";

		controler[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}
}

void DauSachTab::SortList(LINEAR_LIST::LinearList& dsDauSach) {
	for (int i = 0; i < dsDauSach.numberOfNode - 1; ++i) {
		for (int j = i + 1; j < dsDauSach.numberOfNode; ++j) {
			const std::string& valueA = dsDauSach.nodes[i]->GetTenSach();
			const std::string& valueB = dsDauSach.nodes[j]->GetTenSach();

			if (valueA.compare(valueB) > 0) {
				std::swap(dsDauSach.nodes[i], dsDauSach.nodes[j]);
			}
		}
	}
}

DauSachTab::DauSachTab(LINEAR_LIST::LinearList& danhSachDauSach) {
	this->active = false;
	this->displaDatasheet = true;

	HELPER::Coordinate datasheetTopLeft(36, 120);

	this->controler = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT, DAU_SACH_PROPERTIES::PROPERTIES_COUNT, DAU_SACH_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheetsFromList(danhSachDauSach, controler);

	/*
	 * Creating Button for adding or editting or removing item of the list
	*/
	HELPER::Coordinate listManipulateButtonCoordinates[] = {
		HELPER::Coordinate(380, 940),
		HELPER::Coordinate(565, 940),
		HELPER::Coordinate(750, 940)
	};
	HELPER::Dimension listManipulateButtonDimension(150, 30);
	std::string listManipulateButtonPlaceholders[] = {"NEW", "EDIT", "REMOVE"};

	for (int i = 0; i < 3; ++i) {
		this->listManipulateButtons[i] = Button(listManipulateButtonCoordinates[i], listManipulateButtonDimension);
		this->listManipulateButtons[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(this->listManipulateButtons[i]);
	}
}

void DauSachTab::Run() {

	//* Displaying all the items
	if (this->displaDatasheet) {
		this->controler.Display();
		this->controler.DatasheetChangeButtonUpdate();
	}

	for (int i = 0; i < 3; ++i) {
		this->listManipulateButtons[i].Display();
	}

	this->searchField.Display();


	//* List manipulate button logic
	for (int i = 0; i < 3; ++i) {
		Button& currentBtn = this->listManipulateButtons[i];

		if (currentBtn.IsHover()) {
			DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonHoverProperties(currentBtn);
		}
		else if (currentBtn.NotYetClicked() && currentBtn.LeftMouseClicked()) {
			switch (i) {
				case (0):
					//delay(100);

					//* hide datasheet
					std::cerr << std::format("click count: {}\n", currentBtn.GetClickCount());

					if (currentBtn.GetClickCount() == 0) { //* First time the button get clicked -> Hide the datasheet
						this->displaDatasheet = false;
					}
					else { //* The button is clicked, the second time it gets click will turn off the add item function and display the datasheet.
						this->displaDatasheet = true;
						currentBtn.ResetClickCount();
					}
					break;
				case (1):
					std::cerr << "edit item!\n";
					break;
				case (2):
					std::cerr << "remove item!\n";
					break;
			}
		}
		else {
			DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(currentBtn);
		}
	}
}
