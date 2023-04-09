#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../TheDocGia/TheDocGia.h"
#include "../DauSach/DauSach.h"
#include "Elements.h"

class ThongKeView {
private:
	bool active;
	DATASHEET::Controler controler;

private:
	void CreateDatasheets(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler);

public:

	ThongKeView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);

	void Run();
};

#endif // !THONG_KE_VIEW
