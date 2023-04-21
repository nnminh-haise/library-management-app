#include "DanhSachDauSachView.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


namespace DAU_SACH_TAB {

	/*
	 * Function creates datasheet form the given list
	! This function need to be rewrite!
	*/
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* dsDauSach, DATASHEET::Controller& controler) {
		int attributeCount = dsDauSach->numberOfNode;
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

		for (int i = 0; i < dsDauSach->numberOfNode; ++i) {

			++recordIndex;
			if (recordIndex > controler.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (controler.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[controler.GetAttributeCount()];
			data[0] = std::to_string(i + 1);
			data[1] = dsDauSach->nodes[i]->GetISBN();
			data[2] = dsDauSach->nodes[i]->GetTenSach();
			data[3] = std::to_string(dsDauSach->nodes[i]->GetSoTrang());
			data[4] = dsDauSach->nodes[i]->GetTacGia();
			data[5] = std::to_string(dsDauSach->nodes[i]->GetNamXuatBan());
			data[6] = dsDauSach->nodes[i]->GetTheLoai();
			data[7] = "DANH MUC SACH";

			controler[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	/**
	* Search field
	*/
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

	/**
	* Sach add filed constructor
	*/
	SachAddField::SachAddField() {
		this->onDisplay = false;

		this->background = HELPER::Fill(
			HELPER::Coordinate(670, 121), 300, 617,
			rgb(238, 238, 238), rgb(24, 18, 43)
		);

		this->title = Button(HELPER::Coordinate(670, 121), 300, 50);
		this->title.SetPlaceholder("SACH");
		this->title.SetFillColor(rgb(87, 108, 188));
		this->title.SetBorderColor(rgb(24, 18, 43));
		this->title.SetTextColor(rgb(239, 245, 245));

		HELPER::Coordinate inputFieldCoordinates[5] = {
			HELPER::Coordinate(695, 194),
			HELPER::Coordinate(695, 277),
			HELPER::Coordinate(695, 420),
			HELPER::Coordinate(695, 503),
			HELPER::Coordinate(695, 586)
		};
		std::string inputFiledPlaceholders[5] = {
			"Ma sach", "Trang thai", "Vi tri hang", "Vi tri cot", "Vi tri tu"
		};
		for (int i = 0; i < 5; ++i) {
			this->inputField[i] = Button(inputFieldCoordinates[i], 250, 60);
			this->inputField[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField[i].SetFillColor(rgb(255, 251, 245));
			this->inputField[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField[i].SetTextColor(rgb(24, 18, 43));
		}

		this->savebtn = Button(
			HELPER::Coordinate(745, 672), 150, 40,
			rgb(24, 18, 43), rgb(145, 216, 228), rgb(24, 18, 43)
		);
		this->savebtn.SetPlaceholder("SAVE");
	}

	void SachAddField::Display() {
		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 5; ++i) {
			this->inputField[i].Display();
		}
		this->savebtn.Display();
	}

	/**
	* Sach add field controller constructor
	*/
	SachAddFieldController::SachAddFieldController() {
		this->items = nullptr;
		this->activeField = -1;
		this->itemsCount = 0;

		HELPER::Coordinate buttonCoordinates[] = {
			HELPER::Coordinate(670, 756),
			HELPER::Coordinate(720, 756)
		};
		std::string placeholder[] = { "<", ">" };

		for (int i = 0; i < 2; ++i) {
			this->indexChangeButtons[i] = Button(buttonCoordinates[i], 50, 30);
			this->indexChangeButtons[i].SetPlaceholder(placeholder[i]);
			this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			this->indexChangeButtons[i].SetBorderColor(rgb(24, 18, 43));
			this->indexChangeButtons[i].SetTextColor(rgb(24, 18, 43));
		}
	}

	SachAddFieldController::~SachAddFieldController() {
		delete[this->itemsCount] this->items;
	}

	void SachAddFieldController::Initialize(int amount, std::string ISBN) {
		this->itemsCount = amount;
		this->items = new DAU_SACH_TAB::SachAddField[amount];
		this->activeField = 0;

		for (int i = 1; i <= amount; ++i) {
			this->items[i - 1].inputField[0].SetPlaceholder(ISBN + std::to_string(i));
			this->items[i - 1].inputField[1].SetPlaceholder("CHO MUON DUOC");
		}
	}

	void SachAddFieldController::SachAddFieldOnUpdate(LINEAR_LIST::LinearList& dsDauSach, ELEMENTS::InputModeController& InputController) {
		for (int i = 0; i < 5; ++i) {
			if (this->items[this->activeField].inputField[i].IsHover()) {
				this->items[this->activeField].inputField[i].SetFillColor(rgb(233, 248, 249));
				this->items[this->activeField].inputField[i].SetBorderColor(rgb(83, 127, 231));
			}
			else if (this->items[this->activeField].inputField[i].LeftMouseClicked()) {

			}
			else {
				this->items[this->activeField].inputField[i].SetFillColor(rgb(255, 251, 245));
				this->items[this->activeField].inputField[i].SetBorderColor(rgb(24, 18, 43));
			}
		}

	}

	void SachAddFieldController::IndexChangeButtonOnAction() {
		int movement[2] = { -1, +1 };
		for (int i = 0; i < 2; ++i) {
			if (this->indexChangeButtons[i].IsHover()) {
				this->indexChangeButtons[i].SetFillColor(rgb(130, 170, 227));
			}
			else if (this->indexChangeButtons[i].LeftMouseClicked()) {
				this->activeField = (this->activeField + movement[i] + this->itemsCount) % this->itemsCount;
				delay(100);
			}
			else {
				this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			}
		}
	}

	void SachAddFieldController::Display() {
		this->items[this->activeField].Display();

		for (int i = 0; i < 2; ++i) {
			this->indexChangeButtons[i].Display();
		}
	}

	/**
	* Add new item to list
	*/
	ItemAddField::ItemAddField() {
		this->onDisplay = false;
		this->sachAddFieldDisplay = false;

		this->background = HELPER::Fill(
			HELPER::Coordinate(36, 121), 600, 730,
			rgb(238, 238, 238), rgb(24, 18, 43)
		);

		this->title = Button(HELPER::Coordinate(36, 120), 600, 50);
		this->title.SetPlaceholder("DAU SACH");
		this->title.SetFillColor(rgb(87, 108, 188));
		this->title.SetBorderColor(rgb(24, 18, 43));
		this->title.SetTextColor(rgb(239, 245, 245));

		HELPER::Coordinate inputFieldCoordinates[7] = {
			HELPER::Coordinate(61, 194),
			HELPER::Coordinate(61, 277),
			HELPER::Coordinate(61, 360),
			HELPER::Coordinate(61, 443),
			HELPER::Coordinate(61, 526),
			HELPER::Coordinate(61, 609),
			HELPER::Coordinate(61, 692)
		};
		std::string inputFiledPlaceholders[7] = {
			"ISBN", "Ten sach", "So trang", "Tac gia", "Nam xuat ban", "The loai", "Kich thuoc danh muc sach"
		};
		for (int i = 0; i < 7; ++i) {
			this->inputField[i] = Button(inputFieldCoordinates[i], 550, 60);
			this->inputField[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField[i].SetFillColor(rgb(255, 251, 245));
			this->inputField[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField[i].SetTextColor(rgb(24, 18, 43));
		}

		this->submit = Button(
			HELPER::Coordinate(261, 786), 150, 40,
			rgb(24, 18, 43), rgb(145, 216, 228), rgb(24, 18, 43)
		);
		this->submit.SetPlaceholder("ADD");

		this->goBackButton = Button(
			HELPER::Coordinate(36, 921), 70, 50,
			rgb(24, 18, 43), rgb(236, 242, 255), rgb(24, 18, 43)
		);
		this->goBackButton.SetPlaceholder("<");
	}

	bool ItemAddField::ItemAddFieldOnUpdate(LINEAR_LIST::LinearList& dsDauSach, ELEMENTS::InputModeController& InputController) {
		for (int i = 0; i < 7; ++i) {
			if (this->inputField[i].IsHover()) {
				this->inputField[i].SetBorderColor(rgb(83, 127, 231));
				this->inputField[i].SetFillColor(rgb(233, 248, 249));
			}
			else if (this->inputField[i].LeftMouseClicked()) {
				delay(100);
				switch (i) {
					case (0):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 4, true, false, false);
						break;
					case (1):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 50, true, true, true);
						break;
					case (2):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 4, false, true, false);
						break;
					case (3):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 50, true, false, true);
						break;
					case (4):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 4, false, true, false);
						break;
					case (5):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 30, true, false, true);
						break;
					case (6):
						InputController.Activate(&this->inputField[i], &this->inputField[i], 5, false, true, false);
						break;
				}
			}
			else {
				this->inputField[i].SetFillColor(rgb(255, 251, 245));
				this->inputField[i].SetBorderColor(rgb(24, 18, 43));
			}
		}

		if (this->submit.IsHover()) {
			this->submit.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->submit.LeftMouseClicked()) {
			delay(100);
			DAU_SACH::DauSach* newDauSach = new DAU_SACH::DauSach;

			newDauSach->SetISBN(this->inputField[0].GetPlaceholder());
			newDauSach->SetTenSach(this->inputField[1].GetPlaceholder());
			newDauSach->SetSoTrang(std::stoi(this->inputField[2].GetPlaceholder()));
			newDauSach->SetTacGia(this->inputField[3].GetPlaceholder());
			newDauSach->SetNamXuatBan(std::stoi(this->inputField[4].GetPlaceholder()));
			newDauSach->SetTheLoai(this->inputField[5].GetPlaceholder());

			if (VALIDATOR::OnlyDigit(this->inputField[6].GetPlaceholder()) && std::stoi(this->inputField[6].GetPlaceholder()) > 0) {
				this->sachAddFieldDisplay = true;
				this->sachAddFieldController.Initialize(std::stoi(this->inputField[6].GetPlaceholder()), this->inputField[0].GetPlaceholder());
			}
			else if (std::stoi(this->inputField[6].GetPlaceholder()) == 0) {
				newDauSach->SetDanhMucSach(LINKED_LIST::Controller());
			}
			else {
				std::cerr << std::format("[ERROR] Thong tin cua truong \"kich thuoc danh muc sach phai la so nguyen khong am\"\n");
				exit(1);
			}

			LINEAR_LIST::InsertOrder(dsDauSach, newDauSach);
			return true;
		}
		else {
			this->submit.SetFillColor(rgb(145, 216, 228));
		}
		return false;
	}

	void ItemAddField::Display(LINEAR_LIST::LinearList& dsDauSach, ELEMENTS::InputModeController& InputController) {
		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 7; ++i) {
			this->inputField[i].Display();
		}
		this->submit.Display();
		this->goBackButton.Display();

		if (this->sachAddFieldDisplay) {
			this->sachAddFieldController.Display();
			this->sachAddFieldController.IndexChangeButtonOnAction();
			this->sachAddFieldController.SachAddFieldOnUpdate(dsDauSach, InputController);
		}
	}

	bool ItemAddField::GoBackButtonOnAction() {
		if (this->goBackButton.IsHover()) {
			this->goBackButton.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackButton.LeftMouseClicked()) {
			this->onDisplay = false;
			return true;
		}
		else {
			this->goBackButton.SetFillColor(rgb(236, 242, 255)
			);
		}
		return false;
	}
}

