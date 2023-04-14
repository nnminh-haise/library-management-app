#pragma once

#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"


class DanhSachDauSachView {
private:
	bool active;
	DATASHEET::Controler controler;
	ELEMENTS::Button sheetChange[2];

private:
	void DatasheetChangeBTNHover(ELEMENTS::Button& btn);

	void DatasheetChangeBTNProperties(ELEMENTS::Button& btn);

	void CreateDatasheetsFromList(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler);

public:
	DanhSachDauSachView(LINEAR_LIST::LinearList& danhSachDauSach);

	void Run();
};

