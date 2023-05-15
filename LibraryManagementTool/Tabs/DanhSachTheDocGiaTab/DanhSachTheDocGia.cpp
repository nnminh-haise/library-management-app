#include "DanhSachTheDocGia.h"
#include "DanhSachTheDocGiaStyling.h"

#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/IndexGenerator.h"
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
	Stack<AVL_TREE::Pointer> stk;

	AVL_TREE::Pointer p = *this->readerList;
	std::string searchValue{}, fullName{}, readerID{};
	do {
		while (p != nullptr) {
			stk.Push(p);
			p = p->left;
		}

		if (stk.Empty() == false) {
			p = stk.Pop();
			
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

READER_TAB_MEMBERS::NewReaderForm::NewReaderForm(AVL_TREE::Pointer* readerList, ELEMENTS::InputModeController* inputController) {
	this->status = false;
	this->background = HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title.SetPlaceholder("NEW READER");

	this->readerIDButton = Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->readerIDButton.SetPlaceholder("Reader's ID");

	this->readerFirstNameButton = Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->readerFirstNameButton.SetPlaceholder("Reader's first name");

	this->readerLastNameButton = Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->readerLastNameButton.SetPlaceholder("Reader's last name");

	this->readerSexButton = Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->readerSexButton.SetPlaceholder("Reader's sex");

	this->submitButton = Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->submitButton.SetPlaceholder("CREATE");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(&this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(&this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerIDButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerFirstNameButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerLastNameButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerSexButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(&this->submitButton);

	this->readerList = readerList;
	this->inputController = inputController;
}

void READER_TAB_MEMBERS::NewReaderForm::Display() {
	this->background.Draw();
	this->title.Display();
	this->readerIDButton.Display();
	this->readerFirstNameButton.Display();
	this->readerLastNameButton.Display();
	this->readerSexButton.Display();
	this->submitButton.Display();
}

void READER_TAB_MEMBERS::NewReaderForm::FormOnAction()
{
	Button* inputFields[3] = { &this->readerFirstNameButton, &this->readerLastNameButton, &this->readerSexButton };
	int fieldsCharacterLimit[3] = { 30, 15, 6 };

	int readerListSize = 0;
	AVL_TREE::Size(*this->readerList, readerListSize);

	IndexGenerator indexGenerator(500000);
	this->readerIndex = indexGenerator.FromFileGetIndexAt(CONSTANTS::READER_INDICIES, readerListSize);
	this->readerIDButton.SetPlaceholder(std::to_string(readerIndex));

	for (int i = 0; i < 3; ++i) 
	{
		if (inputFields[i]->IsPointed() && inputFields[i]->LeftMouseClicked() == false) 
		{
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(inputFields[i]);
		}
		else if (inputFields[i]->LeftMouseClicked()) 
		{
			delay(100);
			this->inputController->Activate(inputFields[i], inputFields[i], fieldsCharacterLimit[i], true, false, true);
		}
		else 
		{
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(inputFields[i]);
		}
	}
}

bool READER_TAB_MEMBERS::NewReaderForm::SubmitForm() 
{
	if (this->submitButton.IsHover()) 
	{
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(&this->submitButton);
	}
	else if (this->submitButton.LeftMouseClicked()) 
	{
		delay(100);

		READER::Reader newreader;

		newreader.SetID(this->readerIndex);
		newreader.SetFirstName(STR::Trim(this->readerFirstNameButton.GetPlaceholder()));
		newreader.SetLastName(STR::Trim(this->readerLastNameButton.GetPlaceholder()));
		newreader.SetGender(this->readerSexButton.GetPlaceholder() == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);
		newreader.SetStatus(READER::ReaderStatus::ACTIVE);
		newreader.SetBooksCirculation(DOUBLE_LINKED_LIST::Controller());
		delay(100);

		bool res = AVL_TREE::Insert(*this->readerList, newreader);

		return true;
	}
	else 
	{
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(&this->submitButton);
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
	this->hoTen->SetPlaceholder("firstName va readerLastNameButton");

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
			int currentBorrowedBooksCount = BOOK_CIRCULATION_MODULES::CountBorrowedBooks(this->searchResult->info.GetBooksCirculation());
			if (currentBorrowedBooksCount != 0) {
				std::cerr << std::format("[ERROR] DOC GIA DANG MUON BOOK! KHONG THE XOA DOC GIA!\n");
			}
			else {
				this->searchTargetFound = true;
			}

			this->hoTen->SetPlaceholder(this->searchResult->info.GetFullName());
			this->phai->SetPlaceholder(this->searchResult->info.StringifyGender());
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

READER_TAB_MEMBERS::EditReaderInfoForm::EditReaderInfoForm(AVL_TREE::Pointer* readerList, ELEMENTS::InputModeController* inputController) 
{
	this->readerList = readerList;
	this->inputController = inputController;

	this->status = false;
	this->background = HELPER::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title.SetPlaceholder("EDITING READER INFO");

	this->readerIDButton = Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->readerIDButton.SetPlaceholder("Reader's ID");

	this->readerFirstNameButton = Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->readerFirstNameButton.SetPlaceholder("Reader's first name");

	this->readerLastNameButton = Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->readerLastNameButton.SetPlaceholder("Reader's last name");

	this->readerGenderButton = Button(HELPER::Coordinate(1330, 770), 145, 60);
	this->readerGenderButton.SetPlaceholder("Reader's gender");

	this->readerStatusButton = Button(HELPER::Coordinate(1500, 770), 230, 60);
	this->readerStatusButton.SetPlaceholder("Reader's GetStatus");

	this->saveBtn = Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->saveBtn.SetPlaceholder("SAVE");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(&this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(&this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerIDButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerFirstNameButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerLastNameButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerStatusButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerGenderButton);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(&this->saveBtn);

	this->searchReaderFound = 0;
	this->assignReaderOldInfo = false;
	this->searchResult = nullptr;
}

void READER_TAB_MEMBERS::EditReaderInfoForm::ReaderIDButtonOnAction()
{
	if (this->readerIDButton.IsHover())
	{
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(&this->readerIDButton);
	}
	else if (this->readerIDButton.LeftMouseClicked())
	{
		delay(100);
		this->inputController->Activate(&this->readerIDButton, &this->readerIDButton, 6, false, true, false);
		this->assignReaderOldInfo = false;
		this->searchReaderFound = 0;
	}
	else
	{
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(&this->readerIDButton);
	}
}

void READER_TAB_MEMBERS::EditReaderInfoForm::Display() 
{
	this->background.Draw();
	this->title.Display();
	this->readerIDButton.Display();
	this->readerFirstNameButton.Display();
	this->readerLastNameButton.Display();
	this->readerGenderButton.Display();
	this->readerStatusButton.Display();
	this->saveBtn.Display();
}

void READER_TAB_MEMBERS::EditReaderInfoForm::AssignReaderOldInfoToFields()
{
	this->readerIDButton.SetPlaceholder(std::to_string(this->searchResult->info.GetID()));
	this->readerFirstNameButton.SetPlaceholder(this->searchResult->info.GetFirstName());
	this->readerLastNameButton.SetPlaceholder(this->searchResult->info.GetLastName());
	this->readerGenderButton.SetPlaceholder(this->searchResult->info.StringifyGender());
	this->readerStatusButton.SetPlaceholder(this->searchResult->info.StringfyStatus());
}

void READER_TAB_MEMBERS::EditReaderInfoForm::FormOnAction()
{
	this->ReaderIDButtonOnAction();
	this->searchReaderFound += this->SearchReaderProcess();
	if (this->searchReaderFound == 1 && this->assignReaderOldInfo == true)
	{
		this->AssignReaderOldInfoToFields();
		this->assignReaderOldInfo = false;
	}

	Button* inpField[4] = { &this->readerFirstNameButton, &this->readerLastNameButton, &this->readerGenderButton, &this->readerStatusButton };

	for (int i = 0; i < 4; ++i)
	{
		if (inpField[i]->IsHover())
		{
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(inpField[i]);
		}
		else if (inpField[i]->LeftMouseClicked())
		{
			switch (i)
			{
			case (0):
				this->inputController->Activate(inpField[i], inpField[i], 30, true, false, true);
				break;
			case (1):
				this->inputController->Activate(inpField[i], inpField[i], 15, true, false, true);
				break;
			case (2):
				this->inputController->Activate(inpField[i], inpField[i], 6, true, false, false);
				break;
			case (3):
				this->inputController->Activate(inpField[i], inpField[i], 6, true, false, true);
				break;
			}
		}
		else
		{
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(inpField[i]);
		}
	}
}

bool READER_TAB_MEMBERS::EditReaderInfoForm::SearchReaderProcess()
{
	bool checker = VALIDATOR::OnlyDigit(this->readerIDButton.GetPlaceholder());
	if (checker)
	{
		this->searchResult = AVL_TREE::SearchByKey(*this->readerList, std::stoi(this->readerIDButton.GetPlaceholder()));
		if (this->searchResult != nullptr)
		{
			this->assignReaderOldInfo = true;
			return true;
		}
		else
		{
			std::cerr << std::format("[ERROR] MA THE IS NOT EXIST!\n");
		}
	}
	else
	{
		std::cerr << std::format("[ERROR] INVALID SEARCH DATA!\n");
	}
	this->assignReaderOldInfo = false;
	return false;
}

bool READER_TAB_MEMBERS::EditReaderInfoForm::SubmitForm() 
{
	if (this->saveBtn.IsHover()) 
	{
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(&this->saveBtn);
	}
	else if (this->saveBtn.LeftMouseClicked()) 
	{
		delay(100);
		
		if (this->searchReaderFound)
		{
			bool checker = true;

			if (this->readerGenderButton.GetPlaceholder() != "MALE" && this->readerGenderButton.GetPlaceholder() != "FEMALE") 
			{
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG PHAI\n");
				checker = false;
			}

			if (this->readerStatusButton.GetPlaceholder() != "ACTIVE" && this->readerStatusButton.GetPlaceholder() != "BANNED") 
			{
				std::cerr << std::format("[ERROR] SAI DU LIEU O TRUONG TRANG THAI\n");
				checker = false;
			}

			if (checker) 
			{
				this->searchResult->info.SetFirstName(this->readerFirstNameButton.GetPlaceholder());
				this->searchResult->info.SetLastName(this->readerLastNameButton.GetPlaceholder());
				this->searchResult->info.SetGender(
					this->readerGenderButton.GetPlaceholder() == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE
				);
				this->searchResult->info.SetStatus(
					this->readerStatusButton.GetPlaceholder() == "BANNED" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE
				);

				return true;
			}
		}
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(&this->saveBtn);
	}

	return false;
}

READER_TAB_MEMBERS::ReaderInfo::ReaderInfo()
{
	this->background = HELPER::Fill(
		HELPER::Coordinate(1125, 120),
		630, 150,
		rgb(217, 217, 217),
		BLACK
	);

	this->readerFullname = Button(
		HELPER::Coordinate(1140, 138),
		600, 50,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerFullname.SetPlaceholder("Reader fullname");

	this->readerId = Button(
		HELPER::Coordinate(1140, 203),
		250, 50,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerId.SetPlaceholder("Reader ID");

	this->readerStatus = Button(
		HELPER::Coordinate(1400, 203),
		340, 50,
		BLACK,
		rgb(244, 244, 242),
		BLACK
	);
	this->readerStatus.SetPlaceholder("Reader GetStatus");


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

	this->inputController = nullptr;

	this->targetedBookID = nullptr;
}

READER_TAB_MEMBERS::ReaderIndeptDetail::ReaderIndeptDetail(LINEAR_LIST::LinearList* titleList, READER::Reader* reader)
{
	this->titleList = titleList;
	this->reader = reader;

	this->targetedBookID = nullptr;

	const int labelsCount = 5;
	this->titlesDatasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT,
		labelsCount,
		DAU_SACH_PROPERTIES::ROW_HEIGHT,
		HELPER::Coordinate(36, 120),
		HELPER::Coordinate(980, 945)
	);
	this->CreateTitlesDatasheet();
	this->titlesDatasheetController.ActivateDatasheets();

	if (this->reader != nullptr) 
	{
		this->readerInfo.UpdateReaderInfo(this->reader);
	}

	this->goBackButton = Button(
		HELPER::Coordinate(36, 940), 70, 40,
		rgb(24, 18, 43),
		rgb(236, 242, 255),
		rgb(24, 18, 43)
	);
	this->goBackButton.SetPlaceholder("<");
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::SetInputController(ELEMENTS::InputModeController* inputController)
{
	this->inputController = inputController;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::UpdateReader(READER::Reader* reader)
{
	this->InitializeFunctionalButton();
	this->InitializeBookIDButton();

	this->targetedBookID = nullptr;

	this->reader = reader;
	this->readerInfo.UpdateReaderInfo(this->reader);

	this->borrowedBooksDatassheetController = DATASHEET::Controller(
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::MAX_ROW,
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::TOP_LEFT,
		READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::DATASHEET_CHANGE_BUTTON_TOP_LEFT
	);

	this->CreateBorrowBooksDatasheet();
	this->borrowedBooksDatassheetController.ActivateDatasheets();
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Display()
{
	this->titlesDatasheetController.Display();
	this->titlesDatasheetController.DatasheetChangeButtonUpdate();

	this->borrowedBooksDatassheetController.Display();
	this->borrowedBooksDatassheetController.DatasheetChangeButtonUpdate();

	this->bookIDButton.Display();
	this->BookIDButtonOnAction();

	this->borrowBookButton.Display();
	this->BorrowButtonOnAction();

	this->returnBookButton.Display();
	this->ReturnButtonOnAction();

	this->lostBookButton.Display();
	this->LostButtonOnAction();

	this->readerInfo.Display();
	this->goBackButton.Display();
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::GoBackButtonOnAction()
{
	if (this->active == false) 
	{
		return false;
	}

	
	if (this->goBackButton.IsHover()) 
	{
		this->goBackButton.SetFillColor(rgb(130, 170, 227));
	}
	else if (this->goBackButton.LeftMouseClicked()) 
	{
		delay(100);
		this->active = false;
		this->titlesDatasheetController.DeactivateDatasheets();
		return true;
	}
	else 
	{
		this->goBackButton.SetFillColor(rgb(236, 242, 255));
	}
	return false;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::BorrowButtonOnAction()
{
	if (this->borrowBookButton.IsHover())
	{
		this->ApplyHoverStyleForFunctionalButton(this->borrowBookButton);
	}
	else if (this->borrowBookButton.LeftMouseClicked())
	{
		delay(100);
		
		bool borrowingBookProcessResult = false;
		try 
		{
			borrowingBookProcessResult = this->BorrowBook();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}

		if (borrowingBookProcessResult == true)
		{
			this->CreateBorrowBooksDatasheet();
			this->borrowedBooksDatassheetController.ActivateDatasheets();
		}
	}
	else
	{
		this->ApplyDefaultStyleForFunctionalButton(this->borrowBookButton);
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::ReturnButtonOnAction()
{
	if (this->returnBookButton.IsHover())
	{
		this->ApplyHoverStyleForFunctionalButton(this->returnBookButton);
	}
	else if (this->returnBookButton.LeftMouseClicked())
	{
		delay(100);

		bool returningBookProcessresult = false;
		try 
		{
			returningBookProcessresult = this->ReturnBook();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}

		if (returningBookProcessresult == true)
		{
			this->CreateBorrowBooksDatasheet();
			this->borrowedBooksDatassheetController.ActivateDatasheets();
		}
	}
	else
	{
		this->ApplyDefaultStyleForFunctionalButton(this->returnBookButton);
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::LostButtonOnAction()
{
	if (this->lostBookButton.IsHover())
	{
		this->ApplyHoverStyleForFunctionalButton(this->lostBookButton);
	}
	else if (this->lostBookButton.LeftMouseClicked())
	{
		delay(100);

		bool alertingLostBookProcessResult = false;
		try
		{
			alertingLostBookProcessResult = this->LostBook();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}

		if (alertingLostBookProcessResult == true)
		{
			this->CreateBorrowBooksDatasheet();
			this->borrowedBooksDatassheetController.ActivateDatasheets();
		}
	}
	else
	{
		this->ApplyDefaultStyleForFunctionalButton(this->lostBookButton);
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::BookIDButtonOnAction()
{
	if (this->bookIDButton.IsHover())
	{
		this->ApplyHoverStyleForBookIDButton();
	}
	else if (this->bookIDButton.LeftMouseClicked())
	{
		delay(100);
		this->inputController->Activate(&this->bookIDButton, &this->bookIDButton, 8, true, true, false);
	}
	else
	{
		this->ApplyDefaultStyleForBookIDButton();
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Activate()
{
	this->titlesDatasheetController.ActivateDatasheets();
	this->borrowedBooksDatassheetController.ActivateDatasheets();
	this->active = true;
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::Deactivate()
{
	this->titlesDatasheetController.DeactivateDatasheets();
	this->borrowedBooksDatassheetController.DeactivateDatasheets();
	this->active = false;
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::IsActive()
{
	return this->active == true;
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::BorrowBook()
{
	//* VALIDATE USER INPUT (start below) ----------------------------------------------------------------
	const std::string& borrowingBookID = this->bookIDButton.GetPlaceholder();
	if (borrowingBookID == "" || borrowingBookID == " " || borrowingBookID == "Book ID")
	{
		throw std::logic_error("[ERROR] USER MUST ENTER A VALID BOOK'S ID!\n");
		return false;
	}
	//* VALIDATE USER INPUT (ended below) ----------------------------------------------------------------



	//* FINDING CORRESPOND BOOK ID (start below) ---------------------------------------------------------
	const std::string& borrowingTitleISBN = borrowingBookID.substr(0, 4); //* Taking the ISBN code of the targetedBook
	BOOK_TITLE::BookTitle* correspondTitle = LINEAR_LIST::SearchByISBN(*this->titleList, borrowingTitleISBN);
	if (correspondTitle == nullptr)
	{
		throw std::logic_error(std::format("[ERROR] THE ISBN: {} NOT EXIST!\n", borrowingTitleISBN));
		return false;
	}

	LINKED_LIST::Controller titleCatalogue = correspondTitle->GetCatalogue();
	this->targetedBookID = LINKED_LIST::SearchByID(titleCatalogue, borrowingBookID);
	if (this->targetedBookID == nullptr)
	{
		throw std::logic_error(std::format("[ERROR] CANNOT FIND THE CORRESPOND BOOK'S ID: {}!\n", borrowingBookID));
		return false;
	}
	//* FINDING CORRESPOND BOOK ID (ended below) ---------------------------------------------------------



	//* Check for targetedBook's borrow-ability!
	if (this->targetedBookID->GetStatus() != BOOK::Status::AVAILABLE)
	{
		throw std::logic_error("[ERROR] BOOK IS NOT AVAILABLE TO BORROW!\n");
		return false;
	}

	DOUBLE_LINKED_LIST::Controller readerBorrowedBooks = this->reader->GetBooksCirculation();

	//* Check for number of targetedBook is borrowing!
	int readerBorrowedBookCount = 0;
	for (DOUBLE_LINKED_LIST::Pointer readerBorrowedBook = readerBorrowedBooks.First; readerBorrowedBook != nullptr; readerBorrowedBook = readerBorrowedBook->right)
	{
		if (readerBorrowedBook->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING)
		{
			readerBorrowedBookCount += 1;
		}
	}
	if (readerBorrowedBookCount > 3)
	{
		throw std::logic_error("[ERROR] CANNOT BORROW MORE THAN 3 BOOKS! RETURN BEFORE BORROWING MORE BOOK!");
		return false;
	}

	//* Check if there is any targetedBook at did not return on date!
	bool allReturnedInTime = true;
	for (DOUBLE_LINKED_LIST::Pointer currentNode = readerBorrowedBooks.First; currentNode != nullptr; currentNode = currentNode->right)
	{
		//* Check for targetedBook did not return in time!
		if (currentNode->info.IsOverdue())
		{
			allReturnedInTime = false;
			break;
		}
		
	}
	if (!allReturnedInTime)
	{
		throw std::logic_error("[ERROR] EXIST OVERDUE BOOK! RETURN ALL OVERDUE BOOK BEFORE BORROWING A NEW ONE!\n");
		return false;
	}

	//* Check for duplicate title!
	bool noDuplicateTitle = true;
	for (DOUBLE_LINKED_LIST::Pointer currentNode = readerBorrowedBooks.First; currentNode != nullptr; currentNode = currentNode->right)
	{
		//* Check for duplicate ISBN code -> duplicate title!
		if (currentNode->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING && borrowingTitleISBN.substr(0, 4).compare(currentNode->info.GetID().substr(0, 4)) == 0)
		{
			noDuplicateTitle = false;
			break;
		}
	}
	if (!noDuplicateTitle)
	{
		throw std::logic_error("[ERROR] User has borrowed another targetedBook with the same title! Cannot borrows another one!\n");
		return false;
	}

	//* BORROW BOOK PROCESS
	HELPER::Date borrowingDate; //* borrowing date is today;
	HELPER::Date returningDate = borrowingDate + 7; //* returning date is not identified yet, therefore yesterday will be assigned;
	BOOK_CIRCULATION::BookCirculation newBorrowedBook(
		this->targetedBookID->GetID(),
		borrowingDate,
		returningDate,
		BOOK_CIRCULATION::CirculationStatus::BORROWING
	);
	DOUBLE_LINKED_LIST::PushBack(readerBorrowedBooks, newBorrowedBook);
	this->targetedBookID->SetStatus(BOOK::Status::UNAVAILABLE);
	this->reader->SetBooksCirculation(readerBorrowedBooks);
	return true;
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::ReturnBook()
{
	//* VALIDATE USER INPUT (start below) ----------------------------------------------------------------
	const std::string& userTargetedReturnBookID = this->bookIDButton.GetPlaceholder();
	if (userTargetedReturnBookID == "" || userTargetedReturnBookID == " " || userTargetedReturnBookID == "Book ID")
	{
		throw std::logic_error("[ERROR] USER MUST ENTER A VALID BOOK'S ID!\n");
		return false;
	}
	//* VALIDATE USER INPUT (ended below) ----------------------------------------------------------------

	//* Finding existance of the targetedBook's id in the user's borrowing targetedBook list.
	DOUBLE_LINKED_LIST::Controller readerBookCirculationList = this->reader->GetBooksCirculation();

	bool existReaderTargetBookCirculation = false;
	DOUBLE_LINKED_LIST::Pointer targetBookCirculation = readerBookCirculationList.First;
	for (; targetBookCirculation != nullptr; targetBookCirculation = targetBookCirculation->right)
	{
		if (targetBookCirculation->info.GetID().compare(userTargetedReturnBookID) == 0)
		{
			existReaderTargetBookCirculation = true;
			break;
		}
	}
	if (!existReaderTargetBookCirculation)
	{
		throw std::logic_error(std::format("[ERROR] BOOK'S ID: {} IS NOT EXIST IN USER'S BOOK'S CIRCULATION LIST!\n", userTargetedReturnBookID));
		return false;
	}

	//* Finding the title which the targeted targetedBook belongs to.
	int indexOfCoresspondTitle = -1;
	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		if (this->titleList->nodes[i]->GetISBN().compare(userTargetedReturnBookID.substr(0, 4)) == 0)
		{
			indexOfCoresspondTitle = i;
			break;
		}
	}
	if (indexOfCoresspondTitle == -1)
	{
		throw std::logic_error(std::format("[ERROR] CANNOT FIND ANY TITLE WITH ISBN = {} IN THE TITLE LIST!\n", userTargetedReturnBookID.substr(0, 4)));
		return false;
	}

	LINKED_LIST::Controller targetedTitleCatalouge = this->titleList->nodes[indexOfCoresspondTitle]->GetCatalogue();
	bool bookExist = false;
	LINKED_LIST::Pointer targetedBook = targetedTitleCatalouge.first;
	for (; targetedBook != nullptr; targetedBook = targetedBook->next)
	{
		if (targetedBook->info.GetID().compare(userTargetedReturnBookID) == 0)
		{
			bookExist = true;
			break;
		}
	}
	if (!bookExist)
	{
		throw std::logic_error(std::format("[ERROR] CANNOT FIND ANY BOOK WITH THE ID: {}\n", userTargetedReturnBookID));
		return false;
	}

	targetedBook->info.SetStatus(BOOK::Status::AVAILABLE);
	this->titleList->nodes[indexOfCoresspondTitle]->SetCatalogue(targetedTitleCatalouge);
	targetBookCirculation->info.SetReturnDate(HELPER::Date());
	targetBookCirculation->info.SetStatus(BOOK_CIRCULATION::CirculationStatus::RETURNED);
	//DOUBLE_LINKED_LIST::RemoveNode(readerBookCirculationList, targetBookCirculation);
	this->reader->SetBooksCirculation(readerBookCirculationList);
	return true;
}

bool READER_TAB_MEMBERS::ReaderIndeptDetail::LostBook()
{
	//* VALIDATE USER INPUT (start below) ----------------------------------------------------------------
	const std::string& userTargetedLostedBookID = this->bookIDButton.GetPlaceholder();
	if (userTargetedLostedBookID == "" || userTargetedLostedBookID == " " || userTargetedLostedBookID == "Book ID")
	{
		throw std::logic_error("[ERROR] USER MUST ENTER A VALID BOOK'S ID!\n");
		return false;
	}
	//* VALIDATE USER INPUT (ended below) ----------------------------------------------------------------

	//* Finding existance of the targetedBook's id in the user's book circulations list.
	DOUBLE_LINKED_LIST::Controller readerBookCirculationList = this->reader->GetBooksCirculation();

	bool existReaderTargetBookCirculation = false;
	DOUBLE_LINKED_LIST::Pointer targetBookCirculation = readerBookCirculationList.First;
	for (; targetBookCirculation != nullptr; targetBookCirculation = targetBookCirculation->right)
	{
		if (targetBookCirculation->info.GetID().compare(userTargetedLostedBookID) == 0)
		{
			existReaderTargetBookCirculation = true;
			break;
		}
	}
	if (!existReaderTargetBookCirculation)
	{
		throw std::logic_error(std::format("[ERROR] BOOK'S ID: {} IS NOT EXIST IN USER'S BOOK'S CIRCULATION LIST!\n", userTargetedLostedBookID));
		return false;
	}

	targetBookCirculation->info.SetStatus(BOOK_CIRCULATION::CirculationStatus::LOSTED);
	return true;
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
	DOUBLE_LINKED_LIST::Controller readerBookCirculationList = this->reader->GetBooksCirculation();

	int listSize = DOUBLE_LINKED_LIST::Size(readerBookCirculationList);
	this->borrowedBooksDatassheetController.SetDatasheetCount(
		listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
	);
	this->borrowedBooksDatassheetController.InitializeDatasheets();

	for (int i = 0; i < this->borrowedBooksDatassheetController.GetDatasheetCount(); ++i)
	{
		this->borrowedBooksDatassheetController[i] = DATASHEET::Datasheet(
			this->borrowedBooksDatassheetController.GetRecordCount(),
			this->borrowedBooksDatassheetController.GetAttributeCount(),
			this->borrowedBooksDatassheetController.GetRowHeight(),
			this->borrowedBooksDatassheetController.GetTopLeft(),
			(std::string*)READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
			(int*)READER_PROPERTIES::READER_DETAIL_PROPERTIES::BORROWED_BOOK_DATASHEET_PROPERTIES::CHARACTER_LIMITS
		);
	}

	if (DOUBLE_LINKED_LIST::Empty(readerBookCirculationList))
	{
		return;
	}

	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	for (DOUBLE_LINKED_LIST::Pointer currentNode = readerBookCirculationList.First; currentNode != nullptr; currentNode = currentNode->right)
	{
		++recordIndex;
		if (recordIndex > this->borrowedBooksDatassheetController.GetRecordCount() - 1)
		{
			recordIndex = 1;
		}
		if (recordIndex % (this->borrowedBooksDatassheetController.GetRecordCount() - 1) == 1)
		{
			sheetIndex += 1;
		}

		std::string* data = new std::string[this->borrowedBooksDatassheetController.GetAttributeCount()];
		data[0] = std::to_string(++order);
		data[1] = currentNode->info.GetID();
		data[2] = currentNode->info.GetBorrowDate().Stringify();
		data[3] = currentNode->info.GetReturnDate().Stringify();
		data[4] = currentNode->info.StringfyStatus();

		this->borrowedBooksDatassheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::InitializeFunctionalButton()
{
	this->borrowBookButton = Button(HELPER::Coordinate(1275, 940), 100, 40);
	this->borrowBookButton.SetPlaceholder("BORROW");
	this->ApplyDefaultStyleForFunctionalButton(this->borrowBookButton);
	
	this->returnBookButton = Button(HELPER::Coordinate(1390, 940), 100, 40);
	this->returnBookButton.SetPlaceholder("RETURN");
	this->ApplyDefaultStyleForFunctionalButton(this->returnBookButton);

	this->lostBookButton = Button(HELPER::Coordinate(1505, 940), 100, 40);
	this->lostBookButton.SetPlaceholder("LOST");
	this->ApplyDefaultStyleForFunctionalButton(this->lostBookButton);
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::InitializeBookIDButton()
{
	this->bookIDButton = Button(HELPER::Coordinate(1275, 870), 330, 50);
	this->bookIDButton.SetPlaceholder("Book ID");
	this->ApplyDefaultStyleForBookIDButton();
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::ApplyDefaultStyleForFunctionalButton(Button& button)
{
	button.SetFillColor(rgb(236, 242, 255));
	button.SetBorderColor(BLACK);
	button.SetTextColor(BLACK);
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::ApplyHoverStyleForFunctionalButton(Button& button)
{
	button.SetFillColor(rgb(130, 170, 227));
	button.SetBorderColor(BLACK);
	button.SetTextColor(WHITE);
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::ApplyDefaultStyleForBookIDButton()
{
	this->bookIDButton.SetFillColor(rgb(73, 84, 100));
	this->bookIDButton.SetBorderColor(rgb(73, 84, 100));
	this->bookIDButton.SetTextColor(rgb(244, 244, 242));
}

void READER_TAB_MEMBERS::ReaderIndeptDetail::ApplyHoverStyleForBookIDButton()
{
	this->bookIDButton.SetFillColor(rgb(246, 241, 241));
	this->bookIDButton.SetBorderColor(BLACK);
	this->bookIDButton.SetTextColor(rgb(73, 84, 100));
}

//----------------------------------------------------------------------------------------------------------------------------

void DanhSachTheDocGiaView::CreateDatasheetsFromList(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controller* datasheetController) {

	int attributeCount = 0;
	AVL_TREE::Size(danhSachThedocGia, attributeCount);
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
			(std::string*)READER_PROPERTIES::LABEL_PLACEHOLDERS, (int*)READER_PROPERTIES::CHARACTER_LIMITS
		);
	}

	Stack<AVL_TREE::Pointer> stk;
	AVL_TREE::Pointer currentNode = danhSachThedocGia;
	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	do {
		while (currentNode != nullptr) {
			stk.Push(currentNode);
			currentNode = currentNode->left;
		}

		if (stk.Empty() == false) {
			currentNode = stk.Pop();
			
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
			data[4] = currentNode->info.StringifyGender();
			data[5] = currentNode->info.StringfyStatus();

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
			(std::string*)READER_PROPERTIES::LABEL_PLACEHOLDERS, (int*)READER_PROPERTIES::CHARACTER_LIMITS
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
		data[4] = arr[i]->info.StringifyGender();
		data[5] = arr[i]->info.StringfyStatus();

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
	this->inputController = inputController;
	
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 935);
	HELPER::Coordinate toRightBtnTopLeft(86, 935);

	this->datasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT, READER_PROPERTIES::PROPERTIES_COUNT, 
		READER_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
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

	this->searchField = READER_TAB_MEMBERS::SearchField(this->readerList, this->inputController);
	this->searchField.Activate();
	this->readerIndeptDetail = READER_TAB_MEMBERS::ReaderIndeptDetail(this->titleList, nullptr);

	this->newItemForm = new READER_TAB_MEMBERS::NewReaderForm(this->readerList, this->inputController);
	this->editItemForm = new READER_TAB_MEMBERS::EditReaderInfoForm(this->readerList, this->inputController);
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
					this->readerIndeptDetail.SetInputController(this->inputController);
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
				this->newItemForm->Display();
				this->newItemForm->FormOnAction();
				bool formSubmitted = this->newItemForm->SubmitForm();
				if (formSubmitted) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
				}
				break;
			}
			case (1): {
				this->editItemForm->Display();
				this->editItemForm->FormOnAction();
				bool confirmSave = this->editItemForm->SubmitForm();
				if (confirmSave) {
					DanhSachTheDocGiaView::CreateDatasheetsFromList(*this->readerList, &this->datasheetController);
				}
				break;
			}
			case (2): {
				this->deleteItemForm.Display(*this->readerList, *this->inputController);
				bool confirmDelete = this->deleteItemForm.SubmitForm(*this->readerList, *this->inputController);
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