/*
* DauSachTab constructor
*/

DauSachTab::DauSachTab(LINEAR_LIST::LinearList* dsDauSach, ELEMENTS::InputModeController* inputController) {

	//* Initialize data
	this->dsDauSach = dsDauSach;
	this->inputController = inputController;
	this->datasheetDisplayFlag = true;
	this->active = false;
	this->datasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT, 
		DAU_SACH_PROPERTIES::PROPERTIES_COUNT, 
		DAU_SACH_PROPERTIES::ROW_HEIGHT, 
		HELPER::Coordinate(36, 120)
	);

	//* Create datasheet form the list
	DAU_SACH_TAB::CreateDatasheetsFromList(this->dsDauSach, this->datasheetController);

	//* Creating Button for adding or editting or removing item of the list
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
	if (this->datasheetDisplayFlag == true) {
		this->datasheetController.Display();
		this->datasheetController.DatasheetChangeButtonUpdate();

		for (int i = 0; i < 3; ++i) {
			this->listManipulateButtons[i].Display();
		}

		this->searchField.Display();
	}

	if (this->itemAddField.onDisplay) {
		this->itemAddField.Display(*this->dsDauSach, *this->inputController);
		this->datasheetDisplayFlag = this->itemAddField.GoBackButtonOnAction();
		bool regenerateDatasheet = this->itemAddField.ItemAddFieldOnUpdate(*this->dsDauSach, *this->inputController);
		if (regenerateDatasheet) {
			DAU_SACH_TAB::CreateDatasheetsFromList(this->dsDauSach, this->datasheetController);
		}
	}

	//* List manipulate button logic
	for (int i = 0; i < 3; ++i) {
		Button& currentBtn = this->listManipulateButtons[i];

		if (currentBtn.IsHover()) {
			DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonHoverProperties(currentBtn);
		}
		else if (currentBtn.LeftMouseClicked()) {
			switch (i) {
				delay(100);
				case (0):
					this->datasheetDisplayFlag = false;
					this->itemAddField.onDisplay = true;
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
