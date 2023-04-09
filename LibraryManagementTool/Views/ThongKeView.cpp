#include "ThongKeView.h"

#include <iostream>
#include <string>
#include <format>

void ThongKeView::CreateDatasheets(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler) {
	controler.datasheetCount = 1;
	controler.sheets = new DATASHEET::Datasheet[controler.datasheetCount];
	controler.activeSheet = 0;

	std::string labelPlaceholder[] = {"STT", "ISBN", "TEN SACH", "THE LOAI", "TAC GIA", "SO SACH DA MUON"};
	int characterLimit[] = { 2, 4, 30, 10, 20, 4 };

	controler.sheets[0] = DATASHEET::Datasheet(
		controler.rowCount, controler.columnCount, controler.rowHeight, controler.topLeft,
		labelPlaceholder, characterLimit
	);
}

ThongKeView::ThongKeView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {
	this->active = false;
	HELPER::Coordinate datasheetTopLeft(36, 120);

	this->controler = DATASHEET::Controler(
		11, 6, DAU_SACH_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheets(dsDauSach, controler);

}

void ThongKeView::Run() {
	this->controler.Display();

}
