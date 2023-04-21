#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

struct SearchField {
	HELPER::Fill* background;
	Button* title;
	Button* inputSearchBox;
	Button* searchStatusBox;

	SearchField();

	void Display();
};

struct NewListItemForm {
	HELPER::Fill* background;
	Button* title;
	Button* maThe;
	Button* ho;
	Button* ten;
	Button* phai;
	Button* submit;

	NewListItemForm();

	~NewListItemForm();

	void Display();

	bool SubmitForm(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);
};

struct DeleteItemInListForm {
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

struct EditItemInListForm {
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

class DanhSachTheDocGiaView {
private:
	bool active;
	DATASHEET::Controller datasheetController;
	int listManipulationButtonStatus;
	Button listManipulateButton[3];
	bool defaultOrder;

	SearchField searchField;
	NewListItemForm newItemForm;
	DeleteItemInListForm deleteItemForm;
	EditItemInListForm editItemForm;

public:
	void CreateDatasheetsFromList(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controller* controller);

	void CreateDatasheetsFromArr(AVL_TREE::Pointer* arr, int arrSize, DATASHEET::Controller* controller);

	DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia);

	void Run(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController);
};
