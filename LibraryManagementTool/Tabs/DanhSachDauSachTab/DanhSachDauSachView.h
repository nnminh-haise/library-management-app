#pragma once

#include "DanhSachDauSachStyling.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace DAU_SACH_TAB
{
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* titleList, DATASHEET::Controller& datasheetController);

	void CreateDatasheetsWithSortedCategory(BOOK_TITLE::BookTitle** sortedList, int listSize, DATASHEET::Controller& datasheetController);

	struct SachAddField
	{
		bool active;
		HELPER::Fill background;
		Button title;
		Button savebtn;
		Button inputField[5];

		SachAddField();

		void Activate();

		void Deactivate();

		bool DisplayStatus();

		void Display();
	};

	struct SachAddFieldController
	{
		bool active;
		SachAddField* items;
		int itemsCount;
		int activeField;
		Button indexChangeButtons[2];

		SachAddFieldController();

		~SachAddFieldController();

		void Initialize(int amount, std::string isbn);

		void SachAddFieldOnUpdate(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		void IndexChangeButtonOnAction();

		void Activate();

		void Deactivate();

		bool DisplayStatus();

		void Display();
	};

	struct ItemAddField
	{
		bool active;
		bool sachAddFieldDisplay;
		HELPER::Fill background;
		HELPER::Fill backdrop;
		Button title;
		Button createDanhMucSach;
		Button inputField[7];
		Button goBackButton;
		Button submit;

		SachAddFieldController sachAddFieldController;

		ItemAddField();

		bool ItemAddFieldOnUpdate(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		void Activate();

		void Deactivate();

		bool DisplayStatus();

		void Display(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		bool GoBackButtonOnAction();
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

		bool DisplayStatus();

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

		bool DisplayStatus();

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

	DAU_SACH_TAB::ItemAddField itemAddField;

	DAU_SACH_TAB::TitleDetailDisplayField titleDetailField;

public:
	DauSachTab(LINEAR_LIST::LinearList* danhSachDauSach, ELEMENTS::InputModeController* InputController);

	void Destructor();

	void SortByCategory();

	void Run();
};

