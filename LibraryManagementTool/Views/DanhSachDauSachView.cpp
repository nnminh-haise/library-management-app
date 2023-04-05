#include "DanhSachDauSachView.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>

void DANH_SACH_DAU_SACH_VIEW::DefaultDatasheetBackgroundProperties(ELEMENTS::Fill& datasheet) {
	datasheet.fillColor = rgb(239, 245, 245);
	datasheet.borderColor = rgb(11, 36, 71);
}

void DANH_SACH_DAU_SACH_VIEW::Run() {
	//* Draw datasheet

	ELEMENTS::Fill datasheetBackground(HELPER::Coordinate(530, 150), 1200, 800);
	DANH_SACH_DAU_SACH_VIEW::DefaultDatasheetBackgroundProperties(datasheetBackground);
	datasheetBackground.Draw();

	outtextxy(700, 500, (char*)"DAU SACH VIEW");
}
