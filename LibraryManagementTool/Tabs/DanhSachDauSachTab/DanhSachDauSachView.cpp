#include "DanhSachDauSachView.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


namespace DANH_SACH_DAU_SACH_TAB {
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

	// NewListItemForm::NewListItemForm() {
	// 	this->background = new ELEMENTS::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	// 	this->title = new ELEMENTS::Button(HELPER::Coordinate(1305, 420), 450, 50);
	// 	this->title->SetPlaceholder("THE DOC GIA");

	// 	this->maThe = new ELEMENTS::Button(HELPER::Coordinate(1330, 500), 400, 60);
	// 	this->maThe->SetPlaceholder("Ma the");

	// 	this->ho = new ELEMENTS::Button(HELPER::Coordinate(1330, 590), 400, 60);
	// 	this->ho->SetPlaceholder("Ho");

	// 	this->ten = new ELEMENTS::Button(HELPER::Coordinate(1330, 680), 400, 60);
	// 	this->ten->SetPlaceholder("Ten");

	// 	this->phai = new ELEMENTS::Button(HELPER::Coordinate(1330, 770), 400, 60);
	// 	this->phai->SetPlaceholder("Phai");

	// 	this->submit = new ELEMENTS::Button(HELPER::Coordinate(1455, 855), 150, 40);
	// 	this->submit->SetPlaceholder("SUBMIT");

	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ho);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ten);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	// 	DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
	// }

	// NewListItemForm::~NewListItemForm() {
	// 	delete this->background;
	// 	delete this->title;
	// 	delete this->maThe;
	// 	delete this->ho;
	// 	delete this->ten;
	// 	delete this->phai;
	// 	delete this->submit;
	// }

	// void NewListItemForm::Display() {
	// 	this->background->Draw();
	// 	this->title->Display();
	// 	this->maThe->Display();
	// 	this->ho->Display();
	// 	this->ten->Display();
	// 	this->phai->Display();
	// 	this->submit->Display();
	// }

	// bool NewListItemForm::SubmitForm(LINEAR_LIST::LinearList& dsDauSach, ELEMENTS::InputModeController& InputController) {
	// 	ELEMENTS::Button* formInputField[3] = { this->ho, this->ten, this->phai };
	// 	int fieldCharacterLimit[3] = { 30, 15, 3 };

	// 	int nextIndex = THE_DOC_GIA_MODULES::GetIndex(CONSTANTS::THE_DOC_GIA_INDEX, dsTheDocGia);
	// 	this->maThe->SetPlaceholder(std::to_string(nextIndex));

	// 	for (int i = 0; i < 3; ++i) {
	// 		if (formInputField[i]->IsPointed() && formInputField[i]->LeftMouseClicked() == false) {
	// 			DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(formInputField[i]);
	// 		}
	// 		else if (formInputField[i]->LeftMouseClicked()) {
	// 			InputController.Activate(formInputField[i], formInputField[i], fieldCharacterLimit[i], true, false, true);
	// 		}
	// 		else {
	// 			DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(formInputField[i]);
	// 		}
	// 	}

	// 	if (this->submit->IsHover()) {
	// 		DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->submit);
	// 	}
	// 	else if (this->submit->LeftMouseClicked()) {
	// 		THE_DOC_GIA::TheDocGia newItem;

	// 		newItem.SetMaThe(nextIndex);
	// 		newItem.SetHo(STR::Trim(this->ho->GetPlaceholder()));
	// 		newItem.SetTen(STR::Trim(this->ten->GetPlaceholder()));
	// 		newItem.SetPhai(this->phai->GetPlaceholder() == "NAM" ? THE_DOC_GIA::GioiTinh::NAM : THE_DOC_GIA::GioiTinh::NU);
	// 		newItem.SetTrangThai(THE_DOC_GIA::TrangThaiThe::THE_HOAT_DONG);
	// 		newItem.SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler());
	// 		delay(100);

	// 		bool res = AVL_TREE::Insert(dsTheDocGia, newItem);

	// 		return true;
	// 	}
	// 	else {
	// 		DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
	// 	}

	// 	return false;
	// }
}



