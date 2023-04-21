#include "DanhSachTheDocGia.h"
#include "DanhSachTheDocGiaStyling.h"

#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


SearchField::SearchField() {
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 120), 450, 250);
	this->title = new Button(HELPER::Coordinate(1305, 120), 450, 50);
	this->title->SetPlaceholder("SEARCH");

	this->inputSearchBox = new Button(HELPER::Coordinate(1330, 200), 400, 70);
	this->inputSearchBox->SetPlaceholder("Type here to search");

	this->searchStatusBox = new Button(HELPER::Coordinate(1330, 295), 400, 50);
	this->searchStatusBox->SetPlaceholder("Result:");
}

void SearchField::Display() {
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchStatusBox);

	this->background->Draw();
	this->title->Display();
	this->inputSearchBox->Display();
	this->searchStatusBox->Display();
}

NewListItemForm::NewListItemForm() {
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->ho = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho->SetPlaceholder("Ho");

	this->ten = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten->SetPlaceholder("Ten");

	this->phai = new Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->phai->SetPlaceholder("Phai");

	this->submit = new Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->submit->SetPlaceholder("SUBMIT");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ho);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ten);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
}

NewListItemForm::~NewListItemForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->ho;
	delete this->ten;
	delete this->phai;
	delete this->submit;
}

void NewListItemForm::Display() {
	this->background->Draw();
	this->title->Display();
	this->maThe->Display();
	this->ho->Display();
	this->ten->Display();
	this->phai->Display();
	this->submit->Display();
}

bool NewListItemForm::SubmitForm(AVL_TREE::Pointer& dsTheDocGia, ELEMENTS::InputModeController& InputController) {
	Button* formInputField[3] = { this->ho, this->ten, this->phai };
	int fieldCharacterLimit[3] = { 30, 15, 3 };

	int nextIndex = THE_DOC_GIA_MODULES::GetIndex(CONSTANTS::THE_DOC_GIA_INDEX, dsTheDocGia);
	this->maThe->SetPlaceholder(std::to_string(nextIndex));

	for (int i = 0; i < 3; ++i) {
		if (formInputField[i]->IsPointed() && formInputField[i]->LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(formInputField[i]);
		}
		else if (formInputField[i]->LeftMouseClicked()) {
			InputController.Activate(formInputField[i], formInputField[i], fieldCharacterLimit[i], true, false, true);
		}
		else {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(formInputField[i]);
		}
	}

	if (this->submit->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->submit);
	}
	else if (this->submit->LeftMouseClicked()) {
		THE_DOC_GIA::TheDocGia newItem;

		newItem.SetMaThe(nextIndex);
		newItem.SetHo(STR::Trim(this->ho->GetPlaceholder()));
		newItem.SetTen(STR::Trim(this->ten->GetPlaceholder()));
		newItem.SetPhai(this->phai->GetPlaceholder() == "NAM" ? THE_DOC_GIA::GioiTinh::NAM : THE_DOC_GIA::GioiTinh::NU);
		newItem.SetTrangThai(THE_DOC_GIA::TrangThaiThe::THE_HOAT_DONG);
		newItem.SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controller());
		delay(100);

		bool res = AVL_TREE::Insert(dsTheDocGia, newItem);

		return true;
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
	}

	return false;
}

DeleteItemInListForm::DeleteItemInListForm() {
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->hoTen = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->hoTen->SetPlaceholder("Ho va ten");

	this->phai = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->phai->SetPlaceholder("Phai");

	this->trangThai = new Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->trangThai->SetPlaceholder("Trang thai");

	this->deleteBtn = new Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->deleteBtn->SetPlaceholder("DELETE");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->hoTen);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->trangThai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->deleteBtn);
	this->searchTargetFound = false;
	this->searchResult = nullptr;
}

DeleteItemInListForm::~DeleteItemInListForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->hoTen;
	delete this->trangThai;
	delete this->phai;
	delete this->deleteBtn;
}

