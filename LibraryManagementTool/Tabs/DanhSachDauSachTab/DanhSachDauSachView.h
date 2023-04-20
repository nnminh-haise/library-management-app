#pragma once

#include "DanhSachDauSachStyling.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace DAU_SACH_TAB {
	struct SearchField {
		HELPER::Fill* background;
		Button* title;
		Button* inputSearchBox;
		Button* searchStatusBox;

		SearchField();

		void Display();
	};
}

class DauSachTab {
private:
	bool active;
	bool displaDatasheet;
	DATASHEET::Controller controler;
	Button listManipulateButtons[3];

	DAU_SACH_TAB::SearchField searchField;

private:
	void SortList(LINEAR_LIST::LinearList& dsDauSach);


	void CreateDatasheetsFromList(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controller& controler);

public:
	DauSachTab(LINEAR_LIST::LinearList& danhSachDauSach);

	void Run();
};

