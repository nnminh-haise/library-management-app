#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../UI/Elements.h"

struct SearchField {
	ELEMENTS::Fill* background;
	ELEMENTS::Button* title;
	ELEMENTS::Button* inputSearchBox;
	ELEMENTS::Button* searchStatusBox;

	SearchField();

	void Display();
};

struct NewListItemForm {
	ELEMENTS::Fill* background;
	ELEMENTS::Button* title;
	ELEMENTS::Button* maThe;
	ELEMENTS::Button* ho;
	ELEMENTS::Button* ten;
	ELEMENTS::Button* phai;
	ELEMENTS::Button* submit;

	NewListItemForm();

	void Display();
};


class DanhSachTheDocGiaView {
private:
	bool active;
	DATASHEET::Controler controler;
	ELEMENTS::Button sheetChange[2];
	int listManipulationButtonStatus;
	ELEMENTS::Button listManipulateButton[3];

	SearchField searchField;
	NewListItemForm newItemForm;

private:
	void CreateDatasheetsFromDatabase(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler& controler);

public:
	DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia);

	void Run(ELEMENTS::InputModeController& InputController);
};
