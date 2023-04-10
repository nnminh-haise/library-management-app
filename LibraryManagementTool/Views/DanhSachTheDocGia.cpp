#include "DanhSachTheDocGia.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../TheDocGia/TheDocGia.h"
#include "../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>



void DanhSachTheDocGiaView::CreateDatasheetsFromDatabase(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler& controler) {
	THE_DOC_GIA_MODULES::LoadDanhSachTheDocGiaFromDB(CONSTANTS::THE_DOC_GIA_DB, danhSachThedocGia);

	int recordCount = 0;
	AVL_TREE::CountNode(danhSachThedocGia, recordCount);
	controler.datasheetCount = recordCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (recordCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1);
	controler.sheets = new DATASHEET::Datasheet[controler.datasheetCount];
	controler.activeSheet = 0;

	for (int i = 0; i < controler.datasheetCount; ++i) {
		controler.sheets[i] = DATASHEET::Datasheet(
			controler.rowCount, controler.columnCount, controler.rowHeight, controler.topLeft,
			(std::string*)THE_DOC_GIA_PROPERTIES::LABEL_PLACEHOLDERS, (int*)THE_DOC_GIA_PROPERTIES::CHARACTER_LIMITS
		);
	}

	STACK::Stack stk;
	STACK::Initialize(stk);
	AVL_TREE::Pointer currentNode = danhSachThedocGia;
	int rowIndicator = 0;
	int sheetIndicator = -1;

	do {
		while (currentNode != nullptr) {
			STACK::Push(stk, currentNode);
			currentNode = currentNode->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			currentNode = STACK::Pop(stk);
			
			//* Logic stays here
			++rowIndicator;
			if (rowIndicator % CONSTANTS::MAX_ROW_COUNT == 1) {
				++sheetIndicator;
			}

			std::string* data = new std::string[controler.columnCount];
			data[0] = std::to_string(rowIndicator);
			data[1] = std::to_string(currentNode->info.GetMaThe());
			data[2] = currentNode->info.GetHo();
			data[3] = currentNode->info.GetTen();
			data[4] = currentNode->info.GetStringfyPhai();
			data[5] = currentNode->info.GetStringfyTrangThai();
			data[6] = "SACH DANG MUON";

			controler.sheets[sheetIndicator].UpdateNewPlaceholder(data, rowIndicator % CONSTANTS::MAX_ROW_COUNT);

			//---

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);
}

void DanhSachTheDocGiaView::ListManipulateBTNDefaultProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(219, 223, 253));
	btn.SetBorderColor(btn.GetFillColor());
	btn.SetTextColor(rgb(57, 62, 70));
}

void DanhSachTheDocGiaView::ListManipulateBTNHoverProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(155, 163, 235));
	btn.SetBorderColor(rgb(36, 47, 155));
	btn.SetTextColor(rgb(234, 253, 252));
}

void DanhSachTheDocGiaView::NewItemButtonActiveProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(130, 170, 227));
	btn.SetBorderColor(rgb(57, 62, 70));
	btn.SetTextColor(rgb(57, 62, 70));
}

void DanhSachTheDocGiaView::DatasheetChangeBTNHover(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(130, 170, 227));
}

void DanhSachTheDocGiaView::DatasheetChangeBTNProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(236, 242, 255));
	btn.SetBorderColor(rgb(25, 24, 37));
	btn.SetTextColor(rgb(25, 24, 37));
}

void SearchField::BackgroundStyling() {
	this->background.fillColor = rgb(238, 238, 238);
	this->background.borderColor = BLACK;
}

void SearchField::TitleStyling() {
	this->title.SetFillColor(rgb(87, 108, 188));
	this->title.SetBorderColor(BLACK);
	this->title.SetTextColor(rgb(247, 247, 247));
}

void SearchField::SearchBoxStyling() {
	this->inputSearchBox.SetFillColor(rgb(255, 251, 245));
	this->inputSearchBox.SetBorderColor(BLACK);
	this->inputSearchBox.SetTextColor(rgb(57, 62, 70));
}

void SearchField::StatusBoxStyling() {
	this->searchStatusBox.SetFillColor(rgb(238, 238, 238));
	this->searchStatusBox.SetBorderColor(this->searchStatusBox.GetFillColor());
	this->searchStatusBox.SetTextColor(rgb(57, 62, 70));
}

