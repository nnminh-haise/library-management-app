#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/Package.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"

namespace READER_TAB_MEMBERS
{
	struct SearchField
	{
	public:
		SearchField();

		SearchField(Package* package);

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

		bool status;
		bool showSearchResult;
		HELPER::Fill background;
		Button title;
		Button searchBox;
		Button resultBox;
		AVL_TREE::Pointer searchResult = nullptr;
		Package* package_ = nullptr;
	};

	class NewReaderForm
	{
	public:
		NewReaderForm(Package* package);

		void Display();

		void FormOnAction();

		bool SubmitForm();

	private:
		bool status;
		HELPER::Fill background;
		Button title;
		Button readerIDButton;
		Button readerFirstNameButton;
		Button readerLastNameButton;
		Button readerSexButton;
		Button submitButton;

		Package* package_{ nullptr };

		int readerIndex;
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
		AVL_TREE::Pointer searchResult{nullptr};

		Package* package_{ nullptr };

		DeleteItemInListForm();

		~DeleteItemInListForm();

		void Display(Package* package);

		bool SubmitForm(Package* package);
	};

	class EditReaderInfoForm
	{
	public:
		EditReaderInfoForm(Package* package);

		void ReaderIDButtonOnAction();

		void Display();

		void AssignReaderOldInfoToFields();

		void FormOnAction();

		bool SearchReaderProcess();

		bool SubmitForm();

	private:
		bool status;
		HELPER::Fill background;
		Button title;
		Button readerIDButton;
		Button readerFirstNameButton;
		Button readerLastNameButton;
		Button readerStatusButton;
		Button readerGenderButton;
		Button saveBtn;
		int searchReaderFound;
		bool assignReaderOldInfo;

		AVL_TREE::Pointer searchResult{nullptr};

		Package* package_{ nullptr };
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

		ReaderIndeptDetail(Package* package, READER::Reader* reader);

		void UpdateReader(READER::Reader* reader);

		void Display();

		bool GoBackButtonOnAction();

		void BorrowButtonOnAction();

		void ReturnButtonOnAction();

		void LostButtonOnAction();

		void BookIDButtonOnAction();

		void Activate();

		void Deactivate();

		bool IsActive();

	private:
		bool BorrowBook();

		bool ReturnBook();

		bool LostBook();

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
		Package* package_{ nullptr };
		READER::Reader* reader{ nullptr };

		DATASHEET::Controller titlesDatasheetController;
		DATASHEET::Controller borrowedBooksDatassheetController;

		Button bookIDButton;
		Button borrowBookButton;
		Button returnBookButton;
		Button lostBookButton;
		Button goBackButton;

		ReaderInfo readerInfo;

		BOOK::Book* targetedBookID;
	};
}

class DanhSachTheDocGiaView : public View
{
public:
	void CreateDatasheetsFromList(Package* package, DATASHEET::Controller* datasheetController);

	void CreateDatasheetsFromArr(Package* package, DATASHEET::Controller* datasheetController);

	DanhSachTheDocGiaView(Package* package);

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	int Run() override;

private:
	using View::status_;

	Package* package_ = nullptr;

	DATASHEET::Controller datasheetController;
	int listManipulationButtonStatus;
	Button listManipulateButton[3];
	bool defaultOrder;

	READER_TAB_MEMBERS::SearchField searchField;
	READER_TAB_MEMBERS::NewReaderForm* newItemForm;
	READER_TAB_MEMBERS::DeleteItemInListForm deleteItemForm;
	READER_TAB_MEMBERS::EditReaderInfoForm* editItemForm;
	READER_TAB_MEMBERS::ReaderIndeptDetail readerIndeptDetail;
};
