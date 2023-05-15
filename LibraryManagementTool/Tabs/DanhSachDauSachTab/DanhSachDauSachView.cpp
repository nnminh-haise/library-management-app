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
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* titleList, DATASHEET::Controller& controler) {
		int listSize = titleList->numberOfNode;
		controler.SetDatasheetCount(
			listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
		);
		controler.InitializeDatasheets();

		for (int i = 0; i < controler.GetDatasheetCount(); ++i) {
			controler[i] = DATASHEET::Datasheet(
				controler.GetRecordCount(), 
				controler.GetAttributeCount(), 
				controler.GetRowHeight(), 
				controler.GetTopLeft(),
				(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, 
				(int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
			);
		}

		int recordIndex = 0;
		int sheetIndex = -1;

		for (int i = 0; i < titleList->numberOfNode; ++i) {

			++recordIndex;
			if (recordIndex > controler.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (controler.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[controler.GetAttributeCount()];
			data[0] = std::to_string(i + 1);
			data[1] = titleList->nodes[i]->GetISBN();
			data[2] = titleList->nodes[i]->GetTitle();
			data[3] = std::to_string(titleList->nodes[i]->GetPageCount());
			data[4] = titleList->nodes[i]->GetAuthor();
			data[5] = std::to_string(titleList->nodes[i]->GetPublicationYear());
			data[6] = titleList->nodes[i]->GetCategory();		

			controler[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	void CreateDatasheetsWithSortedCategory(BOOK_TITLE::BookTitle** sortedList, int listSize, DATASHEET::Controller& datasheetController) {
		datasheetController.SetDatasheetCount(
			listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
		);
		datasheetController.InitializeDatasheets();

		for (int i = 0; i < datasheetController.GetDatasheetCount(); ++i) {
			datasheetController[i] = DATASHEET::Datasheet(
				datasheetController.GetRecordCount(), 
				datasheetController.GetAttributeCount(), 
				datasheetController.GetRowHeight(),
				datasheetController.GetTopLeft(),
				(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, (int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
			);
		}

		int recordIndex = 0;
		int sheetIndex = -1;

		for (int i = 0; i < listSize; ++i) {

			++recordIndex;
			if (recordIndex > datasheetController.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (datasheetController.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[datasheetController.GetAttributeCount()];
			data[0] = std::to_string(i + 1);
			data[1] = sortedList[i]->GetISBN();
			data[2] = sortedList[i]->GetTitle();
			data[3] = std::to_string(sortedList[i]->GetPageCount());
			data[4] = sortedList[i]->GetAuthor();
			data[5] = std::to_string(sortedList[i]->GetPublicationYear());
			data[6] = sortedList[i]->GetCategory();

			datasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	/**
	* Search field
	*/
	SearchField::SearchField() {
		this->active = false;
		this->searchFound = false;

		this->background = new HELPER::Fill(HELPER::Coordinate(1405, 120), 350, 250);
		this->title = new Button(HELPER::Coordinate(1405, 120), 350, 50);
		this->title->SetPlaceholder("SEARCH");

		this->inputSearchBox = new Button(HELPER::Coordinate(1430, 200), 300, 70);
		this->inputSearchBox->SetPlaceholder("Type here to search");

		this->searchStatusBox = new Button(HELPER::Coordinate(1430, 295), 300, 50);
		this->searchStatusBox->SetPlaceholder("Result: NOT FOUND!");
	}

	void SearchField::Activate() {
		this->active = true;
	}

	void SearchField::Deactivate() {
		this->active = false;
	}

	bool SearchField::DisplayStatus() {
		return this->active;
	}

	void SearchField::OnAction(ELEMENTS::InputModeController* inputController) {
		if (this->inputSearchBox->IsHover()) {
			this->inputSearchBox->SetFillColor(rgb(246, 241, 241));
		}
		else if (this->inputSearchBox->LeftMouseClicked()) {
			this->searchFound = false;
			inputController->Activate(this->inputSearchBox, this->inputSearchBox, 30, true, true, true);
		}
		else {
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
		}
	}

	void SearchField::Display() {
		if (this->active == false) {
			return;
		}

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
	* Book add filed constructor
	*/
	SachAddField::SachAddField() {
		this->active = false;

		this->background = HELPER::Fill(
			HELPER::Coordinate(670, 121), 300, 617,
			rgb(238, 238, 238), rgb(24, 18, 43)
		);

		this->title = Button(HELPER::Coordinate(670, 121), 300, 50);
		this->title.SetPlaceholder("BOOK");
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
		this->savebtn.SetPlaceholder("NEXT");
	}

	void SachAddField::Activate() {
		this->active = true;
	}

	void SachAddField::Deactivate() {
		this->active = false;
	}

	bool SachAddField::DisplayStatus() {
		return this->active;
	}

	void SachAddField::Display() {
		if (this->active == false) {
			return;
		}

		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 5; ++i) {
			this->inputField[i].Display();
		}
		this->savebtn.Display();
	}

	/**
	* Book add field controller constructor
	*/
	SachAddFieldController::SachAddFieldController() {
		this->active = false;
		
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

	void SachAddFieldController::Initialize(int amount, std::string isbn) {
		this->itemsCount = amount;
		this->items = new DAU_SACH_TAB::SachAddField[amount];
		this->activeField = 0;

		for (int i = 1; i <= amount; ++i) {
			this->items[i - 1].inputField[0].SetPlaceholder(isbn + std::to_string(i));
			this->items[i - 1].inputField[1].SetPlaceholder("CHO MUON DUOC");
		}
	}

	void SachAddFieldController::SachAddFieldOnUpdate(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& inputController) {
		if (this->active == false) {
			return;
		}

		for (int i = 2; i < 5; ++i) {
			if (this->items[this->activeField].inputField[i].IsHover()) {
				this->items[this->activeField].inputField[i].SetFillColor(rgb(233, 248, 249));
				this->items[this->activeField].inputField[i].SetBorderColor(rgb(83, 127, 231));
			}
			else if (this->items[this->activeField].inputField[i].LeftMouseClicked()) {
				inputController.Activate(
					&this->items[this->activeField].inputField[i],
					&this->items[this->activeField].inputField[i],
					2, false, true, false
				);
			}
			else {
				this->items[this->activeField].inputField[i].SetFillColor(rgb(255, 251, 245));
				this->items[this->activeField].inputField[i].SetBorderColor(rgb(24, 18, 43));
			}
		}

		if (this->items[this->activeField].savebtn.IsHover()) {
			this->items[this->activeField].savebtn.SetFillColor(rgb(0, 255, 202));
		}
		else if (this->items[this->activeField].savebtn.LeftMouseClicked()){
			delay(100);
			if (this->activeField == this->itemsCount - 1) {
				this->activeField = 0;
				std::cerr << std::format("[INFO] Press Save to save data into the list!\n");
			}
			else {
				this->activeField++;
			}
		}
		else {
			this->items[this->activeField].savebtn.SetFillColor(rgb(145, 216, 228));
		}

	}

	void SachAddFieldController::IndexChangeButtonOnAction() {
		if (this->active == false) {
			return;
		}

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

	void SachAddFieldController::Activate() {
		this->active = true;
	}

	void SachAddFieldController::Deactivate() {
		this->active = false;
	}

	bool SachAddFieldController::DisplayStatus() {
		return this->active;
	}

	void SachAddFieldController::Display() {
		if (this->active == false) {
			return;
		}
		
		this->items[this->activeField].Activate();
		this->items[this->activeField].Display();

		for (int i = 0; i < 2; ++i) {
			this->indexChangeButtons[i].Display();
		}
	}

	/**
	* Add new item to list
	*/
	ItemAddField::ItemAddField() {
		this->active = false;
		this->sachAddFieldDisplay = false;

		this->background = HELPER::Fill(
			HELPER::Coordinate(36, 121), 600, 700,
			rgb(238, 238, 238), rgb(24, 18, 43)
		);

		this->backdrop = HELPER::Fill(
			HELPER::Coordinate(36, 121), 934, 800,
			rgb(216, 216, 216), rgb(24, 24, 35)
		);

		this->title = Button(HELPER::Coordinate(36, 120), 600, 50);
		this->title.SetPlaceholder("DAU BOOK");
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
			"isbn", "lastName sach", "So trang", "Tac gia", "Nam xuat ban", "The loai", "Kich thuoc danh muc sach"
		};
		for (int i = 0; i < 7; ++i) {
			this->inputField[i] = Button(inputFieldCoordinates[i], 550, 60);
			this->inputField[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField[i].SetFillColor(rgb(255, 251, 245));
			this->inputField[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField[i].SetTextColor(rgb(24, 18, 43));
		}

		this->createDanhMucSach = Button(
			HELPER::Coordinate(261, 766), 150, 40,
			rgb(24, 18, 43), rgb(145, 216, 228), rgb(24, 18, 43)
		);
		this->createDanhMucSach.SetPlaceholder("Create book list");

		this->submit = Button(
			HELPER::Coordinate(428, 842), 250, 60,
			rgb(24, 18, 43), rgb(145, 216, 228), rgb(24, 18, 43)
		);
		this->submit.SetPlaceholder("CREATE BOOK_TITLE");

		this->goBackButton = Button(
			HELPER::Coordinate(36, 942), 70, 40,
			rgb(24, 18, 43), rgb(236, 242, 255), rgb(24, 18, 43)
		);
		this->goBackButton.SetPlaceholder("<");
	}

	bool ItemAddField::ItemAddFieldOnUpdate(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController) {
		if (this->active == false) {
			return false;
		}

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

		if (this->createDanhMucSach.IsHover()) {
			this->createDanhMucSach.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->createDanhMucSach.LeftMouseClicked()) {
			delay(100);

			if (VALIDATOR::OnlyDigit(this->inputField[6].GetPlaceholder()) && std::stoi(this->inputField[6].GetPlaceholder()) > 0) {
				this->sachAddFieldController.Activate();
				this->sachAddFieldController.Initialize(std::stoi(this->inputField[6].GetPlaceholder()), this->inputField[0].GetPlaceholder());
			}
			else {
				std::cerr << std::format("[ERROR] Thong tin cua truong \"kich thuoc danh muc sach readerSexButton la so nguyen khong am\"\n");
				exit(1);
			}
		}
		else {
			this->createDanhMucSach.SetFillColor(rgb(145, 216, 228));
		}

		if (this->submit.IsHover()) {
			this->submit.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->submit.LeftMouseClicked()) {
			delay(100);
			BOOK_TITLE::BookTitle* newTitle = new BOOK_TITLE::BookTitle;

			newTitle->SetISBN(this->inputField[0].GetPlaceholder());
			newTitle->SetTitle(this->inputField[1].GetPlaceholder());
			newTitle->SetPageCount(std::stoi(this->inputField[2].GetPlaceholder()));
			newTitle->SetAuthor(this->inputField[3].GetPlaceholder());
			newTitle->SetPublicationYear(std::stoi(this->inputField[4].GetPlaceholder()));
			newTitle->SetCategory(this->inputField[5].GetPlaceholder());

			if (std::stoi(this->inputField[6].GetPlaceholder()) == 0) {
				newTitle->SetCatalogue(LINKED_LIST::Controller());
			}
			else {
				LINKED_LIST::Controller newBookList;
				LINKED_LIST::Initialize(newBookList);
				for (int i = 0; i < this->sachAddFieldController.itemsCount; ++i) {
					BOOK::Book newBook;
					newBook.SetID(this->sachAddFieldController.items[i].inputField[0].GetPlaceholder());
					newBook.SetStatus(BOOK::Status::AVAILABLE);
					newBook.SetDescription(std::format("HANG {} COT {} TU {}", 
						this->sachAddFieldController.items[i].inputField[2].GetPlaceholder(),
						this->sachAddFieldController.items[i].inputField[3].GetPlaceholder(),
						this->sachAddFieldController.items[i].inputField[4].GetPlaceholder()
					));
					LINKED_LIST::PushBack(newBookList, newBook);
				}
				newTitle->SetCatalogue(newBookList);
			}

			LINEAR_LIST::InsertOrder(titleList, newTitle);
			std::cerr << "[INFO] Successfully insert a new item into title list!\n";
			return true;
		}
		else {
			this->submit.SetFillColor(rgb(145, 216, 228));
		}


		return false;
	}

	void ItemAddField::Activate() {
		this->active = true;
	}

	void ItemAddField::Deactivate() {
		this->active = false;
	}

	bool ItemAddField::DisplayStatus() {
		return this->active;
	}

	void ItemAddField::Display(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController) {
		if (this->active == false) {
			return;
		}

		this->backdrop.Draw();
		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 7; ++i) {
			this->inputField[i].Display();
		}
		this->createDanhMucSach.Display();
		this->submit.Display();
		this->goBackButton.Display();

		if (this->sachAddFieldController.DisplayStatus() == true) {
			this->sachAddFieldController.Display();
			this->sachAddFieldController.IndexChangeButtonOnAction();
			this->sachAddFieldController.SachAddFieldOnUpdate(titleList, InputController);
		}
	}

	bool ItemAddField::GoBackButtonOnAction() {
		if (this->active == false) {
			return false;
		}

		if (this->goBackButton.IsHover()) {
			this->goBackButton.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackButton.LeftMouseClicked()) {
			delay(100);
			this->active = false;
			this->sachAddFieldController.Deactivate();
			return true;
		}
		else {
			this->goBackButton.SetFillColor(rgb(236, 242, 255));
		}
		return false;
	}

	TitleDetailDisplayField::TitleDetailDisplayField() {
		this->active = false;

		this->targetedTitle = nullptr;

		this->background = HELPER::Fill(HELPER::Coordinate(1105, 120), 650, 700, rgb(238, 238, 238), BLACK);

		this->title = Button(
			HELPER::Coordinate(1105, 120), HELPER::Dimension(650, 80),
			WHITE, //* text color
			rgb(87, 108, 188), //* Background color
			BLACK //* Border color
		);

		HELPER::Coordinate titleDetailsCoordinates[] = {
			HELPER::Coordinate(1130, 232),
			HELPER::Coordinate(1130, 314),
			HELPER::Coordinate(1130, 397),
			HELPER::Coordinate(1130, 480),
			HELPER::Coordinate(1130, 563),
		};
		for (int i = 0; i < 5; ++i) {
			this->titleDetails[i] = Button(
				titleDetailsCoordinates[i], HELPER::Dimension(600, 60),
				BLACK, //* Text color
				WHITE, //* Fill color
				BLACK  //* Border color
			);
		}

		this->goBackBtn = Button(
			HELPER::Coordinate(1685, 930), 70, 40,
			rgb(24, 18, 43), rgb(236, 242, 255), rgb(24, 18, 43)
		);
		this->goBackBtn.SetPlaceholder("<");

		this->bookListDatasheetController = DATASHEET::Controller(
			16, 4, 50, HELPER::Coordinate(36, 120)
		);

		this->deleteBookBtn = Button(
			HELPER::Coordinate(229, 945), 150, 40,
			rgb(57, 62, 70),
			rgb(219, 223, 253),
			rgb(219, 223, 253)
		);
		this->deleteBookBtn.SetPlaceholder("DELETE");
		this->deleteBook = nullptr;
	}

	void TitleDetailDisplayField::Destructor() {
		this->bookListDatasheetController = DATASHEET::Controller();
	}

	void TitleDetailDisplayField::Initialize(BOOK_TITLE::BookTitle* title) {
		this->targetedTitle = title;

		this->title.SetPlaceholder(this->targetedTitle->GetTitle());

		this->titleDetails[0].SetPlaceholder(std::format("isbn: {}", this->targetedTitle->GetISBN()));
		this->titleDetails[1].SetPlaceholder(std::format("Category: {}", this->targetedTitle->GetCategory()));
		this->titleDetails[2].SetPlaceholder(std::format("Author: {}", this->targetedTitle->GetAuthor()));
		this->titleDetails[3].SetPlaceholder(std::format("Page number: {}", std::to_string(this->targetedTitle->GetPageCount())));
		this->titleDetails[4].SetPlaceholder(std::format("Public: {}", std::to_string(this->targetedTitle->GetPublicationYear())));

		this->CreateBookListDatasheet();
	}

	void TitleDetailDisplayField::CreateBookListDatasheet() {
		std::string labels[] = { "STT", "MA BOOK", "TRANG THAI", "VI TRI" };
		int chrLimits[] = { 3, 8, 18, 20 };
		
		int listSize = LINKED_LIST::Size(this->targetedTitle->GetCatalogue());

		this->bookListDatasheetController.SetDatasheetCount(
			max(1, listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1))
		);
		this->bookListDatasheetController.InitializeDatasheets();

		for (int i = 0; i < this->bookListDatasheetController.GetDatasheetCount(); ++i) {
			this->bookListDatasheetController[i] = DATASHEET::Datasheet(
				this->bookListDatasheetController.GetRecordCount(),
				this->bookListDatasheetController.GetAttributeCount(),
				this->bookListDatasheetController.GetRowHeight(),
				this->bookListDatasheetController.GetTopLeft(),
				labels, chrLimits
			);
		}

		if (listSize == 0) {
			return;
		}

		int recordIndex = 0;
		int sheetIndex = -1;
		int order = 0;
		for (LINKED_LIST::Pointer p = this->targetedTitle->GetCatalogue().first; p != nullptr; p = p->next) {
			++recordIndex;
			if (recordIndex > this->bookListDatasheetController.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (this->bookListDatasheetController.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[this->bookListDatasheetController.GetAttributeCount()];
			data[0] = std::to_string(++order);
			data[1] = p->info.GetID();
			data[2] = p->info.StringfyStatus();
			data[3] = p->info.GetDescription();

			this->bookListDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	void TitleDetailDisplayField::Activate() {
		this->active = true;
	}

	void TitleDetailDisplayField::Deactivate() {
		this->active = false;
	}

	bool TitleDetailDisplayField::DisplayStatus() {
		return this->active;
	}
	
	void TitleDetailDisplayField::Display() {
		if (this->active == false) {
			return;
		}

		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 5; ++i) {
			this->titleDetails[i].Display();
		}

		this->bookListDatasheetController.Display();

		if (this->deleteBookBtn.IsActive() == true) {
			this->deleteBookBtn.Display();

			if (this->deleteBookBtn.IsHover()) {
				this->deleteBookBtn.SetFillColor(rgb(155, 163, 235));
				this->deleteBookBtn.SetBorderColor(rgb(36, 47, 155));
				this->deleteBookBtn.SetTextColor(rgb(234, 253, 252));
			}
			else if (this->deleteBookBtn.LeftMouseClicked()) {
				//todo: LINKED_LIST::DeleteAt function is not working!
				
				LINKED_LIST::Controller buffer = this->targetedTitle->GetCatalogue();
				if (LINKED_LIST::DeleteAt(buffer, this->deleteBook->info)) {
					std::cerr << "delete!\n";
					this->targetedTitle->SetCatalogue(buffer);
					this->CreateBookListDatasheet();
				}
				else {
					std::cerr << "not delete\n";
				}
			}
			else {
				this->deleteBookBtn.SetFillColor(rgb(219, 223, 253));
				this->deleteBookBtn.SetBorderColor(rgb(219, 223, 253));
				this->deleteBookBtn.SetTextColor(rgb(57, 62, 70));
			}
		}

		this->goBackBtn.Display();
	}

	void TitleDetailDisplayField::DeleteBookButtonOnAction() {
		if (this->bookListDatasheetController.GetDatasheetCount() == 0) {
			return;
		}

		for (int i = 1; i < this->bookListDatasheetController.GetRecordCount(); ++i) {	
			Button& bookIdButton = this->bookListDatasheetController[this->bookListDatasheetController.CurrentActiveDatasheet()][i][1];

			if (bookIdButton.IsHover()) {
				bookIdButton.SetFillColor(rgb(244, 249, 249));
			}
			else if (bookIdButton.LeftMouseClicked()) {
				delay(100);
				for (LINKED_LIST::Pointer p = this->targetedTitle->GetCatalogue().first; p != nullptr; p = p->next) {
					if (p->info.GetID().compare(bookIdButton.GetPlaceholder()) == 0) {
						this->deleteBook = p;
						break;
					}
				}
				this->deleteBookBtn.Deactivate();
			}
			else {
				if (i % 2 != 0) {
					bookIdButton.SetFillColor(rgb(255, 251, 245));
				}
				else {
					bookIdButton.SetFillColor(rgb(238, 238, 238));
				}
			}
		}

		if (this->deleteBookBtn.IsHover()) {
			this->deleteBookBtn.SetFillColor(rgb(155, 163, 235));
			this->deleteBookBtn.SetBorderColor(rgb(36, 47, 155));
			this->deleteBookBtn.SetTextColor(rgb(234, 253, 252));
		}
		else if (this->deleteBookBtn.LeftMouseClicked()) {
			delay(100);
		}
		else {
			this->deleteBookBtn.SetFillColor(rgb(219, 223, 253));
			this->deleteBookBtn.SetBorderColor(this->deleteBookBtn.GetFillColor());
			this->deleteBookBtn.SetTextColor(rgb(57, 62, 70));
		}
	}

	void TitleDetailDisplayField::ResetDeleteBookButton() {
		this->deleteBookBtn = Button(
			HELPER::Coordinate(229, 945), 150, 40,
			rgb(57, 62, 70),
			rgb(219, 223, 253),
			rgb(219, 223, 253)
		);
		this->deleteBookBtn.SetPlaceholder("DELETE");
		this->deleteBook = nullptr;
	}

	bool TitleDetailDisplayField::GoBackButtonOnAction() {
		if (this->active == false) {
			return true;
		}

		if (this->goBackBtn.IsHover()) {
			this->goBackBtn.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackBtn.LeftMouseClicked()) {
			delay(100);
			this->active = false;
			return true;
		}
		else {
			this->goBackBtn.SetFillColor(rgb(236, 242, 255)
			);
		}
		return false;
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

/*
* DauSachTab constructor
*/

DauSachTab::DauSachTab(LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController) {

	//* Initialize data
	this->titleList = titleList;
	this->titleListSortedByCategory = nullptr;
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
	DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
	this->datasheetController.ActivateDatasheets(); //* Activate datasheet by default.

	//* Creating Button for adding or editting or removing item of the list
	HELPER::Coordinate listManipulateButtonCoordinates[] = {
		HELPER::Coordinate(380, 940),
		HELPER::Coordinate(565, 940),
		HELPER::Coordinate(750, 940)
	};
	HELPER::Dimension listManipulateButtonDimension(150, 30);
	std::string listManipulateButtonPlaceholders[] = {"NEW", "EDIT", "REMOVE"};
	for (int i = 0; i < 3; ++i) {
		this->functionalButtons[i] = Button(listManipulateButtonCoordinates[i], listManipulateButtonDimension);
		this->functionalButtons[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(this->functionalButtons[i]);
	}
}

void DauSachTab::Destructor() {
	delete[] this->titleListSortedByCategory;
	delete this->inputController;
	delete this->titleList;
}

void DauSachTab::SortByCategory() {
	CATEGORY_LINKED_LIST::Pointer categories;
	CATEGORY_LINKED_LIST::Initialzie(categories);

	CATEGORY_LINKED_LIST::PushFront(categories, this->titleList->nodes[0]->GetCategory());
	bool flag = true;
	int categoryCount = 1;
	for (int i = 1; i < this->titleList->numberOfNode; ++i) {
		flag = true;
		for (int j = 0; j < i; ++j) {
			if (this->titleList->nodes[j]->GetCategory().compare(this->titleList->nodes[i]->GetCategory()) == 0) {
				flag = false;
				break;
			}
		}

		if (flag) {
			CATEGORY_LINKED_LIST::InsertOrder(categories, this->titleList->nodes[i]->GetCategory());
			++categoryCount;
		}
	}

	this->titleListSortedByCategory = new BOOK_TITLE::BookTitle* [this->titleList->numberOfNode];
	int index = 0;
	for (CATEGORY_LINKED_LIST::Pointer p = categories; p != nullptr; p = p->next) {
		for (int i = 0; i < this->titleList->numberOfNode; ++i) {
			if (this->titleList->nodes[i]->GetCategory().compare(p->info) == 0) {
				this->titleListSortedByCategory[index++] = this->titleList->nodes[i];
			}
		}
	}

	//for (int i = 0; i < this->titleList->numberOfNode; ++i) {
	//	std::cerr << this->titleListSortedByCategory[i]->GetTitle() << " - " << this->titleListSortedByCategory[i]->GetCategory() << "\n";
	//}

	delete categories;
}

void DauSachTab::Run() {

	/**
	 * * The tab will displays the Titles's datasheets by default.
	 * * Follow up with the avalable function such as CREATE/UPDATE/DELETE to the Titles database.
	 * * There will be a Search session for users to search for the needed title by searching by it's name.
	 * * User can press the datasheet's label in order to sort the items by the corresponding label.
	 * 
	 * ! Currently, the datasheets are sorted by the title's names and can be sorted by the title's category.
	*/
	if (this->datasheetController.DisplayStatus() == true) {

		//* Display datasheets
		this->datasheetController.Display();
		this->datasheetController.DatasheetChangeButtonUpdate();

		//* Display functional buttons
		for (int i = 0; i < 3; ++i) {
			this->functionalButtons[i].Display();
		}

		//* Display search field
		this->searchField.Activate();
		this->searchField.Display();
		this->searchField.OnAction(this->inputController);
		BOOK_TITLE::BookTitle* searchResult = LINEAR_LIST::SearchByName(*this->titleList, this->searchField.inputSearchBox->GetPlaceholder());
		
		//* Title search logic
		if (searchResult != nullptr) {
			this->searchField.searchStatusBox->SetPlaceholder("SHOW DETAILS");
			this->searchField.searchStatusBox->SetFillColor(rgb(97, 177, 90));
			this->searchField.searchStatusBox->SetBorderColor(rgb(182, 227, 136));
			this->searchField.searchStatusBox->SetTextColor(WHITE);
			this->searchField.searchStatusBox->Display();

			//* Shor detail button logic
			if (this->searchField.searchStatusBox->IsHover()) {
				this->searchField.searchStatusBox->SetFillColor(rgb(199, 242, 164));
			}
			else if (this->searchField.searchStatusBox->LeftMouseClicked()) {
				this->searchField.targetDetails.Activate();
				this->searchField.targetDetails.Initialize(searchResult);
			}
			else {
				this->searchField.searchStatusBox->SetFillColor(rgb(97, 177, 90));
			}
		}
		else {
			this->searchField.targetDetails.Deactivate();
			this->datasheetController.ActivateDatasheets();
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchField.searchStatusBox);
		}

		//* Sort by name (default option)
		Button& titleLabelButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][2];
		if (titleLabelButton.IsHover()) {
			titleLabelButton.SetFillColor(rgb(83, 127, 231));
			titleLabelButton.SetTextColor(rgb(233, 248, 249));
		}
		else if (titleLabelButton.LeftMouseClicked()) {
			delay(100);
			DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
		}
		else {
			titleLabelButton.SetFillColor(rgb(210, 218, 255));
			titleLabelButton.SetTextColor(BLACK);
		}

		//* Sort by category logic
		Button& categoryLabelButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][6];
		if (categoryLabelButton.IsHover()) {
			categoryLabelButton.SetFillColor(rgb(83, 127, 231));
			categoryLabelButton.SetTextColor(rgb(233, 248, 249));
		}
		else if (categoryLabelButton.LeftMouseClicked()) {
			delay(100);
			this->SortByCategory();
			DAU_SACH_TAB::CreateDatasheetsWithSortedCategory(this->titleListSortedByCategory, this->titleList->numberOfNode, this->datasheetController);
		}
		else {
			categoryLabelButton.SetFillColor(rgb(210, 218, 255));
			categoryLabelButton.SetTextColor(BLACK);
		}

		/**
		 * * Book list on action logic
		 * * When hovering the mouse on the title's name, change the pointing button's fill color.
		 * * When pressed at the title's name button, display the title's details.
		 * 
		 * ! Currently, the UI design of this function is not very good!
		*/
		for (int i = 1; i < this->datasheetController.GetRecordCount(); ++i) {
			Button& titleNameButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][i][2];

			if (titleNameButton.IsHover()) {
				titleNameButton.SetFillColor(rgb(244, 249, 249));
			}
			else if (titleNameButton.LeftMouseClicked()) {
				delay(100);
				this->datasheetController.DeactivateDatasheets();
				this->titleDetailField.Activate();
				this->titleDetailField.Initialize(
					this->titleList->nodes[this->datasheetController.CurrentActiveDatasheet() * 15 + i - 1]
				);
			}
			else {
				if (i % 2 != 0) {
					titleNameButton.SetFillColor(rgb(255, 251, 245));
				}
				else {
					titleNameButton.SetFillColor(rgb(238, 238, 238));
				}
			}
		}

		/**
		 * * Functional buttons on action logic
		 * * When hovering the mouse on the functional buttons, highlight the corresponding button by changing the fill color.
		 * * Pressed at each button will activate the corresponding function.
		*/
		for (int i = 0; i < 3; ++i) {
			Button& currentBtn = this->functionalButtons[i];

			if (currentBtn.IsHover()) {
				DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonHoverProperties(currentBtn);
			}
			else if (currentBtn.LeftMouseClicked()) {
				switch (i) {
					delay(100);
				case (0):
					this->datasheetController.DeactivateDatasheets();
					this->itemAddField.Activate();
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

	//* Displaying founded search target
	if (this->searchField.targetDetails.DisplayStatus()) {
		this->datasheetController.DeactivateDatasheets();
		this->searchField.targetDetails.Display();
		this->searchField.targetDetails.DeleteBookButtonOnAction();

		if (this->searchField.targetDetails.GoBackButtonOnAction()) {
			this->datasheetController.ActivateDatasheets();
			this->searchField.targetDetails.Deactivate();
			this->searchField.inputSearchBox->SetPlaceholder("Type here to search");
			this->searchField.searchStatusBox->SetPlaceholder("Result: NOT FOUND!");
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchField.searchStatusBox);
		}
	}

	//* Displaying title's details field
	if (this->titleDetailField.DisplayStatus() == true) {
		this->titleDetailField.Display();
		if (this->titleDetailField.GoBackButtonOnAction() == true) {
			this->datasheetController.ActivateDatasheets();
		}
		else {
			this->datasheetController.DeactivateDatasheets();
		}
	}

	//* Displaying the ADD function.
	if (this->itemAddField.DisplayStatus() == true) {
		this->itemAddField.Display(*this->titleList, *this->inputController);

		if (this->itemAddField.GoBackButtonOnAction()) {
			this->itemAddField.Deactivate();
			this->datasheetController.ActivateDatasheets();
		}

		bool regenerateDatasheet = this->itemAddField.ItemAddFieldOnUpdate(*this->titleList, *this->inputController);
		if (regenerateDatasheet) {
			DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
		}
	}


}