SearchField::SearchField() {
	this->background = ELEMENTS::Fill(HELPER::Coordinate(1305, 120), 450, 250);
	this->title = ELEMENTS::Button(HELPER::Coordinate(1305, 120), 450, 50);
	this->title.SetPlaceholder("SEARCH");

	this->inputSearchBox = ELEMENTS::Button(HELPER::Coordinate(1330, 200), 400, 70);
	this->inputSearchBox.SetPlaceholder("Type here to search");

	this->searchStatusBox = ELEMENTS::Button(HELPER::Coordinate(1330, 295), 400, 50);
	this->searchStatusBox.SetPlaceholder("Result:");
}

void SearchField::Display() {
	this->BackgroundStyling();
	this->TitleStyling();
	this->SearchBoxStyling();
	this->StatusBoxStyling();

	this->background.Draw();
	this->title.Display();
	this->inputSearchBox.Display();
	this->searchStatusBox.Display();
}

void NewListItemForm::BackgroundStyling() {
	this->background.fillColor = rgb(238, 238, 238);
	this->background.borderColor = BLACK;
}

void NewListItemForm::TitleStyling() {
	this->title.SetFillColor(rgb(87, 108, 188));
	this->title.SetBorderColor(BLACK);
	this->title.SetTextColor(rgb(247, 247, 247));
}

void NewListItemForm::InputBoxStyling(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(255, 251, 245));
	btn.SetBorderColor(BLACK);
	btn.SetTextColor(rgb(57, 62, 70));
}

void NewListItemForm::SubmitButtonStyling() {
	this->submit.SetFillColor(rgb(3, 201, 136));
	this->submit.SetBorderColor(this->submit.GetFillColor());
	this->submit.SetTextColor(rgb(57, 62, 70));
}

void NewListItemForm::InputBoxHoverProperties(ELEMENTS::Button* btn) {
	btn->SetBorderColor(rgb(70, 73, 255));
	btn->SetFillColor(rgb(234, 253, 252));
}

NewListItemForm::NewListItemForm() {
	this->background = ELEMENTS::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = ELEMENTS::Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title.SetPlaceholder("THE DOC GIA");

	this->maThe = ELEMENTS::Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe.SetPlaceholder("Ma the");

	this->ho = ELEMENTS::Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho.SetPlaceholder("Ho");

	this->ten = ELEMENTS::Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten.SetPlaceholder("Ten");

	this->phai = ELEMENTS::Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->phai.SetPlaceholder("Phai");

	this->submit = ELEMENTS::Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->submit.SetPlaceholder("SUBMIT");

	this->BackgroundStyling();
	this->TitleStyling();
	this->InputBoxStyling(this->maThe);
	this->InputBoxStyling(this->ho);
	this->InputBoxStyling(this->ten);
	this->InputBoxStyling(this->phai);
	this->SubmitButtonStyling();
}

void NewListItemForm::Display() {
	this->background.Draw();
	this->title.Display();
	this->maThe.Display();
	this->ho.Display();
	this->ten.Display();
	this->phai.Display();
	this->submit.Display();
}



