#pragma once

#include "DanhSachDauSachStyling.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace DAU_SACH_TAB {
	/*
	 * Function creates datasheets from the list.
	 * The datasheets then stored inside the datasheet's controller.
	 * 
	 * Function takes in two references, the first one is the list which store the data will be presented on the datasheet.
	 * The second one is the datasheet's controller.
	 * Function returns no value.
	*/
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* titleList, DATASHEET::Controller& datasheetController);

	void CreateDatasheetsWithSortedCategory(DAU_SACH::DauSach** sortedList, int listSize, DATASHEET::Controller& datasheetController);

	/*
	 * This is a graphical field, with the main purpose is for searching the data on the datasheet.
	 * 
	 * Struct gets initialzied as soon as there is any initialization of the related object happends.
	 * You can draw out the search field with @Display method.
	
	! The logic behind the struct is not written yet!
	*/
	struct SearchField {
		HELPER::Fill* background;
		Button* title;
		Button* inputSearchBox;
		Button* searchStatusBox;

		SearchField();

		void Display();
	};

	/*
	 * This is a graphical field, represented as a form, with the main purpose is for adding new item into the list.
	 * Users have to input the data into the correct field and submit the form in order to save the data into the list.
	 * 
	 * Struct gets initialzied as soon as there is any initialization of the related object happends.
	 * You can draw out the form with @Display method.
	*/
	struct SachAddField {
		bool onDisplay;
		HELPER::Fill background;
		Button title;
		Button savebtn;
		Button inputField[5];

		SachAddField();

		void Display();
	};

	/*
	 * This is a controller for the @SachAddField. There will be many form of @SachAddField. Therefore the main purpose of this controller
	 * is to manage and simplfied the posible task when interact with many form. The number of form is equal to the number of @DanhMucSach.
	 * 
	 * Struct gets initialzied as soon as there is any initialization of the related object happends.
	 * You can draw one current form with @Display method.
	*/
	struct SachAddFieldController {
		SachAddField* items;
		int itemsCount;
		int activeField;
		Button indexChangeButtons[2];

		SachAddFieldController();

		~SachAddFieldController();

		void Initialize(int amount, std::string ISBN);

		void SachAddFieldOnUpdate(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		void IndexChangeButtonOnAction();

		void Display();
	};

	/*
	 * This is a graphical form for taking in the date for each Book,
	 * User must filled out all the input field and press add button.
	 * Then a set of form will be generated, the user must filled out
	 * the following forms in order to complete the process.
	 * 
	 * Struct gets initialzied as soon as there is any initialization of the related object happends.
	 * You can draw the form with @Display method.
	*/
	struct ItemAddField {
		bool onDisplay;
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

		void Display(LINEAR_LIST::LinearList& titleList, ELEMENTS::InputModeController& InputController);

		bool GoBackButtonOnAction();
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

	bool IsEmpty(const Pointer& First);

	void InsertFirst(Pointer& First, std::string info);

	void InsertOrder(Pointer& First, std::string info);

	void Traversal(const Pointer& First);
}


class DauSachTab {
private:
	bool active;
	bool datasheetDisplayFlag;
	DATASHEET::Controller datasheetController;
	ELEMENTS::InputModeController* inputController;
	LINEAR_LIST::LinearList* titleList;
	DAU_SACH::DauSach** titleListSortedByCategory;
	Button listManipulateButtons[3];

private:
	DAU_SACH_TAB::SearchField searchField;

	DAU_SACH_TAB::ItemAddField itemAddField;

public:
	DauSachTab(LINEAR_LIST::LinearList* danhSachDauSach, ELEMENTS::InputModeController* InputController);

	void Destructor();

	void SortByCategory();

	void Run();
};

