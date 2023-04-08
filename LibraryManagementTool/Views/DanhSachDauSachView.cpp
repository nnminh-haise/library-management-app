#include "DanhSachDauSachView.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>



void DANH_SACH_DAU_SACH_VIEW::Run(LINEAR_LIST::LinearList& danhSachDauSach) {
	//* Create datasheet
	int columnCount = 8;
	int rowCount = 16;
	int rowHeight = 50;
	std::string datafieldplaceholders[] = { "...", "...", "...", "...", "...", "...", "...", "..." };
	std::string labelPlaceholders[] = { "STT", "ISBN", "TEN SACH", "SO TRANG", "TAC GIA", "NXB", "THE LOAI", "DANH MUC SACH" };
	int characterLimits[] = { 3, 4, 30, 3, 20, 4, 10, 8 };
	HELPER::Coordinate dataSheetTopLeft(36, 120);

	DATASHEET::Datasheet datasheet(rowCount, columnCount, rowHeight, dataSheetTopLeft, labelPlaceholders, characterLimits);
	
	std::string data[] = {
		"2", "URWX", "CAY CAM NGOT CUA TOI", "250", "JOSE MAURO DE VASCONCELOS", "2012", "TIEU THUYET", "DANH MUC SACH"
	};

	datasheet.UpdateNewPlaceholder(data, 2);

	datasheet.Display();
}