void DeleteItemInListForm::Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	this->searchTargetFound = false;
	this->background->Draw();
	this->title->Display();
	this->maThe->Display();

	//* MaThe input box logic
	if (this->maThe->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	}
	else if (this->maThe->LeftMouseClicked()) {
		InputController.Activate(this->maThe, this->maThe, 4, false, true, false);
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(this->maThe);
	}

	bool checker = VALIDATOR::OnlyDigit(this->maThe->GetPlaceholder());
	if (checker) {
		this->searchResult = AVL_TREE::SearchByKey(danhSachTheDocGia, std::stoi(this->maThe->GetPlaceholder()));
		if (this->searchResult != nullptr) {
			int currentBorrowedBooksCount = MUON_TRA_MODULES::CountBorrowedBooks(this->searchResult->info.GetDanhSachMuonTra());
			if (currentBorrowedBooksCount != 0) {
				std::cerr << std::format("[ERROR] DOC GIA DANG MUON SACH! KHONG THE XOA DOC GIA!\n");
			}
			else {
				this->searchTargetFound = true;
			}

			this->hoTen->SetPlaceholder(this->searchResult->info.GetFullName());
			this->phai->SetPlaceholder(this->searchResult->info.GetStringfyPhai());
			this->trangThai->SetPlaceholder(this->searchResult->info.GetStringfyTrangThai());

			this->hoTen->Display();
			this->phai->Display();
			this->trangThai->Display();
			this->deleteBtn->Display();
		}
		else {
			std::cerr << std::format("[ERROR] MA THE IS NOT EXIST!\n");
		}
	}
	else {
		std::cerr << std::format("[ERROR] INVALID SEARCH DATA!\n");
	}
}

bool DeleteItemInListForm::SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {

	//* Submit button
	if (this->deleteBtn->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->deleteBtn);
	}
	else if (this->deleteBtn->LeftMouseClicked()) {
		if (this->searchTargetFound == true) {
			danhSachTheDocGia = AVL_TREE::RemoveNode(danhSachTheDocGia, this->searchResult->GetKey());
			std::cerr << std::format("[INFO] XOA THE DOC GIA THANH CONG!\n");
			return true;
		}
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->deleteBtn);
	}

	return false;
}

EditItemInListForm::EditItemInListForm() {
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->ho = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho->SetPlaceholder("Ho");

	this->ten = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten->SetPlaceholder("Ten");

	this->phai = new Button(HELPER::Coordinate(1330, 770), 145, 60);
	this->phai->SetPlaceholder("Phai");

	this->trangThai = new Button(HELPER::Coordinate(1500, 770), 230, 60);
	this->trangThai->SetPlaceholder("Trang thai");

	this->saveBtn = new Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->saveBtn->SetPlaceholder("SAVE");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ho);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ten);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->trangThai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->saveBtn);
	this->searchTargetFound = false;
	this->searchResult = nullptr;
}

EditItemInListForm::~EditItemInListForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->ho;
	delete this->ten;
	delete this->trangThai;
	delete this->phai;
	delete this->saveBtn;
}

void EditItemInListForm::Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	this->searchTargetFound = false;

	this->background->Draw();
	this->title->Display();
	this->maThe->Display();

	if (this->maThe->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(this->maThe);
	}
	else if (this->maThe->LeftMouseClicked()) {
		InputController.Activate(this->maThe, this->maThe, 4, false, true, false);
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	}
}

