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


void READER_TAB_MEMBERS::SearchField::ResultBoxDefaultStyling()
{
	this->resultBox.SetFillColor(rgb(73, 84, 100));
	this->resultBox.SetBorderColor(rgb(73, 84, 100));
	this->resultBox.SetTextColor(rgb(244, 244, 242));
}

void READER_TAB_MEMBERS::SearchField::ResultBoxFoundedStyling()
{
	this->resultBox.SetFillColor(rgb(113, 239, 163));
	this->resultBox.SetBorderColor(rgb(80, 203, 147));
	this->resultBox.SetTextColor(rgb(73, 84, 100));
}

void READER_TAB_MEMBERS::SearchField::ResultBoxOnAction()
{

}

READER_TAB_MEMBERS::SearchField::SearchField()
{
	this->readerList = nullptr;
	this->inputController = nullptr;
	this->status = false;
	this->searchResult = nullptr;
	this->showSearchResult = false;

	this->background = HELPER::Fill(HELPER::Coordinate(1305, 120), 450, 250);
	this->title = Button(HELPER::Coordinate(1305, 120), 450, 50);
	this->title.SetPlaceholder("SEARCH");

	this->searchBox = Button(HELPER::Coordinate(1330, 200), 400, 70);
	this->searchBox.SetPlaceholder("Type here to search");

	this->resultBox = Button(HELPER::Coordinate(1330, 295), 400, 50);
	this->resultBox.SetPlaceholder("Result:");

	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::BackgroundStyling(&this->background);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::TitleStyling(&this->title);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::SearchBoxStyling(&this->searchBox);
	this->ResultBoxDefaultStyling();
}

READER_TAB_MEMBERS::SearchField::SearchField(AVL_TREE::Pointer* readerList, ELEMENTS::InputModeController* inputController)
{
	this->readerList = readerList;
	this->inputController = inputController;
	this->status = false;
	this->searchResult = nullptr;
	this->showSearchResult = false;

	this->background = HELPER::Fill(HELPER::Coordinate(1305, 120), 450, 250);
	this->title = Button(HELPER::Coordinate(1305, 120), 450, 50);
	this->title.SetPlaceholder("SEARCH");

	this->searchBox = Button(HELPER::Coordinate(1330, 200), 400, 70);
	this->searchBox.SetPlaceholder("Type here to search");

	this->resultBox = Button(HELPER::Coordinate(1330, 295), 400, 50);
	this->resultBox.SetPlaceholder("Result:");

	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::BackgroundStyling(&this->background);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::TitleStyling(&this->title);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::SearchBoxStyling(&this->searchBox);
	this->ResultBoxDefaultStyling();
}

void READER_TAB_MEMBERS::SearchField::Activate()
{
	this->status = true;
}

void READER_TAB_MEMBERS::SearchField::Deactivate()
{
	this->status = false;
}

bool READER_TAB_MEMBERS::SearchField::IsActive()
{
	return this->status == true;
}

void READER_TAB_MEMBERS::SearchField::SearchBoxOnActionLogic()
{
	if (this->searchBox.IsHover()) {
		this->searchBox.SetFillColor(rgb(255, 234, 210));
		this->searchBox.SetBorderColor(rgb(130, 148, 196));
	}
	else if (this->searchBox.LeftMouseClicked()) {
		delay(100);
		this->inputController->Activate(&this->searchBox, &this->searchBox, 30, true, true, true);
	}
	else {
		DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::SearchBoxStyling(&this->searchBox);
	}
}

int READER_TAB_MEMBERS::SearchField::SearchReaderAlgorithm()
{
	STACK::Stack stk;
	STACK::Initialize(stk);

	AVL_TREE::Pointer p = *this->readerList;
	std::string searchValue{}, fullName{}, readerID{};
	do {
		while (p != nullptr) {
			STACK::Push(stk, p);
			p = p->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			p = STACK::Pop(stk);
			
			//* Search logic here
			searchValue = this->searchBox.GetPlaceholder();
			fullName = p->info.GetFirstName() + p->info.GetLastName();
			readerID = p->info.GetID();

			if (readerID.find(searchValue) != std::string::npos) {
				this->searchResult = p;
				return 1;
			}
			else if (fullName.find(searchValue) != std::string::npos) {
				this->searchResult = p;
				return 2;
			}

			p = p->right;
		}
		else {
			break;
		}
	} while (true);
	this->searchResult = nullptr;
	return 0;
}

