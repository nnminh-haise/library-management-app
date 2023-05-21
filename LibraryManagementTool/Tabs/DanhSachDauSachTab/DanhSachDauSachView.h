#pragma once

#include "DanhSachDauSachStyling.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/Package.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace DAU_SACH_TAB
{
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* titleList, DATASHEET::Controller& datasheetController);

	void CreateDatasheetsWithSortedCategory(BOOK_TITLE::BookTitle** sortedList, int listSize, DATASHEET::Controller& datasheetController);

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct BookCreatingSection
	{
		BookCreatingSection();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

	private:
		void InitializeElements();

	public:
		bool active_;
		HELPER::Fill background_;
		Button titleButton_;
		Button saveButton_;
		Button inputField_[5];
	};

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct CatalogueCreatingSection
	{
		CatalogueCreatingSection();

		CatalogueCreatingSection(LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController);

		~CatalogueCreatingSection();

		void InitializeCatalogue(int amount, std::string isbn);

		void InputFieldOnUpdate();

		void SaveButtonOnUpdate();

		void IndexChangeButtonOnAction();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

	private:
		void InitializeElements();

	public:
		LINEAR_LIST::LinearList* titleList_;
		ELEMENTS::InputModeController* inputController_;

		bool active;
		BookCreatingSection* items;
		int itemsCount;
		int activeField;
		Button indexChangeButtons[2];
	};

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct TitleCreatingSection
	{
	public:
		TitleCreatingSection();

		TitleCreatingSection(Package* package);

		bool InputFieldOnUpdate();

		bool CreateCatalogueButtonOnUpdate();

		bool SubmitButtonOnUpdate();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		bool GoBackButtonOnAction();

	private:
		void InitializeElements();

		bool ISBNInputFieldCheckProcess();

		bool CatalogueSizeCheckProcess();

	public:
		Package* package_;

		bool active;
		bool sachAddFieldDisplay;
		HELPER::Fill background;
		HELPER::Fill backdrop;
		Button title;
		Button createCatalogueButton_;
		Button inputField_[7];
		Button alertField_[2];
		Button goBackButton;
		Button submit;

		bool ISBNCheckProcessResult_ = false;
		bool catalogueSizeProcessResult_ = false;
		bool goodInputFieldCheckResult_ = false;

		CatalogueCreatingSection catalogueCreatingSection;
	};

	struct TitleDetailDisplayField
	{
		bool active;
		BOOK_TITLE::BookTitle* targetedTitle;
		HELPER::Fill background;
		Button title;
		Button titleDetails[5];
		Button goBackBtn;
		DATASHEET::Controller bookListDatasheetController;
		Button deleteBookBtn;
		LINKED_LIST::Pointer deleteBook;

		TitleDetailDisplayField();

		void Destructor();

		void Initialize(BOOK_TITLE::BookTitle* title);

		void CreateBookListDatasheet();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

		void DeleteBookButtonOnAction();

		void ResetDeleteBookButton();

		bool GoBackButtonOnAction();
	};

	struct SearchField
	{
		bool active;
		bool searchFound;
		HELPER::Fill* background;
		Button* title;
		Button* inputSearchBox;
		Button* searchStatusBox;
		TitleDetailDisplayField targetDetails;

		SearchField();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void OnAction(ELEMENTS::InputModeController* InputController);

		void Display();
	};
}


namespace CATEGORY_LINKED_LIST {
	struct Node {
		std::string info;
		Node* next;

		Node(std::string info, Node* next);
	};
	typedef Node* Pointer;

	void Initialzie(Pointer& First);

	bool Empty(const Pointer& First);

	void PushFront(Pointer& First, std::string info);

	void InsertOrder(Pointer& First, std::string info);

	void Traversal(const Pointer& First);
}


class DauSachTab
{
public:
	DauSachTab(Package* package);

	void Destructor();

	void SortByCategory();

	void Run();

private:
	bool active;
	bool datasheetDisplayFlag;
	DATASHEET::Controller datasheetController;
	ELEMENTS::InputModeController* inputController;
	LINEAR_LIST::LinearList* titleList;
	BOOK_TITLE::BookTitle** titleListSortedByCategory;
	Button functionalButtons[3];

private:
	DAU_SACH_TAB::SearchField searchField;

	DAU_SACH_TAB::TitleCreatingSection titleCreatingSection;

	DAU_SACH_TAB::TitleDetailDisplayField titleDetailField;

private:
	Package* package_;
};