bool EditItemInListForm::SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {

	this->searchTargetFound = false;

	bool checker = VALIDATOR::OnlyDigit(this->maThe->GetPlaceholder());
	if (checker) {
		this->searchResult = AVL_TREE::SearchByKey(danhSachTheDocGia, std::stoi(this->maThe->GetPlaceholder()));
		if (this->searchResult != nullptr) {
			this->searchTargetFound = true;

			this->ho->Display();
			this->ten->Display();
			this->phai->Display();
			this->trangThai->Display();
			this->saveBtn->Display();

			Button* inpField[4] = {
				this->ho, this->ten, this->phai, this->trangThai
			};

			for (int i = 0; i < 4; ++i) {
				if (inpField[i]->IsHover()) {
					DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(inpField[i]);
				}
				else if (inpField[i]->LeftMouseClicked()) {
					switch (i) {
					case (0):
						InputController.Activate(inpField[i], inpField[i], 30, true, false, true);
						break;
					case (1):
						InputController.Activate(inpField[i], inpField[i], 15, true, false, true);
						break;
					case (2):
						InputController.Activate(inpField[i], inpField[i], 3, true, false, false);
						break;
					case (3):
						InputController.Activate(inpField[i], inpField[i], 9, true, false, true);
						break;
					}
				}
				else {
					DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(inpField[i]);
				}
			}
		}
		else {
			std::cerr << std::format("[ERROR] MA THE IS NOT EXIST!\n");
		}
	}
	else {
		std::cerr << std::format("[ERROR] INVALID SEARCH DATA!\n");
	}

	//* Submit button
	if (this->saveBtn->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->saveBtn);
	}
	else if (this->saveBtn->LeftMouseClicked()) {
		if (this->searchTargetFound == true) {

			bool checker = true;

			if (this->phai->GetPlaceholder() != "NAM" && this->phai->GetPlaceholder() != "NU") {
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG PHAI\n");
				checker = false;
			}

			if (this->trangThai->GetPlaceholder() != "HOAT DONG" && this->trangThai->GetPlaceholder() != "BI KHOA") {
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG TRANG THAI\n");
				checker = false;
			}

			if (checker) {
				this->searchResult->info.SetHo(this->ho->GetPlaceholder());
				this->searchResult->info.SetTen(this->ten->GetPlaceholder());
				this->searchResult->info.SetPhai(
					this->phai->GetPlaceholder() == "NAM" ? THE_DOC_GIA::GioiTinh::NAM : THE_DOC_GIA::GioiTinh::NU
				);
				this->searchResult->info.SetTrangThai(
					this->trangThai->GetPlaceholder() == "BI KHOA" ? THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA : THE_DOC_GIA::TrangThaiThe::THE_HOAT_DONG
				);

				return true;
			}
		}
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->saveBtn);
	}

	return false;
}