void READER_TAB_MEMBERS::SearchField::ProcessingSearchResult()
{
	const std::string& res = this->searchBox.GetPlaceholder();
	if (res != "" && res != " " && res != "Type here to search") {
		this->SearchReaderAlgorithm();
		if (this->searchResult != nullptr) {
			this->ResultBoxOnAction();
		}
		else {
			this->ResultBoxDefaultStyling();
		}
	}
	else {
		this->ResultBoxDefaultStyling();
	}
}

void READER_TAB_MEMBERS::SearchField::Display()
{
	this->background.Draw();
	this->title.Display();
	this->searchBox.Display();
	this->resultBox.Display();
}

READER_TAB_MEMBERS::NewListItemForm::NewListItemForm() {
	this->status = false;
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->ho = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho->SetPlaceholder("firstName");

	this->ten = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten->SetPlaceholder("lastName");

	this->phai = new Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->phai->SetPlaceholder("sex");

	this->createDanhMucSach = new Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->createDanhMucSach->SetPlaceholder("SUBMIT");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ho);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ten);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->createDanhMucSach);
}

READER_TAB_MEMBERS::NewListItemForm::~NewListItemForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->ho;
	delete this->ten;
	delete this->phai;
	delete this->createDanhMucSach;
}

void READER_TAB_MEMBERS::NewListItemForm::Display() {
	this->background->Draw();
	this->title->Display();
	this->maThe->Display();
	this->ho->Display();
	this->ten->Display();
	this->phai->Display();
	this->createDanhMucSach->Display();
}

bool READER_TAB_MEMBERS::NewListItemForm::SubmitForm(AVL_TREE::Pointer& dsTheDocGia, ELEMENTS::InputModeController& InputController) {
	Button* formInputField[3] = { this->ho, this->ten, this->phai };
	int fieldCharacterLimit[3] = { 30, 15, 3 };

	int nextIndex = READER_MODULES::GetIndex(CONSTANTS::THE_DOC_GIA_INDEX, dsTheDocGia);
	this->maThe->SetPlaceholder(std::to_string(nextIndex));

	for (int i = 0; i < 3; ++i) {
		if (formInputField[i]->IsPointed() && formInputField[i]->LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(formInputField[i]);
		}
		else if (formInputField[i]->LeftMouseClicked()) {
			delay(100);
			InputController.Activate(formInputField[i], formInputField[i], fieldCharacterLimit[i], true, false, true);
		}
		else {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(formInputField[i]);
		}
	}

	if (this->createDanhMucSach->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->createDanhMucSach);
	}
	else if (this->createDanhMucSach->LeftMouseClicked()) {
		delay(100);

		READER::Reader newItem;

		newItem.SetID(nextIndex);
		newItem.SetFirstName(STR::Trim(this->ho->GetPlaceholder()));
		newItem.SetLastName(STR::Trim(this->ten->GetPlaceholder()));
		newItem.SetSex(this->phai->GetPlaceholder() == "MALE" ? READER::Sex::MALE : READER::Sex::FEMALE);
		newItem.SetStatus(READER::ReaderStatus::ACTIVE);
		newItem.SetBorrowedBooks(DOUBLE_LINKED_LIST::Controller());
		delay(100);

		bool res = AVL_TREE::Insert(dsTheDocGia, newItem);

		return true;
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->createDanhMucSach);
	}

	return false;
}

READER_TAB_MEMBERS::DeleteItemInListForm::DeleteItemInListForm() {
	this->status = false;
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->hoTen = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->hoTen->SetPlaceholder("firstName va ten");

	this->phai = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->phai->SetPlaceholder("sex");

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

READER_TAB_MEMBERS::DeleteItemInListForm::~DeleteItemInListForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->hoTen;
	delete this->trangThai;
	delete this->phai;
	delete this->deleteBtn;
}