void DanhSachDauSachView::CreateDatasheetsFromList(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler) {

	int recordCount = danhSachDauSach.numberOfNode;
	controler.datasheetCount = recordCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (recordCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1);
	controler.sheets = new DATASHEET::Datasheet[controler.datasheetCount];
	controler.activeSheet = 0;

	for (int i = 0; i < controler.datasheetCount; ++i) {
		controler.sheets[i] = DATASHEET::Datasheet(
			controler.rowCount, controler.columnCount, controler.rowHeight, controler.topLeft,
			(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, (int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
		);
	}

	int rowIndicator = 0;
	int sheetIndicator = -1;

	for (int i = 0; i < danhSachDauSach.numberOfNode; ++i) {
		++rowIndicator;
		if (rowIndicator % CONSTANTS::MAX_ROW_COUNT == 1) {
			++sheetIndicator;
		}

		std::string* data = new std::string[controler.columnCount];
		data[0] = std::to_string(rowIndicator);
		data[1] = danhSachDauSach.nodes[i]->GetISBN();
		data[2] = danhSachDauSach.nodes[i]->GetTenSach();
		data[3] = std::to_string(danhSachDauSach.nodes[i]->GetSoTrang());
		data[4] = danhSachDauSach.nodes[i]->GetTacGia();
		data[5] = std::to_string(danhSachDauSach.nodes[i]->GetNamXuatBan());
		data[6] = danhSachDauSach.nodes[i]->GetTheLoai();
		data[7] = "DANH MUC SACH";

		controler.sheets[sheetIndicator].UpdateNewPlaceholder(data, rowIndicator % CONSTANTS::MAX_ROW_COUNT);
	}
	
}

void DanhSachDauSachView::DatasheetChangeBTNHover(Button& btn) {
	btn.SetFillColor(rgb(130, 170, 227));
}

void DanhSachDauSachView::DatasheetChangeBTNProperties(Button& btn) {
	btn.SetFillColor(rgb(236, 242, 255));
	btn.SetBorderColor(rgb(25, 24, 37));
	btn.SetTextColor(rgb(25, 24, 37));
}

DanhSachDauSachView::DanhSachDauSachView(LINEAR_LIST::LinearList& danhSachDauSach) {
	this->active = false;
	this->displaDatasheet = true;

	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 940);
	HELPER::Coordinate toRightBtnTopLeft(86, 940);

	this->controler = DATASHEET::Controler(
		CONSTANTS::MAX_ROW_COUNT, DAU_SACH_PROPERTIES::PROPERTIES_COUNT, DAU_SACH_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheetsFromList(danhSachDauSach, controler);

	this->sheetChange[0] = Button(toLeftBtnTopLeft, 50, 30);
	this->sheetChange[1] = Button(toRightBtnTopLeft, 50, 30);
	this->sheetChange[0].SetPlaceholder("<");
	this->sheetChange[1].SetPlaceholder(">");
	for (int i = 0; i < 2; ++i) {
		this->DatasheetChangeBTNProperties(this->sheetChange[i]);
	}

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

void DanhSachDauSachView::Run() {

	//* Displaying all the items
	if (this->displaDatasheet) {
		this->controler.Display();
	}

	for (int i = 0; i < 2; ++i) {
		this->sheetChange[i].Display();
	}

	for (int i = 0; i < 3; ++i) {
		this->listManipulateButtons[i].Display();
	}

	this->searchField.Display();

	//---

	//* Elements changes logic
	for (int i = 0; i < 2; ++i) {
		if (this->sheetChange[i].IsPointed() && this->sheetChange[i].LeftMouseClicked() == false) {
			this->DatasheetChangeBTNHover(this->sheetChange[i]);
		}
		else if (this->sheetChange[i].LeftMouseClicked()) {
			
			if (i == 0) {
				if (this->controler.activeSheet == 0) {
					this->controler.activeSheet = this->controler.datasheetCount - 1;
				}
				else {
					--this->controler.activeSheet;
				}
			}
			else {
				if (this->controler.activeSheet == this->controler.datasheetCount - 1) {
					this->controler.activeSheet = 0;
				}
				else {
					++this->controler.activeSheet;
				}
			}
			delay(100);
		}
		else {
			this->DatasheetChangeBTNProperties(this->sheetChange[i]);
		}
	}

	//* List manipulate button logic
	for (int i = 0; i < 3; ++i) {
		Button& currentBtn = this->listManipulateButtons[i];
		
		std::cerr << currentBtn.NotYetClicked() << "\n";

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
