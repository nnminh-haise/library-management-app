#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace READER_TAB_MEMBERS
{
	struct SearchField
	{
		bool status;
		bool showSearchResult;
		HELPER::Fill background;
		Button title;
		Button searchBox;
		Button resultBox;
		AVL_TREE::Pointer* readerList;
		AVL_TREE::Pointer searchResult;
		ELEMENTS::InputModeController* inputController;

	public:
		SearchField();

		SearchField(AVL_TREE::Pointer* readerList, ELEMENTS::InputModeController* inputController);

		void Deactivate();

		void Activate();

		bool IsActive();

		void SearchBoxOnActionLogic();

		int SearchReaderAlgorithm();

		void ProcessingSearchResult();

		void Display();
		
		void ResultBoxDefaultStyling();

		void ResultBoxFoundedStyling();

		void ResultBoxOnAction();
	};

	struct NewListItemForm 
	{
		bool status;
		HELPER::Fill* background;
		Button* title;
		Button* maThe;
		Button* ho;
		Button* ten;
		Button* phai;
		Button* createDanhMucSach;

		NewListItemForm();

		~NewListItemForm();

		void Display();

		bool SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);
	};

	struct DeleteItemInListForm 
	{
		bool status;
		HELPER::Fill* background;
		Button* title;
		Button* maThe;
		Button* hoTen;
		Button* trangThai;
		Button* phai;
		Button* deleteBtn;
		bool searchTargetFound;
		AVL_TREE::Pointer searchResult;

		DeleteItemInListForm();

		~DeleteItemInListForm();

		void Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);

		bool SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);
	};

	struct EditItemInListForm 
	{
		bool status;
		HELPER::Fill* background;
		Button* title;
		Button* maThe;
		Button* ho;
		Button* ten;
		Button* trangThai;
		Button* phai;
		Button* saveBtn;
		bool searchTargetFound;
		AVL_TREE::Pointer searchResult;

		EditItemInListForm();

		~EditItemInListForm();

		void Display(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);

		bool SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);
	};

	struct ReaderInfo 
	{
		ReaderInfo();

		void UpdateReaderInfo(READER::Reader* reader);

		void Display();

		HELPER::Fill background;
		Button readerFullname;
		Button readerId;
		Button readerStatus;
	};

	class ReaderIndeptDetail 
	{
	public:
		ReaderIndeptDetail();

		ReaderIndeptDetail(LINEAR_LIST::LinearList* titleList, READER::Reader* reader);

		void SetInputController(ELEMENTS::InputModeController* inputController);

		void UpdateReader(READER::Reader* reader);

		void Display();

		bool GoBackButtonOnAction();

		void BorrowButtonOnAction();

		void ReturnButtonOnAction();

		void BookIDButtonOnAction();

		void Activate();

		void Deactivate();

		bool IsActive();

	private:
		bool BorrowBook();

		void CreateTitlesDatasheet();

		void CreateBorrowBooksDatasheet();

		void InitializeFunctionalButton();

		void InitializeBookIDButton();

	private:
		void ApplyDefaultStyleForFunctionalButton(Button& button);

		void ApplyHoverStyleForFunctionalButton(Button& button);

		void ApplyDefaultStyleForBookIDButton();

		void ApplyHoverStyleForBookIDButton();

	private:
		bool active;
		LINEAR_LIST::LinearList* titleList;
		READER::Reader* reader;

		DATASHEET::Controller titlesDatasheetController;
		DATASHEET::Controller borrowedBooksDatassheetController;
		ELEMENTS::InputModeController* inputController;

		Button bookIDButton;
		Button borrowBookButton;
		Button returnBookButton;
		Button goBackButton;

		ReaderInfo readerInfo;

		BOOK::Book* borrowBook;
		BOOK::Book* returnBook;
	};
}

class DanhSachTheDocGiaView {
private:
	bool active;
	DATASHEET::Controller datasheetController;
	int listManipulationButtonStatus;
	Button listManipulateButton[3];
	bool defaultOrder;

	READER_TAB_MEMBERS::SearchField searchField;
	READER_TAB_MEMBERS::NewListItemForm newItemForm;
	READER_TAB_MEMBERS::DeleteItemInListForm deleteItemForm;
	READER_TAB_MEMBERS::EditItemInListForm editItemForm;
	READER_TAB_MEMBERS::ReaderIndeptDetail readerIndeptDetail;

	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;
	ELEMENTS::InputModeController* inputController;

public:
	void CreateDatasheetsFromList(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controller* controller);

	void CreateDatasheetsFromArr(AVL_TREE::Pointer* arr, int arrSize, DATASHEET::Controller* controller);

	DanhSachTheDocGiaView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController);

	void Run();
};

