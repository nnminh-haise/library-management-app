#pragma once

#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "DanhSachDauSachStyling.h"

namespace DANH_SACH_DAU_SACH_TAB {
	struct SearchField {
		HELPER::Fill* background;
		Button* title;
		Button* inputSearchBox;
		Button* searchStatusBox;

		SearchField();

		void Display();
	};

	// struct NewListItemForm {
	// 	ELEMENTS::Fill* background;
	// 	ELEMENTS::Button* title;
	// 	ELEMENTS::Button* submit;

	// 	ELEMENTS::Button* maThe;
	// 	ELEMENTS::Button* ho;
	// 	ELEMENTS::Button* ten;
	// 	ELEMENTS::Button* phai;

	// 	NewListItemForm();

	// 	~NewListItemForm();

	// 	void Display();

	// 	bool SubmitForm(LINEAR_LIST::LinearList& danhSachDauSach, ELEMENTS::InputModeController& InputController);
	// };
}

class DanhSachDauSachView {
private:
	bool active;
	bool displaDatasheet;
	DATASHEET::Controler controler;
	Button sheetChange[2];
	Button listManipulateButtons[3];

	DANH_SACH_DAU_SACH_TAB::SearchField searchField;

private:
	void DatasheetChangeBTNHover(Button& btn);

	void DatasheetChangeBTNProperties(Button& btn);

	void CreateDatasheetsFromList(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler);

public:
	DanhSachDauSachView(LINEAR_LIST::LinearList& danhSachDauSach);

	void Run();
};