void DanhSachTheDocGiaView::CreateDatasheetsFromList(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controller* datasheetController) {

	int attributeCount = 0;
	AVL_TREE::CountNode(danhSachThedocGia, attributeCount);
	datasheetController->SetDatasheetCount(
		attributeCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (attributeCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
	);
	datasheetController->InitializeDatasheets();

	for (int i = 0; i < datasheetController->GetDatasheetCount(); ++i) {
		(*datasheetController)[i] = DATASHEET::Datasheet(
			datasheetController->GetRecordCount(),
			datasheetController->GetAttributeCount(),
			datasheetController->GetRowHeight(),
			datasheetController->GetTopLeft(),
			(std::string*)THE_DOC_GIA_PROPERTIES::LABEL_PLACEHOLDERS, (int*)THE_DOC_GIA_PROPERTIES::CHARACTER_LIMITS
		);
	}

	STACK::Stack stk;
	STACK::Initialize(stk);
	AVL_TREE::Pointer currentNode = danhSachThedocGia;
	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	do {
		while (currentNode != nullptr) {
			STACK::Push(stk, currentNode);
			currentNode = currentNode->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			currentNode = STACK::Pop(stk);
			
			//* Logic stays here
			++recordIndex;
			if (recordIndex > datasheetController->GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (datasheetController->GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[datasheetController->GetAttributeCount()];
			data[0] = std::to_string(++order);
			data[1] = std::to_string(currentNode->info.GetMaThe());
			data[2] = currentNode->info.GetHo();
			data[3] = currentNode->info.GetTen();
			data[4] = currentNode->info.GetStringfyPhai();
			data[5] = currentNode->info.GetStringfyTrangThai();
			data[6] = "SACH DANG MUON";

			(*datasheetController)[sheetIndex].UpdateNewPlaceholder(data, recordIndex);

			//---

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);
}

void DanhSachTheDocGiaView::CreateDatasheetsFromArr(AVL_TREE::Pointer* arr, int arrSize, DATASHEET::Controller* datasheetController) {
	datasheetController->SetDatasheetCount(
		arrSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (arrSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
	);
	datasheetController->InitializeDatasheets();

	for (int i = 0; i < datasheetController->GetDatasheetCount(); ++i) {
		(*datasheetController)[i] = DATASHEET::Datasheet(
			datasheetController->GetRecordCount(),
			datasheetController->GetAttributeCount(),
			datasheetController->GetRowHeight(),
			datasheetController->GetTopLeft(),
			(std::string*)THE_DOC_GIA_PROPERTIES::LABEL_PLACEHOLDERS, (int*)THE_DOC_GIA_PROPERTIES::CHARACTER_LIMITS
		);
	}

	int recordIndex = 0;
	int sheetIndex = -1;

	for (int i = 0; i < arrSize; ++i) {

		//* Logic stays here
		++recordIndex;
		if (recordIndex > datasheetController->GetRecordCount() - 1) {
			recordIndex = 1;
		}
		if (recordIndex % (datasheetController->GetRecordCount() - 1) == 1) {
			sheetIndex += 1;
		}

		std::string* data = new std::string[datasheetController->GetAttributeCount()];
		data[0] = std::to_string(i + 1);
		data[1] = std::to_string(arr[i]->info.GetMaThe());
		data[2] = arr[i]->info.GetHo();
		data[3] = arr[i]->info.GetTen();
		data[4] = arr[i]->info.GetStringfyPhai();
		data[5] = arr[i]->info.GetStringfyTrangThai();
		data[6] = "SACH DANG MUON";

		(*datasheetController)[sheetIndex].UpdateNewPlaceholder(data, recordIndex);

		//---
	}

}

/**
* Tab's constructor
* 
* All the code in this method only run once in the program runtime!
*/
DanhSachTheDocGiaView::DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia) {
	this->active = false;
	this->defaultOrder = true;
	
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 935);
	HELPER::Coordinate toRightBtnTopLeft(86, 935);

	this->datasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT, THE_DOC_GIA_PROPERTIES::PROPERTIES_COUNT, 
		THE_DOC_GIA_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	if (this->defaultOrder) {
		this->CreateDatasheetsFromList(danhSachTheDocGia, &this->datasheetController);
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
		this->listManipulateButton[i] = Button(listManipulateButtonCoordinate[i], 150, 30);
		this->listManipulateButton[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonDefaultProperties(this->listManipulateButton[i]);
	}
}

/**
* Tab's frame logic.
* 
* Code in this method will be run many time.
* Each time the program render a frame, this code will be run once, therefore the element's logic will be in here!
*/
void DanhSachTheDocGiaView::Run(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	
	//* Display datasheet
	this->datasheetController.Display();
	this->datasheetController.DatasheetChangeButtonUpdate();

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
				bool formSubmitted = this->newItemForm.SubmitForm(danhSachTheDocGia, InputController);
				if (formSubmitted) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(danhSachTheDocGia, &this->datasheetController);
				}
				break;
			}
			case (1): {
				this->editItemForm.Display(danhSachTheDocGia, InputController);
				bool confirmSave = this->editItemForm.SubmitForm(danhSachTheDocGia, InputController);
				if (confirmSave) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(danhSachTheDocGia, &this->datasheetController);
				}
				break;
			}
			case (2): {
				this->deleteItemForm.Display(danhSachTheDocGia, InputController);
				bool confirmDelete = this->deleteItemForm.SubmitForm(danhSachTheDocGia, InputController);
				if (confirmDelete) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(danhSachTheDocGia, &this->datasheetController);
				}
				break;
			}
		}
	}

	//* List manipulate button logic
	for (int i = 0; i < 3; ++i) {

		if (this->listManipulateButton[i].IsPointed() && this->listManipulateButton[i].LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonHoverProperties(this->listManipulateButton[i]);
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
				DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonDefaultProperties(this->listManipulateButton[i]);
			}
		}
	}

	//* Mathe label button
	if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1].IsHover()) {
		DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonHoverStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1]);
	}
	else if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1].LeftMouseClicked()) {
		this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1].SetFillColor(RED);
		this->defaultOrder = true;
		this->CreateDatasheetsFromList(danhSachTheDocGia, &this->datasheetController);
	}
	else {
		DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonDefaultStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1]);
	}

	//* Ten label button
	if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3].IsHover()) {
		DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonHoverStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3]);
	}
	else if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3].LeftMouseClicked()) {
		this->defaultOrder = false;
		AVL_TREE::Pointer* pointerArr{};
		int arrSize = 0;
		THE_DOC_GIA_MODULES::SortByName(danhSachTheDocGia, pointerArr, arrSize);

		DanhSachTheDocGiaView::CreateDatasheetsFromArr(pointerArr, arrSize, &this->datasheetController);

		delay(100);
	}
	else {
		DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonDefaultStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3]);
	}
}