//* View Constructor
DanhSachTheDocGiaView::DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia) {
	this->active = false;
	
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 935);
	HELPER::Coordinate toRightBtnTopLeft(86, 935);



	this->controler = DATASHEET::Controler(
		CONSTANTS::MAX_ROW_COUNT, THE_DOC_GIA_PROPERTIES::PROPERTIES_COUNT, 
		THE_DOC_GIA_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheetsFromDatabase(danhSachTheDocGia, controler);

	this->sheetChange[0] = ELEMENTS::Button(toLeftBtnTopLeft, 50, 30);
	this->sheetChange[1] = ELEMENTS::Button(toRightBtnTopLeft, 50, 30);
	this->sheetChange[0].SetPlaceholder("<");
	this->sheetChange[1].SetPlaceholder(">");
	for (int i = 0; i < 2; ++i) {
		this->DatasheetChangeBTNProperties(this->sheetChange[i]);
	}

	//* List manipulation buttons
	this->listManipulationButtonStatus = -1;
	std::string listManipulateButtonPlaceholders[] = { "New", "Edit", "Remove" };
	HELPER::Coordinate listManipulateButtonCoordinate[] = {
		HELPER::Coordinate(380, 940),
		HELPER::Coordinate(565, 940),
		HELPER::Coordinate(750, 940)
	};
	for (int i = 0; i < 3; ++i) {
		this->listManipulateButton[i] = ELEMENTS::Button(listManipulateButtonCoordinate[i], 150, 30);
		this->listManipulateButton[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		this->ListManipulateBTNDefaultProperties(this->listManipulateButton[i]);
	}
}



//* View Render
void DanhSachTheDocGiaView::Run(ELEMENTS::InputModeController& InputController) {
	
	//* Display datasheet
	this->controler.Display();
	
	//* Display datasheet page move button
	for (int i = 0; i < 2; ++i) {
		this->sheetChange[i].Display();
	}

	//* Display function button
	for (int i = 0; i < 3; ++i) {
		this->listManipulateButton[i].Display();
	}

	//* Display Search field
	this->searchField.Display();

	//* Detect if there is a function got activated
	if (this->listManipulationButtonStatus != -1) {
		switch (this->listManipulationButtonStatus) {
		case (0): {
			//* Display form
			this->newItemForm.Display();

			ELEMENTS::Button* formInputField[3] = { &this->newItemForm.ho, &this->newItemForm.ten, &this->newItemForm.phai };
			int fieldCharacterLimit[3] = { 30, 15, 3 };

			for (int i = 0; i < 3; ++i) {
				if (formInputField[i]->IsPointed() && formInputField[i]->LeftMouseClicked() == false) {
					this->newItemForm.InputBoxHoverProperties(formInputField[i]);
				}
				else if (formInputField[i]->LeftMouseClicked()) {
					InputController.Activate(formInputField[i], formInputField[i], fieldCharacterLimit[i], true, false, true);
				}
				else {
					this->newItemForm.InputBoxStyling(*formInputField[i]);
				}
			}

			break;
		}
		case (1): {
			break;
		}
		case (2): {
			break;
		}
		}
	}

	//* Sheet's changes button logic
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

		if (this->listManipulateButton[i].IsPointed() && this->listManipulateButton[i].LeftMouseClicked() == false) {
			this->ListManipulateBTNHoverProperties(this->listManipulateButton[i]);
		}
		else if (this->listManipulateButton[i].LeftMouseClicked()) {
			switch (i) {
				case (0): {//* Pressed new button
					this->listManipulationButtonStatus = 0;
					break;
				}
				case (1): {
					this->listManipulationButtonStatus = 1;
					break;
				}
				case (2): {
					this->listManipulationButtonStatus = 2;
					break;
				}
			}

			delay(100);
		}
		else {
			if (i != this->listManipulationButtonStatus) {
				this->ListManipulateBTNDefaultProperties(this->listManipulateButton[i]);
			}
		}
	}
}

//bool NewItemFormInputController::KeyValidation(const char& chr) {
//	if (chr == ' ') {
//		return true;
//	}
//
//	if (isalnum(chr)) {
//		return true;
//	}
//
//	return false;
//}
//
//void NewItemFormInputController::ActionOnKey(const char& chr) {
//	if (chr == ELEMENTS::SpecialKey::ENTER || chr == ELEMENTS::SpecialKey::ESCAPE) {
//		if (this->outputTextBox != nullptr) {
//			this->outputTextBox->SetPlaceholder(this->inputString);
//		}
//		this->Deactivate();
//	}
//	else if (this->inputString.length() == 0 && chr == ' ') {
//		return;
//	}
//	else if (this->inputString.length() != 0 && this->inputString[this->inputString.length() - 1] == ' ' && chr == ' ') {
//		return;
//	}
//	else if (this->inputString.length() == 0 && chr == ELEMENTS::SpecialKey::BACKSPACE) {
//		return;
//	}
//	else if (chr == ELEMENTS::SpecialKey::BACKSPACE) {
//		this->inputString.pop_back();
//		this->characterCount--;
//		this->currentTextBox->SetPlaceholder(this->inputString);
//	}
//	else if (this->characterCount < this->characterLimit && this->KeyValidation(chr)) {
//		this->inputString.push_back(chr);
//		++this->characterCount;
//		this->currentTextBox->SetPlaceholder(this->inputString);
//	}
//}
