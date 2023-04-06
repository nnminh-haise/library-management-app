#include "DanhSachTheDocGia.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../TheDocGia/TheDocGia.h"

#include <iostream>
#include <format>
#include <string>



void DANH_SACH_THE_DOC_GIA_VIEW::Run(AVL_TREE::Pointer& danhSachTheDocGia) {
	
	//* Setup background
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, CONSTANTS::WINDOW_DIMENSION.width, CONSTANTS::WINDOW_DIMENSION.height);

	//* Setup UI elements
	std::string placeholders[7] = { "STT", "MA THE", "HO", "TEN", "PHAI", "TRANG THAI", "SACH DANG MUON" };
	int characterLimits[7] = { 3, 6, 30, 10, 3, 9, 10 };

	//* Setup view loop
	char inputKey{};
	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {

		//* Display elements

		//* Key register
		inputKey = getch();

		//* View's logic
	}

	//* Clear View
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, CONSTANTS::WINDOW_DIMENSION.width, CONSTANTS::WINDOW_DIMENSION.height);
}