void READER_TAB_MEMBERS::DeleteItemInListForm::Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	this->searchTargetFound = false;
	this->background->Draw();
	this->title->Display();
	this->maThe->Display();

	//* id input box logic
	if (this->maThe->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	}
	else if (this->maThe->LeftMouseClicked()) {
		delay(100);

		InputController.Activate(this->maThe, this->maThe, 4, false, true, false);
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(this->maThe);
	}

	bool checker = VALIDATOR::OnlyDigit(this->maThe->GetPlaceholder());
	if (checker) {
		this->searchResult = AVL_TREE::SearchByKey(danhSachTheDocGia, std::stoi(this->maThe->GetPlaceholder()));
		if (this->searchResult != nullptr) {
			int currentBorrowedBooksCount = BOOK_CIRCULATION_MODULES::CountBorrowedBooks(this->searchResult->info.GetBorrowedBooks());
			if (currentBorrowedBooksCount != 0) {
				std::cerr << std::format("[ERROR] DOC GIA DANG MUON BOOK! KHONG THE XOA DOC GIA!\n");
			}
			else {
				this->searchTargetFound = true;
			}

			this->hoTen->SetPlaceholder(this->searchResult->info.GetFullName());
			this->phai->SetPlaceholder(this->searchResult->info.StringfySex());
			this->trangThai->SetPlaceholder(this->searchResult->info.StringfyStatus());

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

bool READER_TAB_MEMBERS::DeleteItemInListForm::SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {

	//* Submit button
	if (this->deleteBtn->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->deleteBtn);
	}
	else if (this->deleteBtn->LeftMouseClicked()) {
		delay(100);
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

READER_TAB_MEMBERS::EditItemInListForm::EditItemInListForm() {
	this->status = false;
	this->background = new HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->ho = new Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho->SetPlaceholder("firstName");

	this->ten = new Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten->SetPlaceholder("lastName");

	this->phai = new Button(HELPER::Coordinate(1330, 770), 145, 60);
	this->phai->SetPlaceholder("sex");

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

READER_TAB_MEMBERS::EditItemInListForm::~EditItemInListForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->ho;
	delete this->ten;
	delete this->trangThai;
	delete this->phai;
	delete this->saveBtn;
}

void READER_TAB_MEMBERS::EditItemInListForm::Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	this->searchTargetFound = false;

	this->background->Draw();
	this->title->Display();
	this->maThe->Display();

	if (this->maThe->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(this->maThe);
	}
	else if (this->maThe->LeftMouseClicked()) {
		delay(100);
		InputController.Activate(this->maThe, this->maThe, 4, false, true, false);
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	}
}

bool READER_TAB_MEMBERS::EditItemInListForm::SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {

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
		delay(100);

		if (this->searchTargetFound == true) {

			bool checker = true;

			if (this->phai->GetPlaceholder() != "MALE" && this->phai->GetPlaceholder() != "FEMALE") {
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG PHAI\n");
				checker = false;
			}

			if (this->trangThai->GetPlaceholder() != "HOAT DONG" && this->trangThai->GetPlaceholder() != "BI KHOA") {
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG TRANG THAI\n");
				checker = false;
			}

			if (checker) {
				this->searchResult->info.SetFirstName(this->ho->GetPlaceholder());
				this->searchResult->info.SetLastName(this->ten->GetPlaceholder());
				this->searchResult->info.SetSex(
					this->phai->GetPlaceholder() == "MALE" ? READER::Sex::MALE : READER::Sex::FEMALE
				);
				this->searchResult->info.SetStatus(
					this->trangThai->GetPlaceholder() == "BI KHOA" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE
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

READER_TAB_MEMBERS::ReaderInfo::ReaderInfo()
{
	this->background = HELPER::Fill(
		HELPER::Coordinate(1148, 489),
		600, 330,
		rgb(217, 217, 217),
		BLACK
	);

	this->readerFullname = Button(
		HELPER::Coordinate(1171, 525),
		550, 60,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerFullname.SetPlaceholder("Reader fullname");

	this->readerId = Button(
		HELPER::Coordinate(1171, 620),
		550, 60,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerId.SetPlaceholder("Reader ID");

	this->readerStatus = Button(
		HELPER::Coordinate(1171, 723),
		550, 60,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerStatus.SetPlaceholder("Reader Status");


}

void READER_TAB_MEMBERS::ReaderInfo::UpdateReaderInfo(READER::Reader* reader)
{
	this->readerFullname.SetPlaceholder(reader->GetFullName());
	this->readerId.SetPlaceholder(std::to_string(reader->GetID()));
	this->readerStatus.SetPlaceholder(reader->StringfyStatus());
}

void READER_TAB_MEMBERS::ReaderInfo::Display()
{
	this->background.Draw();
	this->readerFullname.Display();
	this->readerId.Display();
	this->readerStatus.Display();
}

READER_TAB_MEMBERS::ReaderIndeptDetail::ReaderIndeptDetail()
{
	this->active = false;
	this->reader = nullptr;
	this->titleList = nullptr;
}

READER_TAB_MEMBERS::ReaderIndeptDetail::ReaderIndeptDetail(LINEAR_LIST::LinearList* titleList, READER::Reader* reader)
{
	this->titleList = titleList;
	this->reader = reader;

	const int labelsCount = 5;
	this->titlesDatasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT,
		labelsCount,
		DAU_SACH_PROPERTIES::ROW_HEIGHT,
		HELPER::Coordinate(36, 120)
	);
	this->CreateTitlesDatasheet();
	this->titlesDatasheetController.ActivateDatasheets();

	if (this->reader != nullptr) {
		this->readerInfo.UpdateReaderInfo(this->reader);
	}

	this->goBackButton = Button(
		HELPER::Coordinate(1685, 930), 70, 40,
		rgb(24, 18, 43), rgb(236, 242, 255), rgb(24, 18, 43)
	);
	this->goBackButton.SetPlaceholder("<");
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::UpdateReader(READER::Reader* reader)
{
	this->reader = reader;
	this->readerInfo.UpdateReaderInfo(this->reader);
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Display()
{
	this->titlesDatasheetController.Display();
	this->titlesDatasheetController.DatasheetChangeButtonUpdate();

	this->readerInfo.Display();
	this->goBackButton.Display();
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::GoBackButtonOnAction()
{
	if (this->active == false) {
		return false;
	}

	if (this->goBackButton.IsHover()) {
		this->goBackButton.SetFillColor(rgb(130, 170, 227));
	}
	else if (this->goBackButton.LeftMouseClicked()) {
		delay(100);
		this->active = false;
		this->titlesDatasheetController.DeactivateDatasheets();
		return true;
	}
	else {
		this->goBackButton.SetFillColor(rgb(236, 242, 255));
	}
	return false;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Activate()
{
	this->titlesDatasheetController.ActivateDatasheets();
	this->active = true;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Deactivate()
{
	this->titlesDatasheetController.DeactivateDatasheets();
	this->active = false;
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::IsActive()
{
	return this->active == true;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::CreateTitlesDatasheet()
{
	std::string labels[] = {
		"ORDER", "ISBN", "TITLE", "AUTHOR", "CATEGORY"
	};
	int characterLimits[] = {
		3, 4, 30, 20, 10
	};
	int listSize = this->titleList->numberOfNode;
	this->titlesDatasheetController.SetDatasheetCount(
		listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
	);

	this->titlesDatasheetController.InitializeDatasheets();

	for (int i = 0; i < this->titlesDatasheetController.GetDatasheetCount(); ++i) 
	{
		this->titlesDatasheetController[i] = DATASHEET::Datasheet(
			this->titlesDatasheetController.GetRecordCount(),
			this->titlesDatasheetController.GetAttributeCount(),
			this->titlesDatasheetController.GetRowHeight(),
			this->titlesDatasheetController.GetTopLeft(),
			labels,
			characterLimits
		);
	}

	int recordIndex = 0;
	int sheetIndex = -1;

	for (int i = 0; i < titleList->numberOfNode; ++i)
	{
		++recordIndex;
		if (recordIndex > this->titlesDatasheetController.GetRecordCount() - 1)
		{
			recordIndex = 1;
		}
		if (recordIndex % (this->titlesDatasheetController.GetRecordCount() - 1) == 1)
		{
			sheetIndex += 1;
		}

		std::string* data = new std::string[this->titlesDatasheetController.GetAttributeCount()];
		data[0] = std::to_string(i + 1);
		data[1] = titleList->nodes[i]->GetISBN();
		data[2] = titleList->nodes[i]->GetTitle();
		data[3] = titleList->nodes[i]->GetAuthor();
		data[4] = titleList->nodes[i]->GetCategory();

		this->titlesDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::CreateBorrowBooksDatasheet()
{
	for (DOUBLE_LINKED_LIST::Pointer p = this->reader->GetBorrowedBooks().First; p != nullptr; p = p->right) 
	{
		std::cout << p->info.GetID() << "\n";
	}
}

//----------------------------------------------------------------------------------------------------------------------------

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
			data[1] = std::to_string(currentNode->info.GetID());
			data[2] = currentNode->info.GetFirstName();
			data[3] = currentNode->info.GetLastName();
			data[4] = currentNode->info.StringfySex();
			data[5] = currentNode->info.StringfyStatus();
			data[6] = "BOOK DANG MUON";

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
		data[1] = std::to_string(arr[i]->info.GetID());
		data[2] = arr[i]->info.GetFirstName();
		data[3] = arr[i]->info.GetLastName();
		data[4] = arr[i]->info.StringfySex();
		data[5] = arr[i]->info.StringfyStatus();
		data[6] = "BOOK DANG MUON";

		(*datasheetController)[sheetIndex].UpdateNewPlaceholder(data, recordIndex);

		//---
	}

}

/**
* Tab's constructor
* 
* All the code in this method only run once in the program runtime!
*/
DanhSachTheDocGiaView::DanhSachTheDocGiaView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController) {
	this->active = false;
	this->defaultOrder = true;
	this->readerList = readerList;
	this->titleList = titleList;
	this->InputController = inputController;
	
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 935);
	HELPER::Coordinate toRightBtnTopLeft(86, 935);

	this->datasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT, THE_DOC_GIA_PROPERTIES::PROPERTIES_COUNT, 
		THE_DOC_GIA_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->datasheetController.ActivateDatasheets();
	if (this->defaultOrder) {
		this->CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
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

	this->searchField = READER_TAB_MEMBERS::SearchField(this->readerList, this->InputController);
	this->searchField.Activate();
	this->readerIndeptDetail = READER_TAB_MEMBERS::ReaderIndeptDetail(this->titleList, nullptr);
}

/**
* Tab's frame logic.
* 
* Code in this method will be run many time.
* Each time the program render a frame, this code will be run once, therefore the element's logic will be in here!
*/
void DanhSachTheDocGiaView::Run()
{
	if (this->datasheetController.DisplayStatus() == true)
	{
		//* Display datasheet
		this->datasheetController.Display();
		this->datasheetController.DatasheetChangeButtonUpdate();

		//* Display function button
		for (int i = 0; i < 3; ++i) {
			this->listManipulateButton[i].Display();
		}

		if (this->searchField.IsActive())
		{
			//* Display Search field
			this->searchField.Display();
			this->searchField.SearchBoxOnActionLogic();
			this->searchField.ProcessingSearchResult();
			if (this->searchField.searchResult != nullptr) {
				if (this->searchField.resultBox.IsHover()) {
					this->searchField.resultBox.SetFillColor(rgb(172, 255, 173));
				}
				else if (this->searchField.resultBox.LeftMouseClicked()) {
					delay(100);
					this->datasheetController.DeactivateDatasheets();
					this->searchField.Deactivate();
					this->readerIndeptDetail.Activate();
					this->readerIndeptDetail.UpdateReader(&this->searchField.searchResult->info);
				}
				else {
					this->searchField.ResultBoxFoundedStyling();
				}
			}
		}

		//* Detect if there is a function got activated
		if (this->listManipulationButtonStatus != -1) {
			switch (this->listManipulationButtonStatus) {
			case (0): {
				//* Display form
				this->newItemForm.Display();
				bool formSubmitted = this->newItemForm.SubmitForm(*this->readerList, *this->InputController);
				if (formSubmitted) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
				}
				break;
			}
			case (1): {
				this->editItemForm.Display(*this->readerList, *this->InputController);
				bool confirmSave = this->editItemForm.SubmitForm(*this->readerList, *this->InputController);
				if (confirmSave) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
				}
				break;
			}
			case (2): {
				this->deleteItemForm.Display(*this->readerList, *this->InputController);
				bool confirmDelete = this->deleteItemForm.SubmitForm(*this->readerList, *this->InputController);
				if (confirmDelete) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
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
				delay(100);
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
			this->CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
		}
		else {
			DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonDefaultStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][1]);
		}

		//* lastName label button
		if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3].IsHover()) {
			DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonHoverStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3]);
		}
		else if (this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3].LeftMouseClicked()) {
			delay(100);

			this->defaultOrder = false;
			AVL_TREE::Pointer* pointerArr{};
			int arrSize = 0;
			READER_MODULES::SortByName(*this->readerList, pointerArr, arrSize);

			DanhSachTheDocGiaView::CreateDatasheetsFromArr(pointerArr, arrSize, &this->datasheetController);

			delete[] pointerArr;
		}
		else {
			DANH_SACH_THE_DOC_GIA_STYLING::DatasheetLabelsButtonDefaultStyling(&this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][3]);
		}
	}

	if (this->readerIndeptDetail.IsActive()) {
		this->readerIndeptDetail.Display();

		if (this->readerIndeptDetail.GoBackButtonOnAction() == true) {
			this->readerIndeptDetail.Deactivate();
			this->datasheetController.ActivateDatasheets();
			this->searchField.Activate();
		}
	}
}

