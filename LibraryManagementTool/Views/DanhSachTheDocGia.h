#pragma once

#include "../TheDocGia/TheDocGia.h"
#include "Elements.h"

struct SearchField {
	ELEMENTS::Fill background;
	ELEMENTS::Button title;
	ELEMENTS::Button inputSearchBox;
	ELEMENTS::Button searchStatusBox;

	void BackgroundStyling();

	void TitleStyling();

	void SearchBoxStyling();

	void StatusBoxStyling();

	SearchField();

	void Display();
};

struct NewListItemForm {
	ELEMENTS::Fill background;
	ELEMENTS::Button title;
	ELEMENTS::Button maThe;
	ELEMENTS::Button ho;
	ELEMENTS::Button ten;
	ELEMENTS::Button phai;
	ELEMENTS::Button submit;

	void BackgroundStyling();

	void TitleStyling();

	void InputBoxStyling(ELEMENTS::Button& btn);

	void SubmitButtonStyling();

	void InputBoxHoverProperties(ELEMENTS::Button* btn);

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
	void DatasheetChangeBTNHover(ELEMENTS::Button& btn);

	void DatasheetChangeBTNProperties(ELEMENTS::Button& btn);

	void CreateDatasheetsFromDatabase(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler& controler);

	void ListManipulateBTNDefaultProperties(ELEMENTS::Button& btn);

	void ListManipulateBTNHoverProperties(ELEMENTS::Button& btn);

	void NewItemButtonActiveProperties(ELEMENTS::Button& btn);

public:
	DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia);

	void Run(ELEMENTS::InputModeController& InputController);
};
