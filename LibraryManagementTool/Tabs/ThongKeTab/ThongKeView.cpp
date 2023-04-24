#include "ThongKeView.h"

#include <iostream>
#include <string>
#include <format>

void ThongKeView::CreateDatasheets(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controller& datasheetController) {
	datasheetController.SetDatasheetCount(1);
	datasheetController.InitializeDatasheets();

	std::string labelPlaceholder[] = {"STT", "ISBN", "TEN SACH", "THE LOAI", "TAC GIA", "SO SACH DA MUON"};
	int characterLimit[] = { 2, 4, 30, 10, 20, 4 };

	datasheetController[0] = DATASHEET::Datasheet(
		datasheetController.GetRecordCount(), 
		datasheetController.GetAttributeCount(), 
		datasheetController.GetRowHeight(), 
		datasheetController.GetTopLeft(),
		labelPlaceholder, characterLimit
	);
}

ThongKeView::ThongKeView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& titleList) {
	this->active = false;
	HELPER::Coordinate datasheetTopLeft(36, 120);

	this->datasheetController = DATASHEET::Controller(
		11, 6, DAU_SACH_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheets(titleList, datasheetController);

}

void ThongKeView::Run() {
	this->datasheetController.Display();

}
