#pragma once

#include "../TheDocGia/TheDocGia.h"
#include "Elements.h"



class DanhSachTheDocGiaView {
private:
	bool active;
	DATASHEET::Controler controler;
	ELEMENTS::Button sheetChange[2];

private:
	void DatasheetChangeBTNHover(ELEMENTS::Button& btn);

	void DatasheetChangeBTNProperties(ELEMENTS::Button& btn);

	void CreateDatasheetsFromDatabase(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler& controler);

public:
	DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia);

	void Run();
};
